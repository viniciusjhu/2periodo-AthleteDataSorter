#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "structJogadores.h"

void bubble_sort(Jogador* jogadores, int n, long long int *comparacoes, long long int *trocas);
void merge_sort(Jogador* jogadores, int inicio, int fim, long long int *comparacoes, long long int *trocas);
void merge(Jogador* jogadores, int inicio, int meio, int fim, long long int *comparacoes, long long int *trocas);
void radix_sort(Jogador* jogadores, int n, long long int *comparacoes, long long int *trocas);

#endif