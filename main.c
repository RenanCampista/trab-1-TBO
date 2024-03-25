#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "cartesian_plane.h"
#include "kruskal.h"

int main(int argc, char *argv[]) {
    //./trab1 <nome_arquivo_entrada> k <nome_arquivo_saida>
    if (argc != 4)
        exit(printf("Error: invalid number of arguments.\n"));
    
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
        exit(printf("Error: failed to open input file.\n"));
    CartesianPlane *cp = cartesian_plane_construct();
    cartesian_plane_read(cp, input);
    fclose(input);

    cartesian_plane_calculate_distances(cp);
    //cartesian_plane_print_distances(cp);
    
    
    int groups = atoi(argv[2]);
    if (groups <= 0)
        exit(printf("Error: invalid number of groups.\n"));

    Kruskal *k = kruskal_construct(cp);
    kruskal_solve(k, groups);
    kruskal_destroy(k);

    cartesian_plane_destroy(cp);
    FILE *output = fopen(argv[3], "w");
    if (output == NULL)
        exit(printf("Error: failed to open output file.\n"));
    fclose(output);

    return 0;
}