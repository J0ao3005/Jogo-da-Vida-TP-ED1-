#ifndef AUTOMATO_H
#define AUTOMATO_H

typedef struct {
    int linha;
    int coluna;
    int estado; // 1 para viva, 0 para morta
} Celula;

typedef struct {
    Celula **tabela;
    int tamanho;
    int numElementos;
} AutomatoCelular;

AutomatoCelular* alocarReticulado(int tamanho);
void desalocarReticulado(AutomatoCelular *aut);
void inserirCelula(AutomatoCelular *aut, int linha, int coluna);
void removerCelula(AutomatoCelular *aut, int linha, int coluna);
int buscarCelula(AutomatoCelular *aut, int linha, int coluna);
int contarVizinhos(AutomatoCelular *aut, int linha, int coluna);
void evoluirReticulado(AutomatoCelular *aut, int);
void imprimeReticulado(AutomatoCelular *aut, int);

#endif
