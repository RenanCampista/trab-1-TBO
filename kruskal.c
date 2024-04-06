#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "kruskal.h"
#include "UF.h"

typedef struct Kruskal Kruskal;
struct Kruskal {
    CartesianPlane *cp;
};

typedef struct Edge Edge;
struct Edge {
    int src, dest;
    double weight;
};

int edge_compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

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
            (&edges[z])->src = i;
            (&edges[z])->dest = j;
            (&edges[z])->weight = point_euclidean_distance(p1, p2, dimension);
            z++;
        }
    }
    qsort(edges, total_points * (total_points - 1) / 2, sizeof(Edge), edge_compare);
}

void process_edges(int *parent, int *sz, Edge *edges, Kruskal *k, int groups) {
    int num_edges = 0;
    int i = 0;
    while (num_edges < cartesian_plane_get_number_points(k->cp) - groups) {
        i++;
        
        if (!UF_connected(parent, edges[i].src, edges[i].dest)) {
            UF_union(parent, sz, edges[i].src, edges[i].dest);
            num_edges++;
        }
    }
}

void kruskal_print_groups_and_destroy(Kruskal *k, int *parent, char *output_file) {
    int total_points = cartesian_plane_get_number_points(k->cp);
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

    fclose(output);
    free(visited);
    free(parent);
}

void kruskal_solve(CartesianPlane *cp, int groups, char *output_file) {
    cartesian_plane_qsort(cp);
    
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
    
    kruskal_print_groups_and_destroy(k, parent, output_file);
    free(edges);
    free(sz);
    kruskal_destroy(k);
}
