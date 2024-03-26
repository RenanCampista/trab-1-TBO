#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "cartesian_plane.h"

struct Edge {
    int src, dest;
    double weight;
};


Edge *edge_construct(int src, int dest, double weight) {
    Edge *e = (Edge *)calloc(1, sizeof(Edge));
    if (e == NULL)
        exit(printf("Error: edge_construct failed to allocate memory.\n"));

    e->src = src;
    e->dest = dest;
    e->weight = weight;

    return e;
}

void edge_destroy(Edge *e) {
    free(e);
}

int edge_compare(const void *a, const void *b) {
    return ((*(Edge **)a)->weight > (*(Edge **)b)->weight) - ((*(Edge **)a)->weight < (*(Edge **)b)->weight);
}

int edge_get_src(Edge *e) {
    return e->src;
}

int edge_get_dest(Edge *e) {
    return e->dest;
}
