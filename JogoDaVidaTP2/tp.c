#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "matriz.h"



int main() {
    int dimensao, geracoes;
    scanf("%d %d", &dimensao, &geracoes);

    int **matrizInicial = alocarMatriz(dimensao);
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            scanf("%d", &matrizInicial[i][j]);
        }
    }

    AutomatoCelular *aut = alocarReticulado(dimensao);
    leituraReticulado(aut, matrizInicial);
    desalocarMatriz(matrizInicial, dimensao);

    for (int i = 0; i < geracoes; i++) {
        evoluirReticulado(aut);
    }

    imprimeReticulado(aut);
    desalocarReticulado(aut);

    return 0;
}