#ifndef LERJOGADORES_H
#define LERJOGADORES_H

#include "structJogadores.h"
Jogador* ler_jogadores(const char *nome_arquivo, int *num_jogadores);
void liberar_jogadores(Jogador* jogadores);

#endif