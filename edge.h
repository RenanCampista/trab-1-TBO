#if !defined(_EDGE_H_)
#define _EDGE_H_

typedef struct Edge Edge;

Edge *edge_construct(int src, int dest, double weight);
void edge_destroy(Edge *e);
int edge_compare(const void *a, const void *b);
int edge_get_src(Edge *e);
int edge_get_dest(Edge *e);

#endif // _EDGE_H_
