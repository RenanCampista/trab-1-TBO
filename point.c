#include <stdio.h>
#include <stdlib.h>
#include "point.h"

Point *point_construct(int size) {
    Point *p = (Point *) calloc(1, sizeof(Point));
    if (p == NULL)
        exit(printf("Error: point_construct failed to allocate memory.\n"));
    p->coordinate = (float *) calloc(size, sizeof(float));
    p->size = size;
    return p;
}

void point_destruct(Point *p) {
    free(p->coordinate);
    free(p);
}