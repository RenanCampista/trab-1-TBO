/**
 * @file vector.h
 * @brief Este arquivo contém a definição da estrutura de dados Vector e suas funções relacionadas.
 */

#if !defined(_VECTOR_H_)
#define _VECTOR_H_

/**
 * @brief Estrutura para representar um vetor.
 */
typedef struct Vector Vector;

/**
 * @brief Tipo de dado genérico.
 */
typedef void * data_type;

/**
 * @brief Constrói um vetor.
 * @return Um ponteiro para o vetor construído.
 */
Vector *vector_construct();

/**
 * @brief Destroi um vetor.
 * @param v O vetor a ser destruído.
 */
void vector_destroy(Vector *v);

/**
 * @brief Adiciona um elemento ao vetor.
 * @param v O vetor ao qual o elemento será adicionado.
 * @param element O elemento a ser adicionado.
 */
void vector_push_back(Vector *v, void *element);

/**
 * @brief Obtém um elemento do vetor.
 * @param v O vetor do qual o elemento será obtido.
 * @param index O índice do elemento a ser obtido.
 * @return Um ponteiro para o elemento.
 */
void *vector_get(Vector *v, int index);

/**
 * @brief Obtém o tamanho do vetor.
 * @param v O vetor do qual o tamanho será obtido.
 * @return O tamanho do vetor.
 */
int vector_size(Vector *v);

#endif // _VECTOR_H_