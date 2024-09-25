//Luis Filipe Silva Forti - 14592348
//Lucien Rodrigues Franzen - 14554835

//Trabalho 1 de ED3

#ifndef DINOSSAURO_H_INCLUDED
#define DINOSSAURO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes_fornecidas.h"
#include "funcoes_auxiliares.h"

//Struct para armazenamento dos registros
typedef struct dinossauro
{
    char removido;
    int encadeamento;
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    char* nome;
    char* especie;
    char* habitat;
    char* tipo;
    char* dieta;
    char* alimento;
} Dinossauro;

//Cria um dinossauro com valores nulos
Dinossauro CriaDinossauro();
//Cria um dinossauro com uma entrada de um CSV
Dinossauro CriaDinossauroCSV(FILE* arq);
//Cria um dinossauro à partir da posição do cursor no arquivo entrada
Dinossauro CriaDinossauroBin(FILE* entrada);
//Libera o espaço alocado para dino
void LiberaDinossauro(Dinossauro dino);
//Imprime dino na tela
void ImprimeDinossauro(Dinossauro dino);

#endif // DINOSSAURO_H_INCLUDED
