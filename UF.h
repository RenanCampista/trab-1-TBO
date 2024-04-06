/**
 * @file UF.h
 * @brief Este arquivo contém a definição da estrutura de dados Union-Find e suas funções relacionadas.
 */

#if !defined(_UF_H_)
#define _UF_H_

/**
 * @brief Encontra o conjunto de um elemento.
 * @param parent O array parent representando os conjuntos disjuntos.
 * @param i O elemento a ser encontrado.
 * @return O representante do conjunto ao qual o elemento pertence.
 */
int UF_find(int *parent, int i);

/**
 * @brief Une dois conjuntos.
 * @param parent O array parent representando os conjuntos disjuntos.
 * @param sz O array sz para acompanhar o tamanho de cada conjunto.
 * @param p O primeiro conjunto.
 * @param q O segundo conjunto.
 */
void UF_union(int *parent, int *sz, int p, int q);

#endif // _UF_H_