#include "double_hash.h"

#define PESOS1 {1, 2}
#define PESOS2 {3, 4}

int hash1(int linha, int coluna, int tamanho) {
    int pesos[] = PESOS1;
    int hash = (pesos[0] * linha + pesos[1] * coluna) % tamanho;
    return (hash < 0) ? hash + tamanho : hash;  // Garante que o resultado seja positivo
}

int hash2(int linha, int coluna, int tamanho) {
    int pesos[] = PESOS2;
    int hash = (pesos[0] * linha + pesos[1] * coluna) % (tamanho - 1);
    if (hash < 0) {
        hash += (tamanho - 1);  // Garante que o resultado seja positivo
    }
    return (hash == 0) ? 1 : hash;  // Garante que o hash2 nunca seja 0
}
