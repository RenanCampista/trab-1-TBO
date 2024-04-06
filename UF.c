#include "UF.h"

int UF_find(int *parent, int i) {
    while (parent[i] != i) {
        parent[i] = parent[parent[i]];
        i = parent[i];
    }
    return i;
}

void UF_union(int *parent, int *sz, int p, int q) {
    int i = UF_find(parent, p);
    int j = UF_find(parent, q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        parent[i] = j;
        sz[j] += sz[i];
    } else {
        parent[j] = i;
        sz[i] += sz[j];
    }
}
