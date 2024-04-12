/**
 * @file kruskal.h
 * @brief Este arquivo contém a definição da função kruskal_solve e suas dependências.
 */

#if !defined(_KRUSKAL_H_)
#define _KRUSKAL_H_
#include "cartesian_plane.h"

/**
 * @struct Kruskal
 * @brief Estrutura para representar o algoritmo de Kruskal.
 */
typedef struct Kruskal Kruskal;

/**
 * @brief Resolve o problema usando o algoritmo de Kruskal.
 * @param cp Ponteiro para o plano cartesiano.
 * @param groups Número de grupos.
 * @return Ponteiro para a estrutura Kruskal.
 */
Kruskal *kruskal_solve(CartesianPlane *cp, int groups);

/**
 * @brief Imprime os grupos formados pelo algoritmo de Kruskal.
 * @param k Ponteiro para a estrutura Kruskal.
 * @param output_file Nome do arquivo de saída.
 */
void kruskal_print_groups(Kruskal *k, char *output_file);

/**
 * @brief Libera a memória alocada para a estrutura Kruskal.
 * @param k Ponteiro para a estrutura Kruskal.
 */
void kruskal_destroy(Kruskal *k);

#endif // _KRUSKAL_H_