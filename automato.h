#ifndef AUTOMATO_H
#define AUTOMATO_H

typedef struct{

    int **matrizPrincipal;
    int tamanhoMat;

}strDados;

int **alocarReticulado (int tamanhoMat);
void desalocarReticulado (int **reticulado, int tamanhoMat);
void leEntradaConsole(int *qntMov,strDados *dados);
void evoluirReticulado (strDados *dados, int qntMov);
void imprimeReticulado (strDados *dados);



#endif