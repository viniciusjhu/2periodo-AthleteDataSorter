#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lerJogadores.h"

Jogador* ler_jogadores(const char *nome_arquivo, int *num_jogadores) {

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    // Contar o número de jogadores (linhas no arquivo, menos o cabeçalho)
    *num_jogadores = 0;
    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Descartar cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        (*num_jogadores)++;
    }

    fseek(arquivo, 0, SEEK_SET); // Voltar ao início do arquivo
    fgets(linha, sizeof(linha), arquivo); // Descartar cabeçalho novamente

    Jogador* jogadores = (Jogador*) malloc(*num_jogadores * sizeof(Jogador));
    
    if (!jogadores) {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < *num_jogadores; i++) {
        if(fgets(linha, sizeof(linha), arquivo)){
            sscanf(linha, "%99[^,],%49[^,],%49[^,],%49[^,],%d", 
                   jogadores[i].nome, jogadores[i].posicao, jogadores[i].naturalidade,
                   jogadores[i].clube, &jogadores[i].idade);
        } else {
             // Lidar com erro de leitura (como linha incompleta)
             fprintf(stderr, "Erro de leitura na linha %d\n", i + 2); // +2 para contar cabeçalho e índice base 0
             free(jogadores);
             fclose(arquivo);
             return NULL;
        }
    }

    fclose(arquivo);
    return jogadores;

}

void liberar_jogadores(Jogador* jogadores) {
    free(jogadores);
}