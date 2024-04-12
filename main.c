#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartesian_plane.h"
#include "kruskal.h"

int main(int argc, char *argv[]) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    //./trab1 <nome_arquivo_entrada> k <nome_arquivo_saida>
    if (argc != 4)
        exit(printf("Error: invalid number of arguments.\n"));
    
    CartesianPlane *cp = cartesian_plane_construct();
    cartesian_plane_read(cp, argv[1]);
    
    int groups = atoi(argv[2]);
    if (groups <= 0 || groups > cartesian_plane_get_number_points(cp))
        exit(printf("Error: invalid number of groups.\n"));
  
    Kruskal *kr = kruskal_solve(cp, groups);
    kruskal_print_groups(kr, argv[3]);
    kruskal_destroy(kr);
    cartesian_plane_destroy(cp);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    FILE *time_file = fopen("runtime.txt", "w");
    if (time_file == NULL)
        exit(printf("Error: could not open runtime file.\n"));
    fprintf(time_file, "Program executed in %f seconds\n", cpu_time_used);
    fclose(time_file);

    return 0;
}