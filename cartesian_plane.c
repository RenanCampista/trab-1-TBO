#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "cartesian_plane.h"
#include "point.h"

static const int VECTOR_INIT_SIZE = 100;
static const int VECTOR_GROWTH_RATE = 150;

struct CartesianPlane {
    Point **points;
    int number_points;
    int allocated_points;
    int dimension; 
};


CartesianPlane *cartesian_plane_construct() {
    CartesianPlane *cp = (CartesianPlane *)calloc(1, sizeof(CartesianPlane));
    if (cp == NULL)
        exit(printf("Error: cartesian_plane_construct failed to allocate memory.\n"));

    cp->allocated_points = VECTOR_INIT_SIZE;
    cp->points = (Point **)calloc(cp->allocated_points, sizeof(Point *));
    cp->number_points = 0;
    return cp;
}

void cartesian_plane_destroy(CartesianPlane *cp) {
    for (int i = 0; i < cp->number_points; i++)
        point_destroy(cp->points[i]);
    free(cp->points);
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

        if(cp->number_points == cp->allocated_points) {
            cp->allocated_points *= VECTOR_GROWTH_RATE;
            cp->points = (Point **)realloc(cp->points, cp->allocated_points * sizeof(Point *));
        }
        cp->points[cp->number_points] = p;
        cp->number_points++;

    }
    free(line);
    fclose(input);
}

int cartesian_plane_get_number_points(CartesianPlane *cp) {
    return cp->number_points;
}

Point *cartesian_plane_get_point(CartesianPlane *cp, int i) {
    return cp->points[i];
}

int cartesian_plane_get_dimension(CartesianPlane *cp) {
    return cp->dimension;
}

void cartesian_plane_qsort(CartesianPlane *cp) {
    qsort(cp->points, cp->number_points, sizeof(Point *), point_compare);
}

// Debug
// void cartesian_plane_print(CartesianPlane *cp) {
//     for (int i = 0; i < cp->number_points; i++)
//         point_print(cp->points[i], cp->dimension);
// }  
 