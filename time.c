#include <stdio.h>
#include <time.h>
#include "time.h"

double tempo_total = 0, tempo_leitura_dados = 0, tempo_calculo_distancias = 0,
       tempo_ordenação_distancias = 0, tempo_obtencao_mst = 0, tempo_identificação_grupos = 0,
       tempo_escrita_saida = 0, tempo_total_marcado = 0;
void calcula_tempo(clock_t start, clock_t end, int id_funcao)
{
    /*legenda dos ids:
- 0 = tempo_total
- 1 = tempo_leitura
- 2 = tempo_calculo_distancias
- 3 = tempo_ordenação_distancias
- 4 = tempo_obtenção_mst
- 5 = tempo_ident_grupos
- 6 = tempo_escrita_saida
 */
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;

    switch (id_funcao)
    {
    case TEMPO_TOTAL:
        tempo_total += tempo;
        break;
    case TEMPO_LEITURA:
        tempo_leitura_dados += tempo;
        break;
    case TEMPO_CALCULO_DISTANCIAS:
        tempo_calculo_distancias += tempo;
        break;
    case TEMPO_ORDENACAO_DISTANCIAS:
        tempo_ordenação_distancias += tempo;
        break;
    case TEMPO_OBTENCAO_MST:
        tempo_obtencao_mst += tempo;
        break;
    case TEMPO_IDENT_GRUPOS:
        tempo_identificação_grupos += tempo;
        break;
    case TEMPO_ESCRITA_SAIDA:
        tempo_escrita_saida += tempo;
        break;

    default:
        break;
    }
    tempo_total_marcado = tempo_leitura_dados + tempo_ordenação_distancias + tempo_calculo_distancias + tempo_obtencao_mst + tempo_identificação_grupos + tempo_escrita_saida;
}

void imprime_tempo()
{
    FILE *saida;
    saida = fopen("analise_do_tempo", "wt");
    if (saida == NULL)
    {
        printf("Problema na saida da analise de tempo!!\n");
        return;
    }

    fprintf(saida, "Tempo total bruto:                       %f          \n", tempo_total);
    fprintf(saida, "Tempo total :                            %f (%.2f %%)\n", tempo_total_marcado, 100.0);
    fprintf(saida, "Diferença do total:                      %f\n", tempo_total - tempo_total_marcado);
    fprintf(saida, "Tempo leitura do arquivo:                %f (%.2f %%)\n", tempo_leitura_dados, ((tempo_leitura_dados * 100) / tempo_total_marcado));
    fprintf(saida, "Tempo do calculo de distancias:          %f (%.2f %%)\n", tempo_calculo_distancias, ((tempo_calculo_distancias * 100) / tempo_total_marcado));
    fprintf(saida, "Tempo da ordenação das distancias:       %f (%.2f %%)\n", tempo_ordenação_distancias, ((tempo_ordenação_distancias * 100.0) / tempo_total_marcado));
    fprintf(saida, "Tempo da obtenção da MST:                %f (%.2f %%)\n", tempo_obtencao_mst, ((tempo_obtencao_mst * 100.0) / tempo_total_marcado));
    fprintf(saida, "Tempo da formação dos grupos:            %f (%.2f %%)\n", tempo_identificação_grupos, ((tempo_identificação_grupos * 100.0) / tempo_total_marcado));
    fprintf(saida, "Tempo de escrita do arquivo de saida:    %f (%.2f %%)\n", tempo_escrita_saida, ((tempo_escrita_saida * 100.0) / tempo_total_marcado));

    fclose(saida);
}
