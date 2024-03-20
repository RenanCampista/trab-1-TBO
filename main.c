#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //./trab1 <nome_arquivo_entrada> k <nome_arquivo_saida>
    if (argc != 4)
        exit(printf("Error: invalid number of arguments.\n"));
    
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
        exit(printf("Error: failed to open input file.\n"));
    fclose(input);

    int groups = atoi(argv[2]);
    if (groups <= 0)
        exit(printf("Error: invalid number of groups.\n"));

    FILE *output = fopen(argv[3], "w");
    if (output == NULL)
        exit(printf("Error: failed to open output file.\n"));
    fclose(output);

    return 0;
}