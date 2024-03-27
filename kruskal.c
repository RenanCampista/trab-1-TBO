#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "kruskal.h"
#include "edge.h"
#include "UF.h"

typedef struct Kruskal Kruskal;

struct Kruskal {
    CartesianPlane *cp;
};


Kruskal *kruskal_construct(CartesianPlane *cp) {
    Kruskal *k = (Kruskal *)calloc(1, sizeof(Kruskal));
    if (k == NULL)
        exit(printf("Error: kruskal_construct failed to allocate memory.\n"));
    k->cp = cp;
    return k;
}

void kruskal_destroy(Kruskal *k) {
    free(k);
}

void populate_edges_and_parents(int *parent, int *sz, Edge *edges, Kruskal *k) {
    int total_points = cartesian_plane_get_number_points(k->cp);
    int z = 0;
    int dimension = cartesian_plane_get_dimension(k->cp);

    for (int i = 0; i < total_points; i++) {
        parent[i] = i;
        sz[i] = 1;
        for (int j = 0; j < i; j++) {
            Point *p1 = cartesian_plane_get_point(k->cp, i);
            Point *p2 = cartesian_plane_get_point(k->cp, j);
            //edges[z] = edge_construct(i, j, point_euclidean_distance(p1, p2, dimension));
            (&edges[z])->src = i;
            (&edges[z])->dest = j;
            (&edges[z])->weight = point_euclidean_distance(p1, p2, dimension);
            z++;
        }
    }
    qsort(edges, total_points * (total_points - 1) / 2, sizeof(Edge), edge_compare);
}

void process_edges(int *parent, int *sz, Edge *edges, Kruskal *k, int groups) {
    /*
        O loop `while` continua até que o número de arestas seja menor que o número de pontos no plano cartesiano menos o número de grupos. Isso garante que todas as arestas necessárias para conectar todos os pontos sejam consideradas.
        
        A cada iteração, uma aresta é selecionada do array de arestas `edges[i]` e o índice `i` é incrementado.

        As funções `kruskal_find` são usadas para encontrar os conjuntos aos quais os pontos de origem (`edge_get_src(edge)`) e destino (`edge_get_dest(edge)`) da aresta pertencem. Isso é feito para verificar se a adição da aresta atual criará um ciclo.

        Se os pontos de origem e destino pertencerem a conjuntos diferentes (`x != y`), a aresta é adicionada à árvore geradora mínima. Isso é feito pela função `kruskal_union`, que une os dois conjuntos. O número de arestas (`num_edges`) é então incrementado.

        O processo é repetido até que todas as arestas necessárias sejam adicionadas à árvore geradora mínima.
    */
    
    int num_edges = 0;
    int i = 0;
    while (num_edges < cartesian_plane_get_number_points(k->cp) - groups) {
        Edge *edge = &edges[i];
        i++;

        int x = UF_find(parent, edge->src);
        int y = UF_find(parent, edge->dest);
        if (x != y) {
            UF_union(parent, sz, x, y);
            num_edges++;
        }
    }
}

void kruskal_print_groups_and_destroy(Kruskal *k, int *parent, Edge *edges, char *output_file) {
    int total_points = cartesian_plane_get_number_points(k->cp);
    //int total_edges = cartesian_plane_get_number_points(k->cp) * (cartesian_plane_get_number_points(k->cp) - 1) / 2;
    bool *visited = (bool *)calloc(total_points, sizeof(bool));
    if (visited == NULL)
        exit(printf("Error: kruskal_print_groups failed to allocate memory.\n"));

    FILE *output = fopen(output_file, "w");
    if (output == NULL)
        exit(printf("Error: kruskal_print_groups failed to open file.\n"));

    for (int i = 0; i < total_points; i++) {
        int x = UF_find(parent, i);
        if (!visited[x]) {
            visited[x] = true;
            Point *p = cartesian_plane_get_point(k->cp, i);
            fprintf(output, "%s", point_get_id(p));
            for (int j = i + 1; j < total_points; j++) {
                if (UF_find(parent, j) == x) {
                    Point *p = cartesian_plane_get_point(k->cp, j);
                    fprintf(output, ", %s", point_get_id(p));
                    visited[j] = true;
                }
            }
            fprintf(output, "\n");
        }
    }

    // Quando sz era sempre zero, tinha que imprimir dessa forma
    // for (int i = 0; i < total_points; i++) {
    //     if (!visited[i]) {
    //         Point *p = cartesian_plane_get_point(k->cp, i);
    //         fprintf(output, "%s", point_get_id(p));
    //         visited[i] = true;

    //         int j = i;
    //         while (parent[j] != j) {
    //             Point *p = cartesian_plane_get_point(k->cp, parent[j]);
    //             if (!visited[parent[j]])
    //                 fprintf(output, ", %s", point_get_id(p));
    //             visited[parent[j]] = true;
    //             j = parent[j];
    //         }
    //         fprintf(output, "\n");
    //     }
    // }

    fclose(output);
    free(visited);
    free(parent);
    // for(int i = 0; i < total_edges; i++)
    //     edge_destroy(&edges[i]);
    free(edges);

}

void kruskal_solve(CartesianPlane *cp, int groups, char *output_file) {
    Kruskal *k = kruskal_construct(cp);
    //O numero de arestas eh n*(n-1)/2.
    int total_edges = cartesian_plane_get_number_points(k->cp) * (cartesian_plane_get_number_points(k->cp) - 1) / 2;
    int total_points = cartesian_plane_get_number_points(k->cp);

    Edge *edges = (Edge *)calloc(total_edges, sizeof(Edge ));
    int *parent = (int *)calloc(total_points, sizeof(int));
    int *sz = (int *)calloc(total_points, sizeof(int));

    if (edges == NULL || parent == NULL || sz == NULL)
        exit(printf("Error: kruskal_solve failed to allocate memory.\n"));

    populate_edges_and_parents(parent, sz, edges, k);
    process_edges(parent, sz, edges, k, groups);
    
    kruskal_print_groups_and_destroy(k, parent, edges, output_file);
    free(sz);
    kruskal_destroy(k);
}
