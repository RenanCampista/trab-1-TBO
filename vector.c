
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static const int VECTOR_INIT_SIZE = 100;
static const int VECTOR_GROWTH_RATE = 150;

struct Vector {
    data_type *data;
    int size;
    int allocated;
};

Vector *vector_construct() {
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    if (v == NULL)
        exit(printf("Error: vector_construct: could not allocate memory.\n"));
        
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));

    return v;
}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

int vector_size(Vector *v) {
    return v->size;
}

data_type vector_get(Vector *v, int i) {
    if (i >= vector_size(v) || i < 0)
        exit(printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v)));
    return v->data[i];
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size >= v->allocated) {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

data_type vector_remove(Vector *v, int i) {
    if (i >= v->size || i < 0)
        exit(printf("Error: vector_remove: invalid index %d for vector with size %d.\n", i, v->size));

    data_type val = v->data[i];

    for (int j = i; j < v->size - 1; j++)
        v->data[j] = v->data[j + 1];

    v->size--;
    return val;
}

data_type vector_pop_front(Vector *v) {
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v) {
    return vector_remove(v, v->size - 1);
}

void vector_swap(Vector *v, int i, int j) {
    data_type temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_sort(Vector *v) {
    for (int i = 0; i < v->size - 1; i++) {
        int n_trocas = 0;
        for (int j = 0; j < v->size - i - 1; j++) {
            if (v->data[j] > v->data[j + 1]) {
                vector_swap(v, j, j + 1);
                n_trocas++;
            }
        }
        if (n_trocas == 0)
            break;
    }
}

int vector_binary_search(Vector *v, data_type val) {
    int left = 0;
    int right = v->size - 1;

    while (left <= right){
        int mid = left + (right - left) / 2;

        if (v->data[mid] == val)
            return mid;
        else if (v->data[mid] < val)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}
