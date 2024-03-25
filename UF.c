#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UF.h"

struct UF {
    int *parent;
    int *sz;
    int count;
};

UF *UF_construct(int size) {
    UF *uf = (UF *)calloc(1, sizeof(UF));
    uf->parent = (int *)calloc(size, sizeof(int));
    uf->sz = (int *)calloc(size, sizeof(int));
    
    if (uf == NULL || uf->parent == NULL || uf->sz == NULL)
        exit(printf("Error: UF_construct failed to allocate memory.\n"));
    uf->count = size;

    for (int i = 0; i < size; i++) 
        uf->parent[i] = i;

    return uf;
}

void UF_destroy(UF *uf) {
    free(uf->parent);
    free(uf->sz);
    free(uf);
}

int UF_find(UF *uf, int i) {
    while (uf->parent[i] != i) {
        uf->parent[i] = uf->parent[uf->parent[i]];
        i = uf->parent[i];
    }
    return i;
}

void UF_union(UF *uf, int p, int q) {
    int i = UF_find(uf, p);
    int j = UF_find(uf, q);
    if (i == j) return;
    if (uf->sz[i] < uf->sz[j]) {
        uf->parent[i] = j;
        uf->sz[j] += uf->sz[i];
    } else {
        uf->parent[j] = i;
        uf->sz[i] += uf->sz[j];
    }
    //uf->count--;
}

int UF_get_count(UF *uf) {
    return uf->count;
}

int UF_connected(UF *uf, int p, int q) {
    return UF_find(uf, p) == UF_find(uf, q);
}

void UF_print(UF *uf) {
    bool *visited = (bool *)calloc(uf->count, sizeof(bool));
    if (visited == NULL)
        exit(printf("Error: UF_print failed to allocate memory.\n"));

    for (int i = 0; i < uf->count; i++) {
        if (!visited[i]) {
            printf("%d: ", i);
            for (int j = 0; j < uf->count; j++) {
                if (UF_find(uf, j) == i) {
                    printf("%d ", j);
                    visited[j] = true;
                }
            }
            printf("\n");
        }
    }
    free(visited);
}

int UF_get_id(UF *uf, int i) {
    return uf->parent[i];
}