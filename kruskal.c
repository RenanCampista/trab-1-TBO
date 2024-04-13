#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "kruskal.h"
#include "UF.h"
#include "time.h"

struct Kruskal {
    CartesianPlane *cp;
    int *parent;
    int *sz;
};

typedef struct Edge Edge;
struct Edge {
    int src, dest;
    double weight;
};

int edge_compare(const void *a, const void *b) {
    Edge *edge1 = (Edge *)a;
    Edge *edge2 = (Edge *)b;
    if (edge1->weight < edge2->weight) return -1;
    else if (edge1->weight > edge2->weight) return 1;
    else return 0;
}

Kruskal *kruskal_construct(CartesianPlane *cp) {
    Kruskal *k = (Kruskal *)calloc(1, sizeof(Kruskal));
    if (k == NULL)
        exit(printf("Error: kruskal_construct failed to allocate memory.\n"));
    k->cp = cp;
    k->parent = (int *)calloc(cartesian_plane_get_number_points(cp), sizeof(int));
    k->sz = (int *)calloc(cartesian_plane_get_number_points(cp), sizeof(int));
    if (k->parent == NULL || k->sz == NULL)
        exit(printf("Error: kruskal_construct failed to allocate memory.\n"));
    return k;
}

void kruskal_destroy(Kruskal *k) {
    free(k->parent);
    free(k->sz);
    free(k);
}

void populate_edges_and_parents(Edge *edges, Kruskal *k) {
    int total_points = cartesian_plane_get_number_points(k->cp);
    int z = 0;
    int dimension = cartesian_plane_get_dimension(k->cp);

    for (int i = 0; i < total_points; i++) {
        k->parent[i] = i;
        k->sz[i] = 1;
        Point *p1 = cartesian_plane_get_point(k->cp, i);
        for (int j = 0; j < i; j++) {
            Point *p2 = cartesian_plane_get_point(k->cp, j);
            (&edges[z])->src = i;
            (&edges[z])->dest = j;

            //Tempo para calcular as distancias
            clock_t start = clock();
            (&edges[z])->weight = point_euclidean_distance(p1, p2, dimension);
            clock_t end = clock();
            calcula_tempo(start, end, TEMPO_CALCULO_DISTANCIAS);
            z++;
        }
    }

}

void process_edges(Edge *edges, Kruskal *k, int groups) {
    int total_points = cartesian_plane_get_number_points(k->cp);
    //Tempo para ordenar as arestas
    clock_t start = clock();
    qsort(edges, total_points * (total_points - 1) / 2, sizeof(Edge), edge_compare);
    clock_t end = clock();
    calcula_tempo(start, end, TEMPO_ORDENACAO_DISTANCIAS);
    int num_edges = 0;
    int i = 0;
    while (num_edges < total_points - groups) {
        i++;

        if (!UF_connected(k->parent, edges[i].src, edges[i].dest)) {
            UF_union(k->parent, k->sz, edges[i].src, edges[i].dest);
            num_edges++;
        }
    }
}

void kruskal_print_groups(Kruskal *k, char *output_file) {
    int total_points = cartesian_plane_get_number_points(k->cp);
    bool *visited = (bool *)calloc(total_points, sizeof(bool));
    if (visited == NULL)
        exit(printf("Error: kruskal_print_groups failed to allocate memory.\n"));

    FILE *output = fopen(output_file, "w");
    if (output == NULL)
        exit(printf("Error: kruskal_print_groups failed to open file.\n"));

    for (int i = 0; i < total_points; i++) {
        //Identificação do grupo
        clock_t start = clock();
        int x = UF_find(k->parent, i);
        if (!visited[x]) {
            visited[x] = true;
            Point *p = cartesian_plane_get_point(k->cp, i);
            fprintf(output, "%s", point_get_id(p));
            for (int j = i + 1; j < total_points; j++) {
                if (UF_find(k->parent, j) == x) {
                    Point *p = cartesian_plane_get_point(k->cp, j);
                    fprintf(output, ", %s", point_get_id(p));
                    visited[j] = true;
                }
            }
        clock_t end = clock();
        calcula_tempo(start, end, TEMPO_IDENT_GRUPOS);
            fprintf(output, "\n");
        }
    }

    fclose(output);
    free(visited);
}

Kruskal *kruskal_solve(CartesianPlane *cp, int groups) {
    clock_t start = clock();
    cartesian_plane_qsort(cp);
    clock_t end = clock();
    calcula_tempo(start, end, TEMPO_ESCRITA_SAIDA);

    Kruskal *k = kruskal_construct(cp);
    //O numero de arestas eh n*(n-1)/2.
    int total_edges = cartesian_plane_get_number_points(k->cp) * (cartesian_plane_get_number_points(k->cp) - 1) / 2;

    Edge *edges = (Edge *)calloc(total_edges, sizeof(Edge ));
    if (edges == NULL)
        exit(printf("Error: kruskal_solve failed to allocate memory.\n"));

    populate_edges_and_parents(edges, k);

    //Tempo para obter a arvore geradora minima
    start = clock();
    process_edges(edges, k, groups);
    end = clock();
    calcula_tempo(start, end, TEMPO_OBTENCAO_MST);
    free(edges);
    
    return k;
}
