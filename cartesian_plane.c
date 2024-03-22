#include <stdio.h>
#include <stdlib.h>
#include "cartesian_plane.h"
#include "vector.h"
#include "point.h"

struct CartesianPlane {
    Vector *points;
    int dimension; // Colocando a dimensão pd retirar a variavel size  de Point e assim economizar memória
    double ** euclidean_dist;
    // Armazenar a quantidade de grupos?
};

// Fazer uma função para leitura de pontos

CartesianPlane *cartesian_plane_construct(int dimension) {
    CartesianPlane *cp = (CartesianPlane *)calloc(1, sizeof(CartesianPlane));
    if (cp == NULL)
        exit(printf("Error: cartesian_plane_construct failed to allocate memory.\n"));

    cp->points = vector_construct();
    cp->dimension = dimension;
    // A matriz deve ser alocada somente após a leitura, após saber a quantidade de pontos (vector_size)

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

void cartesian_plane_calculate_distances(CartesianPlane *cp) {
    for (int i = 0; i < vector_size(cp->points); i++) {
        for (int j = 0; j < i; j++) {
            Point *p1 = (Point *) vector_get(cp->points, i);
            Point *p2 = (Point *) vector_get(cp->points, j);
            cp->euclidean_dist[i][j] = point_euclidean_distance(p1, p2);
        }
    }
}