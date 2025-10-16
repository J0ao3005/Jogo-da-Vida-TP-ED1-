#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main (int argc, char *argv[]){

    int qntMov;
    strDados dados;

    leEntradaConsole(&qntMov, &dados);

    evoluirReticulado(&dados, qntMov);
    imprimeReticulado(&dados);

    desalocarReticulado(dados.matrizPrincipal, dados.tamanhoMat);

    return 0;
}
