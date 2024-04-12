- 1 = tempo_leitura
Marcar o tempo na chamada cartesian_plane_read() que fica na main

- 2 = tempo_calculo_distancias
Chamada da função point_euclidean_distance(). Ela é chamada diversas vezes, então vai somando o valor.

- 3 = tempo_ordenação_distancias
Marcar o tempo do qsort()


- 4 = tempo_obtenção_mst
Marcar o tempo na chamada da função process_edges() que fica dentro de kruskal_solve()


- 5 = tempo_ident_grupos
/*Ideia anterior*/
Marcar o tempo em volta do if() dentro da função process_edges(). Sera um somatorio.
/*Na verdade nosso programa identifica os grupos apenas no momento de impressão, pois nao usamos estruturas para salvar os grupos, apenas percorremos a arvores e imprimimos os pontos que estão no memsmo grupo. No relatorio poderia ser dito que identificamos os grupos apenas no momento de imprimir. Antes disso so temos a arvore*/

/*Ideia atual*/
Marcar o tempo dentro da função de impressão, na parte que imprimimos o elementos do /*mesmo grupo*/


- 6 = tempo_escrita_saida
Chamada da função cartesian_plane_qsort(cp) e da função kruskal_print_groups_and_destroy(). Somar o tempo das duas funções.