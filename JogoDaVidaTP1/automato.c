#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

void desalocarReticulado (int **reticulado, int tamanhoMat){
    for(int i = 0; i < tamanhoMat; i++){
        free(reticulado[i]);
    }
    free(reticulado);
}

int **alocarReticulado (int tamanhoMat){

    int **matrizAux;
    matrizAux = (int **) malloc (tamanhoMat * sizeof(int*));
    for(int i = 0; i < tamanhoMat; i++){
        matrizAux[i] = (int *) malloc ( tamanhoMat * sizeof(int));
    }

    return matrizAux;

}

void leEntradaConsole (int *qntMov, strDados *dados){
    scanf("%d", &dados->tamanhoMat);
    scanf("%d", qntMov);

    dados->matrizPrincipal = alocarReticulado(dados->tamanhoMat);

    for(int i = 0; i < dados->tamanhoMat; i++) {
        for(int j = 0; j < dados->tamanhoMat; j++) {
            scanf("%d", &dados->matrizPrincipal[i][j]);
        }
    }
}

void evoluirReticulado (strDados *dados, int qntMov){

    int tamanhoMat = dados->tamanhoMat;

    for (int geracao = 0; geracao < qntMov; geracao++) {
        int **novaMatriz = alocarReticulado(tamanhoMat);

        for (int i = 0; i < tamanhoMat; i++) {
            for (int j = 0; j < tamanhoMat; j++) {
                int vivos = 0;

                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x == 0 && y == 0) continue;
                        int ni = i + x, nj = j + y;
                        if (ni >= 0 && ni < tamanhoMat && nj >= 0 && nj < tamanhoMat) {
                            vivos += dados->matrizPrincipal[ni][nj];
                        }
                    }
                }

                if (dados->matrizPrincipal[i][j] == 1) {
                    if (vivos < 2 || vivos > 3) {
                        novaMatriz[i][j] = 0;
                    } else {
                        novaMatriz[i][j] = 1;
                    }
                } else {
                    if (vivos == 3) {
                        novaMatriz[i][j] = 1;
                    } else {
                        novaMatriz[i][j] = 0;
                    }
                }
            }
        }

        desalocarReticulado(dados->matrizPrincipal, tamanhoMat);
        dados->matrizPrincipal = novaMatriz;
    }
}

void imprimeReticulado(strDados *dados){
    int tamanhoMat = dados->tamanhoMat;

    printf("\n");
    for(int i = 0; i < tamanhoMat; i++){
        for(int j = 0; j < tamanhoMat; j++){
            printf("%d ", dados -> matrizPrincipal[i][j]);
        }
        printf("\n");
    }
}
