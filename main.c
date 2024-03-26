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
    cartesian_plane_calculate_distances(cp);

    int groups = atoi(argv[2]);
    if (groups <= 0)
        exit(printf("Error: invalid number of groups.\n"));
  
    kruskal_solve(cp, groups, argv[3]);
    cartesian_plane_destroy(cp);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    FILE *time_file = fopen("runtime.txt", "w");
    if (time_file == NULL)
        exit(printf("Error: could not open runtime file.\n"));
    fprintf(time_file, "%.3f\n", cpu_time_used);
    fclose(time_file);

    return 0;
}