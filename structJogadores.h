#ifndef STRUCTJOGADORES_H
#define STRUCTJOGADORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char posicao[50];
    char naturalidade[50];
    char clube[50];
    int idade;
} Jogador;

#endif