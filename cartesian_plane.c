#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "cartesian_plane.h"
#include "vector.h"
#include "point.h"

struct CartesianPlane {
    Vector *points;
    int dimension; 
    double ** euclidean_dist;
};


CartesianPlane *cartesian_plane_construct() {
    CartesianPlane *cp = (CartesianPlane *)calloc(1, sizeof(CartesianPlane));
    if (cp == NULL)
        exit(printf("Error: cartesian_plane_construct failed to allocate memory.\n"));

    cp->points = vector_construct();
    // A matriz deve ser alocada somente após a leitura, após saber a quantidade de pontos (vector_size)
    return cp;
}

void cartesian_plane_destroy(CartesianPlane *cp) {
    for (int i = 0; i < vector_size(cp->points); i++) {
        free(cp->euclidean_dist[i]);
        point_destroy((Point *)vector_get(cp->points, i));
    }
    free(cp->euclidean_dist);    
    vector_destroy(cp->points);
    free(cp);
}

void cartesian_plane_read(CartesianPlane *cp, char *input_file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *input = fopen(input_file, "r");
    if (input == NULL)
        exit(printf("Error: cartesian_plane_read failed to open input file.\n"));

    if ((read = getline(&line, &len, input)) == -1)
        exit(printf("Error: cartesian_plane_read input file is empty.\n"));

    // Remove o caractere de nova linha (\n) do final da linha. Evitar realloc.
    line[strcspn(line, "\n")] = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',') 
            cp->dimension++;    
    }
    // Retorna ao início do arquivo para processar novamente
    fseek(input, 0, SEEK_SET);

    while((read = getline(&line, &len, input)) != -1) {
        // Remove o caractere \n do final da linha
        line[strcspn(line, "\n")] = 0;
        Point *p = point_read(cp->dimension, line);
        vector_push_back(cp->points, p);
    }
    free(line);
    fclose(input);
    cp->euclidean_dist = (double **)calloc(vector_size(cp->points), sizeof(double *));
    for (int i = 0; i < vector_size(cp->points); i++) 
        cp->euclidean_dist[i] = (double *)calloc(vector_size(cp->points), sizeof(double));
}

void cartesian_plane_calculate_distances(CartesianPlane *cp) {
    for (int i = 0; i < vector_size(cp->points); i++) {
        for (int j = 0; j < i; j++) {
            Point *p1 = (Point *) vector_get(cp->points, i);
            Point *p2 = (Point *) vector_get(cp->points, j);
            cp->euclidean_dist[i][j] = point_euclidean_distance(p1, p2, cp->dimension);
        }
    }
}

// Debug
void cartesian_plane_print_distances(CartesianPlane *cp) {
    for (int i = 0; i < vector_size(cp->points); i++) {
        for (int j = 0; j < i; j++) {
            printf("%.2f\t", cp->euclidean_dist[i][j]);
        }
        printf("\n");
    }
}

int cartesian_plane_get_number_points(CartesianPlane *cp) {
    return vector_size(cp->points);
}

double cartesian_plane_get_distance(CartesianPlane *cp, int i, int j) {
    return cp->euclidean_dist[i][j];
}

Point *cartesian_plane_get_point(CartesianPlane *cp, int i) {
    return (Point *) vector_get(cp->points, i);
}
