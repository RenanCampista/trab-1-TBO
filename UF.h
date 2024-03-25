#if !defined(_UF_H_)
#define _UF_H_

int UF_find(int *parent, int i);
void UF_union(int *parent, int *sz, int p, int q);
int UF_connected(int *parent, int p, int q);

#endif // _UF_H_
