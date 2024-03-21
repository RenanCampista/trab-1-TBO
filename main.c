#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //./trab1 <nome_arquivo_entrada> k <nome_arquivo_saida>
    if (argc != 4)
        exit(printf("Error: invalid number of arguments.\n"));
    
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
        exit(printf("Error: failed to open input file.\n"));

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *token;
    int dimension = 0;

    if ((read = getline(&line, &len, input)) == -1)
        exit(printf("Error: input file is empty.\n"));

    // Remove o caractere de nova linha (\n) do final da linha
    line[strcspn(line, "\n")] = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ',') {
            dimension++;
        }
    }

    // Retorna ao início do arquivo para processar novamente
    fseek(input, 0, SEEK_SET);

    //pegar um vector para armazenar os points
    

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