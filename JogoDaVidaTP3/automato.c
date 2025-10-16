#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "double_hash.h"

AutomatoCelular* alocarReticulado(int tamanho) {
    AutomatoCelular *aut = (AutomatoCelular *)malloc(sizeof(AutomatoCelular));
    aut->tamanho = tamanho;
    aut->numElementos = 0;
    aut->tabela = (Celula **)calloc(tamanho, sizeof(Celula *));  // Certificando que todas as posições estão nulas
    return aut;
}

void desalocarReticulado(AutomatoCelular *aut) {
    for (int i = 0; i < aut->tamanho; i++) {
        if (aut->tabela[i] != NULL) {
            free(aut->tabela[i]);
        }
    }
    free(aut->tabela);
    free(aut);
}

void inserirCelula(AutomatoCelular *aut, int linha, int coluna) {
    int tamanho = aut->tamanho;
    int h1 = hash1(linha, coluna, tamanho);
    int h2 = hash2(linha, coluna, tamanho);

    for (int i = 0; i < tamanho; i++) {
        int pos = (h1 + i * h2) % tamanho;

        // Verificando se a posição está dentro dos limites
        if (pos < 0 || pos >= tamanho) {
            printf("Erro: índice fora dos limites (%d).\n", pos);
            return;
        }

        if (aut->tabela[pos] == NULL) {  // Se a posição está livre, insira a célula
            Celula *nova = (Celula *)malloc(sizeof(Celula));
            if (!nova) {
                printf("Erro: falha ao alocar célula.\n");
                return;
            }
            nova->linha = linha;
            nova->coluna = coluna;
            nova->estado = 1;  // Viva
            aut->tabela[pos] = nova;
            aut->numElementos++;
            return;
        }
    }

    // Caso a tabela esteja cheia (não deveria acontecer, mas é uma verificação extra)
    printf("Erro: tabela hash cheia! Não foi possível inserir a célula (%d, %d).\n", linha, coluna);
}


void removerCelula(AutomatoCelular *aut, int linha, int coluna) {
    int tamanho = aut->tamanho;
    int h1 = hash1(linha, coluna, tamanho);
    int h2 = hash2(linha, coluna, tamanho);

    for (int i = 0; i < tamanho; i++) {
        int pos = (h1 + i * h2) % tamanho;
        if (aut->tabela[pos] != NULL && aut->tabela[pos]->linha == linha && aut->tabela[pos]->coluna == coluna) {
            free(aut->tabela[pos]);
            aut->tabela[pos] = NULL;
            aut->numElementos--;
            return;
        }
    }
}

int buscarCelula(AutomatoCelular *aut, int linha, int coluna) {
    int tamanho = aut->tamanho;
    int h1 = hash1(linha, coluna, tamanho);
    int h2 = hash2(linha, coluna, tamanho);

    for (int i = 0; i < tamanho; i++) {
        int pos = (h1 + i * h2) % tamanho;

        if (pos < 0 || pos >= tamanho) {
            printf("Erro: índice fora dos limites ao buscar célula (%d).\n", pos);
            return 0;  // Retornamos 0 (morta) se o índice estiver fora dos limites
        }

        if (aut->tabela[pos] != NULL && aut->tabela[pos]->linha == linha && aut->tabela[pos]->coluna == coluna) {
            return 1;  // Célula viva
        }
    }
    return 0;  // Célula morta
}


int contarVizinhos(AutomatoCelular *aut, int linha, int coluna) {
    int vizinhos = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            vizinhos += buscarCelula(aut, linha + i, coluna + j);
        }
    }
    return vizinhos;
}

void evoluirReticulado(AutomatoCelular *aut, int dimensao) {
    AutomatoCelular *novoAut = alocarReticulado(aut->tamanho);  // Tamanho é o mesmo do aut atual
    
    // Verificações de limites e inicialização
    if (!novoAut || !aut) {
        printf("Erro: falha ao alocar reticulado.\n");
        return;
    }
    
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            int vizinhos = contarVizinhos(aut, i, j);
            int viva = buscarCelula(aut, i, j);

            // Aplicando as regras do jogo da vida
            if (vizinhos == 3 || (vizinhos == 2 && viva)) {
                inserirCelula(novoAut, i, j);
            }
        }
    }

    // Desalocamos apenas a tabela antiga, não o aut
    Celula **tabelaAntiga = aut->tabela;
    aut->tabela = novoAut->tabela;  // Substituímos a tabela pelo novo estado evoluído
    aut->numElementos = novoAut->numElementos;  // Atualizamos o número de células

    free(tabelaAntiga);  // Liberamos a tabela antiga
    free(novoAut);  // Liberamos a estrutura temporária de novoAut
}



void imprimeReticulado(AutomatoCelular *aut, int dimensao) {
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            // Verifica se a célula (i, j) está viva
            if (buscarCelula(aut, i, j)) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");  // Quebra de linha para a próxima linha do reticulado
    }
}
