#ifndef AUTOMATO_H
#define AUTOMATO_H

typedef struct Celula {
    int linha;
    int coluna;
    struct Celula *proxLinha;
    struct Celula *proxColuna;
} Celula;

typedef struct {
    int dimensao;
    Celula **linhas;
    Celula **colunas;
} AutomatoCelular;

AutomatoCelular* alocarReticulado(int dimensao);
void desalocarReticulado(AutomatoCelular *aut);
void leituraReticulado(AutomatoCelular *aut, int **matrizInicial);
void evoluirReticulado(AutomatoCelular *aut);
void imprimeReticulado(AutomatoCelular *aut);

#endif
