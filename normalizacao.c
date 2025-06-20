#include "normalizacao.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structJogadores.h"

void normalizar_string(char *str) {
    
    unsigned char *s = (unsigned char *)str;

    while (*s) {

        // 1. Remover acentos PRIMEIRO
        if (strchr("àáâãäÀÁÂÃÄ", *s)) {
            *s = 'a';
        } else if (strchr("éèêëÉÈÊË", *s)) {
            *s = 'e';
        } else if (strchr("íìîïÍÌÎÏ", *s)) {
            *s = 'i';
        } else if (strchr("óòõôöÓÒÕÔÖ", *s)) {
            *s = 'o';
        } else if (strchr("úùûüÚÙÛÜ", *s)) {
            *s = 'u';
        } else if (strchr("çÇ", *s)) {
            *s = 'c';
        } else if (strchr("ñÑ", *s)) {
            *s = 'n';
        } else if (strchr("ýÿÝ", *s)) {
            *s = 'y';
        } else if (strchr("šŠ", *s)) {
            *s = 's';
        } else if (strchr("žŽ", *s)) {
            *s = 'z';
        } else if (strchr("ğĞ", *s)) {
            *s = 'g';
        } else if (strchr("şŞ", *s)) {
            *s = 's';
        } else if (strchr("ıİ", *s)) {
            *s = 'i';
        }

        // 2. Converter para minúscula DEPOIS
        *s = tolower(*s);
        
        s++;
    }

}

int comparar_nomes_normalizada(const void *a, const void *b) {
    const Jogador *j1 = (const Jogador *)a;
    const Jogador *j2 = (const Jogador *)b;

    const unsigned char *s1 = (const unsigned char *)j1->nome;
    const unsigned char *s2 = (const unsigned char *)j2->nome;

    while (*s1 && *s2) {
        unsigned char c1 = *s1;
        unsigned char c2 = *s2;

        // Normalização apenas para comparação
        unsigned char nc1 = tolower(c1);
        unsigned char nc2 = tolower(c2);

        // Usando strchr para todos os caracteres especiais
        if (strchr("áàãâä", nc1)) nc1 = 'a';
        if (strchr("áàãâä", nc2)) nc2 = 'a';
        if (strchr("éèêë", nc1)) nc1 = 'e';
        if (strchr("éèêë", nc2)) nc2 = 'e';
        if (strchr("íìîï", nc1)) nc1 = 'i';
        if (strchr("íìîï", nc2)) nc2 = 'i';
        if (strchr("óòöôõ", nc1)) nc1 = 'o';
        if (strchr("óòöôõ", nc2)) nc2 = 'o';
        if (strchr("úùü", nc1)) nc1 = 'u';
        if (strchr("úùü", nc2)) nc2 = 'u';
        if (strchr("ç", nc1)) nc1 = 'c';
        if (strchr("ç", nc2)) nc2 = 'c';
        if (strchr("ñ", nc1)) nc1 = 'n';
        if (strchr("ñ", nc2)) nc2 = 'n';
        if (strchr("İ", nc1)) nc1 = 'i';
        if (strchr("İ", nc2)) nc2 = 'i';
        if (strchr("ı", nc1)) nc1 = 'i';
        if (strchr("ı", nc2)) nc2 = 'i';
        if (strchr("Ğ", nc1)) nc1 = 'g';
        if (strchr("Ğ", nc2)) nc2 = 'g';
        if (strchr("ğ", nc1)) nc1 = 'g';
        if (strchr("ğ", nc2)) nc2 = 'g';
        if (strchr("şŞ", nc1)) nc1 = 's';
        if (strchr("şŞ", nc2)) nc2 = 's';
        if (strchr("çÇ", nc1)) nc1 = 'c';
        if (strchr("çÇ", nc2)) nc2 = 'c';


        if (nc1 != nc2) {
            return (int)nc1 - (int)nc2;
        }

        s1++;
        s2++;
    }

    return (int)*s1 - (int)*s2;
}