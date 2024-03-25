#if !defined(_UF_H_)
#define _UF_H_

typedef struct UF UF;

UF *UF_construct(int size);
void UF_destroy(UF *uf);
int UF_find(UF *uf, int i);
void UF_union(UF *uf, int p, int q);
int UF_get_count(UF *uf);
int UF_connected(UF *uf, int p, int q);
void UF_print(UF *uf);
int UF_get_id(UF *uf, int i);

#endif // _UF_H_
