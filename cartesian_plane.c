#include <stdio.h>
#include <stdlib.h>
#include "cartesian_plane.h"
#include "vector.h"
#include "point.h"

struct CartesianPlane {
    Vector *points;
    int dimension; // Colocando a dimensão pd retirar a variavel size  de Point e assim economizar memória
    double ** euclidean_dist;
};

// Fazer uma função para leitura de pontos

CartesianPlane *cartesian_plane_construct(int dimension) {
    CartesianPlane *cp = (CartesianPlane *)calloc(1, sizeof(CartesianPlane));
    if (cp == NULL)
        exit(printf("Error: cartesian_plane_construct failed to allocate memory.\n"));

    cp->points = vector_construct();
    cp->dimension = dimension;
    cp->euclidean_dist = (double **)calloc(dimension, sizeof(double *));

    for (int i = 0; i < dimension; i++)
        cp->euclidean_dist[i] = (double *)calloc(dimension, sizeof(double));

    return cp;
}

void cartesian_plane_destroy(CartesianPlane *cp) {
    for (int i = 0; i < cp->dimension; i++)
        free(cp->euclidean_dist[i]);
    free(cp->euclidean_dist);
    for (int i = 0; i < vector_size(cp->points); i++)
        point_destroy((Point *)vector_get(cp->points, i));
    free(cp);
}