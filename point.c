#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"

struct Point {
    char *id;
    double *coordinate;
    int size;
};

Point *point_construct(char *id, int size) {
    Point *p = (Point *) calloc(1, sizeof(Point));
    if (p == NULL)
        exit(printf("Error: point_construct failed to allocate memory.\n"));
    p->coordinate = (double *) calloc(size, sizeof(double));
    p->size = size;
    p->id = id;
    return p;
}

Point *point_read(int size, char *line) {
    char *token = strtok(line, ",");
    Point *p = point_construct(token, size);
    int i = 0;

    token = strtok(NULL, ",");
    while(token != NULL || i < size) {
        p->coordinate[i] = strtod(token, NULL);
        token = strtok(NULL, ",");
        i++;
    }

    return p;
}

void point_destroy(Point *p) {
    free(p->coordinate);
    free(p);
}

// Debug
void point_print(Point *p) {
    printf("%s", p->id);
    for (int i = 0; i < p->size; i++) {
        printf(",%.2f", p->coordinate[i]);
    }
    printf("\n");
}

double point_euclidean_distance(Point *p1, Point *p2) {
    double sum = 0;
    for (int i = 0; i < p1->size; i++) 
        sum += (p1->coordinate[i] - p2->coordinate[i]) * (p1->coordinate[i] - p2->coordinate[i]);
    // sqrt(sum) não é necessário para comparação
    return sum;
}