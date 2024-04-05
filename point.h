/**
 * @file point.h
 * @brief Este arquivo contém a definição da estrutura Point e suas funções relacionadas.
 */

#if !defined(_POINT_H_)
#define _POINT_H_

/**
 * @brief Estrutura para representar um ponto.
 */
typedef struct Point Point;

/**
 * @brief Constrói um ponto.
 * @param id O ID do ponto.
 * @param size O tamanho do ponto.
 * @return Um ponteiro para o ponto construído.
 */
Point *point_construct(char *id, int size);

/**
 * @brief Lê um ponto de uma linha.
 * @param size O tamanho do ponto.
 * @param line A linha de onde ler o ponto.
 * @return Um ponteiro para o ponto lido.
 */
Point *point_read(int size, char *line);

/**
 * @brief Destroi um ponto.
 * @param p O ponto a ser destruído.
 */
void point_destroy(Point *p);

/**
 * @brief Calcula a distância euclidiana entre dois pontos.
 * @param p1 O primeiro ponto.
 * @param p2 O segundo ponto.
 * @param dimension A dimensão dos pontos.
 * @return A distância euclidiana entre os dois pontos.
 */
double point_euclidean_distance(Point *p1, Point *p2, int dimension);

/**
 * @brief Obtém o ID de um ponto.
 * @param p O ponto do qual obter o ID.
 * @return O ID do ponto.
 */
char *point_get_id(Point *p);

/**
 * @brief Compara dois pontos.
 * @param a O primeiro ponto.
 * @param b O segundo ponto.
 * @return O resultado da comparação.
 */
int point_compare(const void *a, const void *b);

#endif // _POINT_H_