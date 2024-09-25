//Luis Filipe Silva Forti - 14592348
//Lucien Rodrigues Franzen - 14554835

//Trabalho 1 de ED3

#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes_fornecidas.h"
#include "funcoes_auxiliares.h"
#include "dinossauro.h"

//Struct para armazenar dados do cabeçalho dos arquivos
typedef struct cabecalho
{
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} Cabecalho;

//Lê o cabeçalho (apenas chamado pelo AbrirArquivo)
void LerCabecalho(FILE *arq);
//Escreve o cabeçalho salvo em cab
void EscreverCabecalho(FILE *arq, char naoEstaNoComeco);

//Cria um arquivo com cabeçalho no endereço passado
FILE* CriarArquivo(char* endereco);
//Cria um arquivo no endereço passado e lê o cabeçalho
FILE* AbrirArquivo(char* endereco);
//Fecha o arquivo no endereço passado e atualiza o cabeçalho
void FecharArquivo(FILE* arq, char* endereco);

//Modifica a string passada para salvar de acordo com as definições do projeto
int SalvarStringRegistro(char* str, FILE* arq);
//Salva o dino passado, seguindo as definições do projeto
void SalvarRegistro(Dinossauro dino, FILE* arq);

//Define qual o tipo de remoção (qual atributo de Dinossauro)
int TipoAchado(char* comando);
//Encontra o RRN do primeiro registro >= RRNinicial
//Devem serem passados o arquivo, o RRNinicial (onde começar a busca),
//o idBusca (qual atributo de Dinossauro) e o valS (valor do atributo procurado)
int EncontrarRRN(FILE* arq, int RRNinicial, int idBusca, char* valS);

//Cria a tabela usando os endereços de entrada e saída
void CreateTable(char* enderecoE, char* enderecoS);
//Imprime os dados dos registros da tabela enderecoE não removidos logicamente
void SelectTable(char* enderecoE);
//Remove logicamente um número de registros em enderecoE igual à qtd
void RemoverRegistros(char* enderecoE, int qtd);
//Insere um número de registros em enderecoE igual à qtd
//Ele irá salvar no local do último registro removido, ou então adicionará no final
void InsertInto(char* enderecoS, int qtd);

void AcharRegistros(char* enderecoE, int qtd); //Acha registros de acordo com campo pedido
void Compactar(char* enderecoE);

#endif // CONTROLADOR_H_INCLUDED
