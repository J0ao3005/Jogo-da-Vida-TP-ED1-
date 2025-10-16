#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main() {
    int dimensao, geracoes;
    scanf("%d %d", &dimensao, &geracoes);

    AutomatoCelular *aut = alocarReticulado(dimensao * dimensao * 2);

    // Leitura do estado inicial
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            int estado;
            scanf("%d", &estado);
            if (estado == 1) {
                inserirCelula(aut, i, j);
            }
        }
    }

    // Evolução do reticulado
    for (int i = 0; i < geracoes; i++) {
        evoluirReticulado(aut, dimensao);  // Passando a dimensão para evoluirReticulado
    }

    // Impressão do resultado
    imprimeReticulado(aut, dimensao);  // Passando a dimensão para imprimeReticulado

    desalocarReticulado(aut);  // Libera a memória
    return 0;
}
