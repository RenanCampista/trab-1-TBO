#if !defined(_KRUSKAL_H_)
#define _KRUSKAL_H_
#include "cartesian_plane.h"

typedef struct Kruskal Kruskal;

Kruskal *kruskal_construct(CartesianPlane *cp);
void kruskal_destroy(Kruskal *k);
void kruskal_solve(Kruskal *k, int groups);

#endif // _KRUSKAL_H_
