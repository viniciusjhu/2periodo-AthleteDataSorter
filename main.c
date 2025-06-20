/* TP3 da disciplina de AEDS II

Nome: Vinicius Ribeiro da Silva do Carmo (2023.2.08.003)
Nome: Maria Cláudia Pio Ramos (2023.2.08.002)

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lerJogadores.h"
#include "ordenacao.h"
#include "tempo.h"
#include "structJogadores.h"
#include "normalizacao.h"

int main(int argc, char *argv[]) {

    long long int comparacoes = 0; // "long int" para acomodar potencialmente grandes números de operações
    long long int trocas = 0;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <metodo_ordenacao>\n", argv[0]);
        fprintf(stderr, "Onde <metodo_ordenacao> é:\n");
        fprintf(stderr, "1 - Bubble Sort\n");
        fprintf(stderr, "2 - Merge Sort\n");
        fprintf(stderr, "3 - Radix Sort\n");
        return 1;
    }


    int metodo = atoi(argv[1]);
    if (metodo < 1 || metodo > 3) {
        fprintf(stderr, "Método de ordenação inválido.\n");
        return 1;
    }

    int num_jogadores;

    Jogador* jogadores = ler_jogadores("jogadores.csv", &num_jogadores);
    if (!jogadores) {
        return 1; 
    }

    clock_t inicio, fim;
    double tempo_gasto;

    size_t memoria_gasta = num_jogadores * sizeof(Jogador);

    switch (metodo) {

        case 1:

            inicio = clock();
            bubble_sort(jogadores, num_jogadores, &comparacoes, &trocas);
            fim = clock();

        break;

        case 2:

            inicio = clock();
            merge_sort(jogadores, 0, num_jogadores - 1, &comparacoes, &trocas);
            fim = clock();

        break;

        case 3:

            inicio = clock();
            radix_sort(jogadores, num_jogadores, &comparacoes, &trocas);
            fim = clock();
            
        break;
    }

    tempo_gasto = calcular_tempo(inicio, fim);

    // Imprimir jogadores ordenados
    for (int i = 0; i < num_jogadores; i++) {
        printf("%s, %s, %s, %s, %d\n", jogadores[i].nome, jogadores[i].posicao,
               jogadores[i].naturalidade, jogadores[i].clube, jogadores[i].idade);
    }
    
    puts("\n");
    printf("\tNúmeros de Comparações: %lld\n", comparacoes);
    printf("\tNúmeros de Trocas: %lld\n", trocas); 
    printf("\tTempo gasto (em milisegundos): %.4lf\n", tempo_gasto);
    printf("\tMemória gasta: %.0zu\n\n", memoria_gasta);

    liberar_jogadores(jogadores);

    return 0;
}