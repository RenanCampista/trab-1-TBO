/**
 * @file cartesian_plane.h
 * @brief Este arquivo contém a definição da estrutura CartesianPlane e suas funções relacionadas.
 */

#if !defined(_CARTESIAN_PLANE_H_)
#define _CARTESIAN_PLANE_H_

#include "point.h"

/**
 * @brief Estrutura para representar um plano cartesiano.
 */
typedef struct CartesianPlane CartesianPlane;

/**
 * @brief Constrói um plano cartesiano.
 * @return Um ponteiro para o plano cartesiano construído.
 */
CartesianPlane *cartesian_plane_construct();

/**
 * @brief Destroi um plano cartesiano.
 * @param cp O plano cartesiano a ser destruído.
 */
void cartesian_plane_destroy(CartesianPlane *cp);

/**
 * @brief Lê um plano cartesiano de um arquivo de entrada.
 * @param cp O plano cartesiano para ler.
 * @param input_file O arquivo de entrada de onde ler o plano cartesiano.
 */
void cartesian_plane_read(CartesianPlane *cp, char *input_file);

/**
 * @brief Obtém o número de pontos em um plano cartesiano.
 * @param cp O plano cartesiano do qual obter o número de pontos.
 * @return O número de pontos no plano cartesiano.
 */
int cartesian_plane_get_number_points(CartesianPlane *cp);

/**
 * @brief Obtém um ponto de um plano cartesiano.
 * @param cp O plano cartesiano do qual obter o ponto.
 * @param i O índice do ponto a obter.
 * @return Um ponteiro para o ponto.
 */
Point *cartesian_plane_get_point(CartesianPlane *cp, int i);

/**
 * @brief Obtém a dimensão de um plano cartesiano.
 * @param cp O plano cartesiano do qual obter a dimensão.
 * @return A dimensão do plano cartesiano.
 */
int cartesian_plane_get_dimension(CartesianPlane *cp);

/**
 * @brief Ordena os pontos de um plano cartesiano.
 * @param cp O plano cartesiano a ser ordenado.
 */
void cartesian_plane_qsort(CartesianPlane *cp);

#endif // _CARTESIAN_PLANE_H_