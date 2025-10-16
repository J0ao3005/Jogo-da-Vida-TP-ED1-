#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "matriz.h"

AutomatoCelular* alocarReticulado(int dimensao) {
    AutomatoCelular *aut = (AutomatoCelular *)malloc(sizeof(AutomatoCelular));
    aut->dimensao = dimensao;
    aut->linhas = (Celula **)malloc(dimensao * sizeof(Celula *));
    aut->colunas = (Celula **)malloc(dimensao * sizeof(Celula *));
    for (int i = 0; i < dimensao; i++) {
        aut->linhas[i] = NULL;
        aut->colunas[i] = NULL;
    }
    return aut;
}

void desalocarReticulado(AutomatoCelular *aut) {
    for (int i = 0; i < aut->dimensao; i++) {
        Celula *linhaAtual = aut->linhas[i];
        while (linhaAtual != NULL) {
            Celula *prox = linhaAtual->proxLinha;
            free(linhaAtual);
            linhaAtual = prox;
        }
    }
    free(aut->linhas);
    free(aut->colunas);
    free(aut);
}

void leituraReticulado(AutomatoCelular *aut, int **matrizInicial) {
    for (int i = 0; i < aut->dimensao; i++) {
        for (int j = 0; j < aut->dimensao; j++) {
            if (matrizInicial[i][j] == 1) {
                insereCelula(aut, i, j);
            }
        }
    }
}

void evoluirReticulado(AutomatoCelular *aut) {
    int dimensao = aut->dimensao;
    int **novaMatriz = alocarMatriz(dimensao);

    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            int vizinhos = contaVizinhos(aut, i, j);
            Celula *atual = aut->linhas[i];
            int viva = 0;
            while (atual != NULL) {
                if (atual->coluna == j) {
                    viva = 1;
                    break;
                }
                atual = atual->proxLinha;
            }
            if (vizinhos == 3 || (vizinhos == 2 && viva)) {
                novaMatriz[i][j] = 1;
            } else {
                novaMatriz[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            if (novaMatriz[i][j] == 1) {
                insereCelula(aut, i, j);
            } else {
                removeCelula(aut, i, j);
            }
        }
    }

    desalocarMatriz(novaMatriz, dimensao);
}

void imprimeReticulado(AutomatoCelular *aut) {

    printf("\n");
    for (int i = 0; i < aut->dimensao; i++) {
        for (int j = 0; j < aut->dimensao; j++) {
            Celula *atual = aut->linhas[i];
            int encontrada = 0;
            while (atual != NULL) {
                if (atual->coluna == j) {
                    printf("1 ");
                    encontrada = 1;
                    break;
                }
                atual = atual->proxLinha;
            }
            if (!encontrada) {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
