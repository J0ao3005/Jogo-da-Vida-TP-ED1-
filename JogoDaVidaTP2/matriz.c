#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "matriz.h"

void insereCelula(AutomatoCelular *aut, int linha, int coluna) {
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->linha = linha;
    nova->coluna = coluna;
    nova->proxLinha = aut->linhas[linha];
    aut->linhas[linha] = nova;

    nova->proxColuna = aut->colunas[coluna];
    aut->colunas[coluna] = nova;
}

void removeCelula(AutomatoCelular *aut, int linha, int coluna) {
    Celula **atual = &(aut->linhas[linha]);
    while (*atual != NULL && (*atual)->coluna != coluna) {
        atual = &((*atual)->proxLinha);
    }
    if (*atual != NULL) {
        Celula *remover = *atual;
        *atual = remover->proxLinha;

        atual = &(aut->colunas[coluna]);
        while (*atual != NULL && (*atual)->linha != linha) {
            atual = &((*atual)->proxColuna);
        }
        if (*atual != NULL) {
            *atual = remover->proxColuna;
        }
        free(remover);
    }
}

int contaVizinhos(AutomatoCelular *aut, int linha, int coluna) {
    int vizinhos = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int novaLinha = linha + i;
            int novaColuna = coluna + j;
            if (novaLinha >= 0 && novaLinha < aut->dimensao && novaColuna >= 0 && novaColuna < aut->dimensao) {
                Celula *atual = aut->linhas[novaLinha];
                while (atual != NULL) {
                    if (atual->coluna == novaColuna) {
                        vizinhos++;
                        break;
                    }
                    atual = atual->proxLinha;
                }
            }
        }
    }
    return vizinhos;
}

int** alocarMatriz(int dimensao) {
    int **matriz = (int **)malloc(dimensao * sizeof(int *));
    for (int i = 0; i < dimensao; i++) {
        matriz[i] = (int *)malloc(dimensao * sizeof(int));
        for (int j = 0; j < dimensao; j++) {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void desalocarMatriz(int **matriz, int dimensao) {
    for (int i = 0; i < dimensao; i++) {
        free(matriz[i]);
    }
    free(matriz);
}


void VetorOla(int *vetor1, int *vetor2) {
    for (; (*vetor1 = *vetor2) != '\0'; *vetor1++, *vetor2--)
    {
    }   
}