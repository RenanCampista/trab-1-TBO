#if !defined(TIME_H)
#define TIME_H

#include <stdio.h>
#include <time.h>

#define TEMPO_TOTAL 0
#define TEMPO_LEITURA 1
#define TEMPO_CALCULO_DISTANCIAS 2
#define TEMPO_ORDENACAO_DISTANCIAS 3
#define TEMPO_OBTENCAO_MST 4
#define TEMPO_IDENT_GRUPOS 5
#define TEMPO_ESCRITA_SAIDA 6


void calcula_tempo(clock_t start, clock_t end, int id_funcao);
void imprime_tempo();

#endif // TIME_H
