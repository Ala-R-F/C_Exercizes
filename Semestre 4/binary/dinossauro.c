//Luis Filipe Silva Forti - 14592348
//Lucien Rodrigues Franzen - 14554835

//Trabalho 1 de ED3

#include "dinossauro.h"

//Cria um dinossauro com valores nulos
Dinossauro CriaDinossauro()
{
    Dinossauro dino;
    dino.removido = '0';
    dino.encadeamento = -1;
    dino.populacao = -1;
    dino.tamanho = -1;
    dino.unidadeMedida = '$';
    dino.velocidade = -1;
    dino.nome = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior
    dino.especie = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior
    dino.habitat = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior
    dino.tipo = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior
    dino.dieta = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior
    dino.alimento = calloc(160, sizeof(char)); //160 bytes pois é o tamanho do registro, nunca será maior

    return dino;
}

//Cria um dinossauro com uma entrada de um CSV
Dinossauro CriaDinossauroCSV(FILE* arq)
{
    //Cria um dinossauro nulo
    Dinossauro dino = CriaDinossauro();
    //String para armazenar a entrada dos dados
    char* linha = calloc(200, sizeof(char));
    //Auxiliar para separar os dados
    char* aux = calloc(200, sizeof(char));

    //Se não conseguiu ler
    if(!fgets(linha, 200, arq))
    {
        //Define que acabou o arquivo
        dino.removido = 'E';
        //Libera os espaços alocados
        free(linha);
        free(aux);
        //Retorna o dino
        return dino;
    }

    //Separa os dados pedidos da linha
    //Quando necessário, confere se realmente foi passado um valor

    SepararDado(linha, dino.nome, 0, ',');
    SepararDado(linha, dino.dieta, 1, ',');
    SepararDado(linha, dino.habitat, 2, ',');

    SepararDado(linha, aux, 3, ',');
    if(strcmp(aux, "") != 0)
        dino.populacao = atoi(aux);

    SepararDado(linha, dino.tipo, 4, ',');

    SepararDado(linha, aux, 5, ',');
    if(strcmp(aux, "") != 0)
        dino.velocidade = atoi(aux);

    SepararDado(linha, aux, 6, ',');
    if(strcmp(aux, "") != 0)
        dino.unidadeMedida = aux[0];

    SepararDado(linha, aux, 7, ',');
    if(strcmp(aux, "") != 0)
        dino.tamanho = atof(aux);

    SepararDado(linha, dino.especie, 8, ',');
    SepararDado(linha, dino.alimento, 9, ',');

    free(linha);
    free(aux);

    return dino;
}

//Cria um dinossauro à partir da posição do cursor no arquivo entrada
Dinossauro CriaDinossauroBin(FILE* entrada)
{
    //Cria um dinossauro nulo
    Dinossauro dino = CriaDinossauro();

    //Se não conseguiu ler o primeiro caractere
    if(!fread(&dino.removido, sizeof(char), 1, entrada))
    {
        //Define que houve um erro
        dino.removido = 'E';
        //Retorna o dino
        return dino;
    }

    //Se o registro atual tiver sido removido logicamente
    if(dino.removido == '1')
    {
        //Retorna o dino
        return dino;
    }

    //Lê os dados do registro
    fread(&dino.encadeamento, sizeof(int), 1, entrada);
    fread(&dino.populacao, sizeof(int), 1, entrada);
    fread(&dino.tamanho, sizeof(int), 1, entrada);
    fread(&dino.unidadeMedida, sizeof(char), 1, entrada);
    fread(&dino.velocidade, sizeof(int), 1, entrada);

    //Para ler as informações de tamanho variável do registro
    char* linha = calloc(160, sizeof(char));
    fgets(linha, 161 - sizeof(int) * 4 - sizeof(char)*2, entrada);

    SepararDado(linha, dino.nome, 0, '#');
    SepararDado(linha, dino.especie, 1, '#');
    SepararDado(linha, dino.habitat, 2, '#');
    SepararDado(linha, dino.tipo, 3, '#');
    SepararDado(linha, dino.dieta, 4, '#');
    SepararDado(linha, dino.alimento, 5, '#');

    free(linha);

    return dino;
}

//Libera o espaço alocado para dino
void LiberaDinossauro(Dinossauro dino)
{
    if(dino.nome) //if != NULL
        free(dino.nome);

    if(dino.especie) //if != NULL
        free(dino.especie);

    if(dino.habitat) //if != NULL
        free(dino.habitat);

    if(dino.tipo) //if != NULL
        free(dino.tipo);

    if(dino.dieta) //if != NULL
        free(dino.dieta);

    if(dino.alimento) //if != NULL
        free(dino.alimento);
}

//Imprime dino na tela
void ImprimeDinossauro(Dinossauro dino)
{
    printf("Nome: %s\n", dino.nome);
    printf("Especie: %s\n", dino.especie);

    if(strcmp(dino.tipo, "") != 0) //if não é nulo
        printf("Tipo: %s\n", dino.tipo);

    printf("Dieta: %s\n", dino.dieta);

    if(strcmp(dino.habitat, "") != 0) //if não é nulo
        printf("Lugar que habitava: %s\n", dino.habitat);

    if(dino.tamanho != -1) //if não é nulo
        printf("Tamanho: %.1f m\n", dino.tamanho);

    if(dino.velocidade != -1 && dino.unidadeMedida != '$') //if não é nulo algum dos valores
        printf("Velocidade: %d %cm/h\n", dino.velocidade, dino.unidadeMedida);

    printf("\n");
}
