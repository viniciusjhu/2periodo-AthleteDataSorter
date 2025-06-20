#include <stdio.h>
#include <stdlib.h>
#include "tempo.h"

double calcular_tempo(clock_t inicio, clock_t fim) {

    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;
    
}