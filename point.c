#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"

struct Point {
    char *id;
    double *coordinate;
};


Point *point_construct(char *id, int size) {
    Point *p = (Point *) calloc(1, sizeof(Point));
    if (p == NULL)
        exit(printf("Error: point_construct failed to allocate memory.\n"));
    p->coordinate = (double *) calloc(size, sizeof(double));
    p->id = strdup(id);
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
    free(p->id);
    free(p);
}

// Debug
void point_print(Point *p, int dimension) {
    printf("%s", p->id);
    for (int i = 0; i < dimension; i++) {
        printf(",%.2f", p->coordinate[i]);
    }
    printf("\n");
}

double point_euclidean_distance(Point *p1, Point *p2, int dimension) {
    double sum = 0;
    for (int i = 0; i < dimension; i++) 
        sum += (p1->coordinate[i] - p2->coordinate[i]) * (p1->coordinate[i] - p2->coordinate[i]);
    return sum; // sqrt(sum) não é necessário para comparação.
}

char *point_get_id(Point *p) {
    return p->id;
}

int point_compare(const void *a, const void *b) {
    Point *p1 = *(Point **)a;
    Point *p2 = *(Point **)b;
    return strcmp(p1->id, p2->id);
}
