#if !defined(_VECTOR_H_)
#define _VECTOR_H_

typedef void * data_type;
typedef struct Vector Vector;

Vector *vector_construct();
int vector_size(Vector *v);
data_type vector_get(Vector *v, int i);
void vector_push_back(Vector *v, data_type val);
data_type vector_remove(Vector *v, int i);
data_type vector_pop_front(Vector *v);
data_type vector_pop_back(Vector *v);
void vector_swap(Vector *v, int i, int j);
void vector_sort(Vector *v);
int vector_binary_search(Vector *v, data_type val);
void vector_destroy(Vector *v) ;


#endif // _VECTOR_H_
