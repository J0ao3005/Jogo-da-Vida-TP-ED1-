#ifndef MATRIZ_H
#define MATRIZ_H

void insereCelula(AutomatoCelular *aut, int linha, int coluna);
void removeCelula(AutomatoCelular *aut, int linha, int coluna);
int contaVizinhos(AutomatoCelular *aut, int linha, int coluna);
int** alocarMatriz(int dimensao);
void desalocarMatriz(int **matriz, int dimensao);

#endif
