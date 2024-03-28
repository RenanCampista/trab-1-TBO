/**
 * @file kruskal.h
 * @brief Este arquivo contém a definição da função kruskal_solve e suas dependências.
 */

#if !defined(_KRUSKAL_H_)
#define _KRUSKAL_H_
#include "cartesian_plane.h"

/**
 * @brief Resolve o problema de agrupamento utilizando o algoritmo de Kruskal.
 * @param cp Ponteiro para a estrutura que representa o plano cartesiano.
 * @param groups Número de grupos a serem formados.
 * @param output_file Nome do arquivo onde a saída será escrita.
 */
void kruskal_solve(CartesianPlane *cp, int groups, char *output_file);

#endif // _KRUSKAL_H_