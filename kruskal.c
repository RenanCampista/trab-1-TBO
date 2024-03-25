#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartesian_plane.h"
#include "point.h"
#include "vector.h"
#include "kruskal.h"
#include "edge.h"
#include <stdbool.h>

struct Kruskal {
    CartesianPlane *cp;
    Edge **edges;
};

Kruskal *kruskal_construct(CartesianPlane *cp) {
    Kruskal *k = (Kruskal *)calloc(1, sizeof(Kruskal));
    k->cp = cp;
    k->edges = (Edge **)calloc(cartesian_plane_get_number_points(cp) * (cartesian_plane_get_number_points(cp) - 1) / 2, sizeof(Edge *));
    if (k == NULL || k->edges == NULL)
        exit(printf("Error: kruskal_construct failed to allocate memory.\n"));

    int z = 0;
    for (int i = 0; i < cartesian_plane_get_number_points(cp); i++) {
        for (int j = 0; j < i; j++) {
            double distance = cartesian_plane_get_distance(cp, i, j);
            k->edges[z] = edge_construct(i, j, distance);
            z++;
        }
    }

    return k;
}

void kruskal_destroy(Kruskal *k) {
    for (int i = 0; i < cartesian_plane_get_number_points(k->cp) * (cartesian_plane_get_number_points(k->cp) - 1) / 2; i++)
        edge_destroy(k->edges[i]);
    free(k->edges);
    free(k);
}

int kruskal_find(int *parent, int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

void kruskal_union(int *parent, int *sz,int p, int q) {
    int i = kruskal_find(parent, p);
    int j = kruskal_find(parent, q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        parent[i] = j;
        sz[j] += sz[i];
    } else {
        parent[j] = i;
        sz[i] += sz[j];
    }
    
}

void union_print(int *parent, int n, bool *visited) {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("%d ", i);
            visited[i] = true;
            int j = i;
            while (parent[j] != j) {
                printf("%d ", parent[j]);
                visited[parent[j]] = true;
                j = parent[j];
            }
            printf("\n");
        }
    }
}

// Essa função será modularizada
void kruskal_solve(Kruskal *k, int groups) {
    // Ordenando as arestas de acordo com a distancia (pesos). O numero de arestas eh n*(n-1)/2.
    qsort(k->edges, cartesian_plane_get_number_points(k->cp) * (cartesian_plane_get_number_points(k->cp) - 1) / 2, sizeof(Edge *), edge_compare);

    // Inicializando os vetores parent, sz e rank. Sera usado para fazer a uniao dos conjuntos. (union-find algorithm)
    int *parent = (int *)calloc(cartesian_plane_get_number_points(k->cp), sizeof(int));
    if (parent == NULL)
        exit(printf("Error: kruskal_solve failed to allocate memory.\n"));
    int *sz = (int *)calloc(cartesian_plane_get_number_points(k->cp), sizeof(int));
    if (sz == NULL)
        exit(printf("Error: kruskal_solve failed to allocate memory.\n"));
    
    for (int i = 0; i < cartesian_plane_get_number_points(k->cp); i++) {
        parent[i] = i;
    }

    int *rank = (int *)calloc(cartesian_plane_get_number_points(k->cp), sizeof(int));
    if (rank == NULL)
        exit(printf("Error: kruskal_solve failed to allocate memory.\n"));

    int num_edges = 0;
    int i = 0;

    /*
    O loop `while` continua até que o número de arestas seja menor que o número de pontos no plano cartesiano menos o número de grupos. Isso garante que todas as arestas necessárias para conectar todos os pontos sejam consideradas.
    
    A cada iteração, uma aresta é selecionada do array de arestas `k->edges[i]` e o índice `i` é incrementado.

    As funções `kruskal_find` são usadas para encontrar os conjuntos aos quais os pontos de origem (`edge_get_src(edge)`) e destino (`edge_get_dest(edge)`) da aresta pertencem. Isso é feito para verificar se a adição da aresta atual criará um ciclo.

    Se os pontos de origem e destino pertencerem a conjuntos diferentes (`x != y`), a aresta é adicionada à árvore geradora mínima. Isso é feito pela função `kruskal_union`, que une os dois conjuntos. O número de arestas (`num_edges`) é então incrementado.

    O processo é repetido até que todas as arestas necessárias sejam adicionadas à árvore geradora mínima.
    */
    while (num_edges < cartesian_plane_get_number_points(k->cp) - groups) {
        Edge *edge = k->edges[i];
        i++;

        int x = kruskal_find(parent, edge_get_src(edge));
        int y = kruskal_find(parent, edge_get_dest(edge));
        if (x != y) {
            kruskal_union(parent, sz, x, y);
            num_edges++;
        }
    }

    // Daqui em diante é apenas para printar a árvore geradora mínima. Modularizar isso em uma função.
    bool *visited = (bool *)calloc(cartesian_plane_get_number_points(k->cp), sizeof(bool));

    for (int i = 0; i < cartesian_plane_get_number_points(k->cp); i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < cartesian_plane_get_number_points(k->cp); i++) {
        printf("%d ", parent[i]);

        // if (!visited[i]) {
        //     Point *p = cartesian_plane_get_point(k->cp, i);
        //     printf("%s", point_get_id(p));
        //     visited[i] = true;
        //     int j = i;
        //     while (parent[j] != j) {
        //         Point *p = cartesian_plane_get_point(k->cp, parent[j]);
        //         if (!visited[parent[j]])
        //             printf(", %s", point_get_id(p));
        //         visited[parent[j]] = true;
        //         j = parent[j];
        //     }
        //     printf("\n");
        // }
    }
    printf("\n");
    for (int i = 0; i < cartesian_plane_get_number_points(k->cp); i++) {
        Point *p = cartesian_plane_get_point(k->cp, i);
        printf("%s ", point_get_id(p));
    }
    printf("\n\n");
    for (int i = 0; i < cartesian_plane_get_number_points(k->cp); i++) {
        if (!visited[i]) {
            Point *p = cartesian_plane_get_point(k->cp, i);
            printf("%s", point_get_id(p));
            visited[i] = true;
            int j = i;
            while (parent[j] != j) {
                Point *p = cartesian_plane_get_point(k->cp, parent[j]);
                if (!visited[parent[j]])
                    printf(", %s", point_get_id(p));
                visited[parent[j]] = true;
                j = parent[j];
            }
            printf("\n");
        }
    }


    free(parent);
    free(rank);
    free(sz);
    free(visited);
}