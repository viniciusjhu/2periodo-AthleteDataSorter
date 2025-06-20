#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ordenacao.h"
#include "normalizacao.h"
#include <string.h>

// Função Bubble Sort // 

void bubble_sort(Jogador* jogadores, int n, long long int *comparacoes, long long int *trocas) {

    *trocas = 0;
    *comparacoes = 0;
    long long int trocas_local = 0;

    do {
        trocas_local = 0;
        for (int i = 0; i < n - 1; i++) {
            (*comparacoes)++;
            if (comparar_nomes_normalizada(&jogadores[i].nome, &jogadores[i + 1].nome) > 0) {
                Jogador temp = jogadores[i];
                jogadores[i] = jogadores[i + 1];
                jogadores[i + 1] = temp;
                trocas_local = 1;
            }
        }
        *trocas += trocas_local;
    } while (trocas_local > 0);

}

// Funções do Merge Sort //

void merge(Jogador* jogadores, int inicio, int meio, int fim, long long int *comparacoes, long long int *trocas) {

    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    (*comparacoes) = 0;
    (*trocas) = 0;

    Jogador* esquerda = (Jogador*) malloc(n1 * sizeof(Jogador));
    Jogador* direita = (Jogador*) malloc(n2 * sizeof(Jogador));

    if (!esquerda || !direita) {
        puts("Erro ao alocar memória para merge");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++) {
        esquerda[i] = jogadores[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        direita[j] = jogadores[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {

        (*comparacoes)++;

        if (comparar_nomes_normalizada(&esquerda[i].nome, &direita[j].nome) <= 0) {
            jogadores[k] = esquerda[i];
            i++;
            (*trocas)++;
        } else {
            jogadores[k] = direita[j];
            j++;
            (*trocas)++;
        }
        k++;
    }

    while (i < n1) {
        jogadores[k] = esquerda[i];
        i++;
        k++;

    }

    while (j < n2) {
        jogadores[k] = direita[j];
        j++;
        k++;

    }

    free(esquerda);
    free(direita);

}

void merge_sort(Jogador* jogadores, int inicio, int fim, long long int *comparacoes, long long int *trocas) {

    long long int comparacoes_esquerda = 0;
    long long int trocas_esquerda = 0;
    long long int comparacoes_direita = 0;
    long long int trocas_direita = 0;
    long long int comparacoes_merge = 0;
    long long int trocas_merge = 0;

    if (inicio < fim) {

        int meio = inicio + (fim - inicio) / 2;
        merge_sort(jogadores, inicio, meio, &comparacoes_esquerda, &trocas_esquerda);
        merge_sort(jogadores, meio + 1, fim, &comparacoes_direita, &trocas_direita);
        merge(jogadores, inicio, meio, fim, &comparacoes_merge, &trocas_merge);
    }

    *comparacoes = comparacoes_esquerda + comparacoes_direita + comparacoes_merge;
    *trocas = trocas_esquerda + trocas_direita + trocas_merge;

}


// Função de Radix Sort //

void radix_sort(Jogador* jogadores, int n, long long int *comparacoes, long long int *trocas) {

    *comparacoes = 0; // Radix Sort não faz comparações diretas
    *trocas = 0;

    char** nomes_normalizados = malloc(n * sizeof(char*)); // Copia dos nomes normalizados

    if (!nomes_normalizados) {
        perror("Erro ao alocar memória para nomes_normalizados.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        nomes_normalizados[i] = malloc((strlen(jogadores[i].nome) + 1) * sizeof(char));

        if (!nomes_normalizados[i]) {

            perror("Erro ao alocar memória para nomes_normalizados[i].");
            exit(EXIT_FAILURE);
        }
        strcpy(nomes_normalizados[i], jogadores[i].nome);
        normalizar_string(nomes_normalizados[i]); // Normalizar o nome

    }

    int max_len = 0;

    for (int i = 0; i < n; i++) {
        int len = strlen(nomes_normalizados[i]);
        if (len > max_len) {
            max_len = len;
        }

    }

    // Alocando e inicializando o vetor de índices

    int * indices = malloc(n*sizeof(int));

    if (!indices) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    for(int i = 0; i < n; i++){
        indices[i] = i;
    }

    Jogador* temp = malloc(n * sizeof(Jogador));

    if (!temp) {
        perror("Erro ao alocar memória para array temporário.");
        exit(EXIT_FAILURE);
    }

    // Radix Sort usando os índices
    for (int pos = max_len - 1; pos >= 0; pos--) {

        int count[257] = {0};

        for (int i = 0; i < n; i++) {

            int indice_jogador = indices[i];

            unsigned char char_at_pos = (pos < strlen(nomes_normalizados[indice_jogador]))
                                ? (unsigned char)tolower(nomes_normalizados[indice_jogador][pos]) + 1
                                : 0;
            count[char_at_pos]++;
        }

        for (int i = 1; i < 257; i++) {
            count[i] += count[i - 1];
        }

        // Reordenando os índices

        int* temp_indices = malloc(n * sizeof(int));

        if (!temp_indices) {
            perror("Erro de alocação de memória.");
            exit(1);
        }

        for (int i = n - 1; i >= 0; i--) {

            int indice_jogador = indices[i];

            unsigned char char_at_pos = (pos < strlen(nomes_normalizados[indice_jogador]))
                                ? (unsigned char)tolower(nomes_normalizados[indice_jogador][pos]) + 1
                                : 0;
            temp_indices[count[char_at_pos] - 1] = indice_jogador;
            count[char_at_pos]--;
        }

        for(int i = 0; i < n; i++){
            indices[i] = temp_indices[i];
        }

        free(temp_indices);
    }

    // Reordenando o array original com base nos índices ordenados

    for (int i = 0; i < n; i++) {

        temp[i] = jogadores[indices[i]];
        if(indices[i] != i)(*trocas)++;
    }

    for (int i = 0; i < n; i++) {
        jogadores[i] = temp[i];
    }

    // Liberando memórias alocadas
    free(temp);
    for (int i = 0; i < n; i++) {
        free(nomes_normalizados[i]);
    }

    free(nomes_normalizados);
    free(indices);
}