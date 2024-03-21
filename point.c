#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"

Point *point_construct(char *id, int size) {
    Point *p = (Point *) calloc(1, sizeof(Point));
    if (p == NULL)
        exit(printf("Error: point_construct failed to allocate memory.\n"));
    p->coordinate = (float *) calloc(size, sizeof(float));
    p->size = size;
    p->id = strdup(id);
    return p;
}

Point *point_read(int size, char *token) {
    Point *p = point_construct(size, token);
    int i = 0;

    while(token != NULL) {
        token = strtok(NULL, ",");
        p->coordinate[i] = atof(token);
        i++;
    }
    
    return p;
}

void point_destruct(Point *p) {
    free(p->coordinate);
    free(p);
}