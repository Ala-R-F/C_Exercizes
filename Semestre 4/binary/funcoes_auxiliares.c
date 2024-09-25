//Luis Filipe Silva Forti - 14592348
//Lucien Rodrigues Franzen - 14554835

//Trabalho 1 de ED3

#include "funcoes_auxiliares.h"

//Separa os dados de entrada no intervalo nroDado entre dois sep, salvando em saida
void SepararDado(char* entrada, char* saida, int nroDado, char sep)
{
    //Quantidade de caracteres na string
    int tam = strlen(entrada);
    //Valores auxiliares
    int pos = 0, qtdSep = 0, aux = 0;

    //Enquanto não chegar no fim e não encontra o intervalo desejado
    for(int i = 0; i < tam && qtdSep < nroDado; i++)
    {
        //Se encontrou um dos separadores
        if(entrada[i] == sep)
            //Avança em 1 intervalo
            qtdSep++;
        //Avança a posição
        pos++;
    }

    //Enquanto não chegar no próximo intervalo ou encontrar um caractere indesejado
    while(entrada[pos] != sep && entrada[pos] != '\r' &&
           entrada[pos] != '\n' && entrada[pos] != '\0')
    {
        //Salva o caractere atual
        saida[aux] = entrada[pos];

        //Avança as posições
        pos++;
        aux++;
    }
    //Adiciona o \0 final
    saida[aux] = '\0';
}
