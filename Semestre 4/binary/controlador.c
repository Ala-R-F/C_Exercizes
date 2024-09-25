//Luis Filipe Silva Forti - 14592348
//Lucien Rodrigues Franzen - 14554835

//Trabalho 1 de ED3

#include "controlador.h"

//Dado utilizado para controlar o cabeçalho dos arquivos
Cabecalho cab;

//Lê o cabeçalho (apenas chamado pelo AbrirArquivo)
void LerCabecalho(FILE *arq)
{
    //Volta para o começo do arquivo
    fseek(arq, 0, SEEK_SET);

    //Lê os dados do cabeçalho
    fread(&cab.status, sizeof(char), 1, arq);
    fread(&cab.topo, sizeof(int), 1, arq);
    fread(&cab.proxRRN, sizeof(int), 1, arq);
    fread(&cab.nroRegRem, sizeof(int), 1, arq);
    fread(&cab.nroPagDisco, sizeof(int), 1, arq);
    fread(&cab.qttCompacta, sizeof(int), 1, arq);
}

//Escreve o cabeçalho salvo em cab (apenas chamado pelo CriarArquivo e o FecharArquivo)
void EscreverCabecalho(FILE *arq, char jaExiste)
{
    //if jaExiste == 1 (true)
    if(jaExiste == 1)
        //Volta para o começo do arquivo
        fseek(arq, 0, SEEK_SET);

    //Escreve os dados do cabeçalho
    fwrite(&cab.status, sizeof(char), 1, arq);
    fwrite(&cab.topo, sizeof(int), 1, arq);
    fwrite(&cab.proxRRN, sizeof(int), 1, arq);
    fwrite(&cab.nroRegRem, sizeof(int), 1, arq);
    fwrite(&cab.nroPagDisco, sizeof(int), 1, arq);
    fwrite(&cab.qttCompacta, sizeof(int), 1, arq);
}

//Cria um arquivo com cabeçalho no endereço passado
FILE* CriarArquivo(char* endereco)
{
    //Cria um arquivo no modo de escrita binária
    FILE* arq = fopen(endereco, "wb");

    //Se deu erro
    if(arq == NULL)
    {
        //Alerta e sai
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    //Escreve o cabeçalho salvo em cab
    EscreverCabecalho(arq, 0);
    //Preenche o restante da página com o caracter de lixo
    for(int i = 0; i < 1579; i++)
        fwrite("$", sizeof(char), 1, arq);

    return arq;
}

//Cria um arquivo no endereço passado e lê o cabeçalho
FILE* AbrirArquivo(char* endereco)
{
    //Abre o arquivo no modo de leitura e escrita binária
    FILE* arq = fopen(endereco, "rb+");

    //Se deu erro
    if(arq == NULL)
    {
        //Alerta e sai
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    //Lê o cabeçalho
    LerCabecalho(arq);

    if(cab.status == 0)
    {
        //Fecha o arquivo, alerta e sai
        fclose(arq);
        printf("Falha no processamento do arquivo.");
        return NULL;
    }

    //Avança para o fim da página do cabeçalho
    fseek(arq, 1600, SEEK_SET);

    return arq;
}

//Fecha o arquivo no endereço passado e atualiza o cabeçalho
void FecharArquivo(FILE* arq, char* endereco)
{
    //Define que o arquivo será fechado com êxito
    cab.status = '1';

    //Atualiza o cabeçalho
    EscreverCabecalho(arq, 1);

    //Fecha o arquivo
    fclose(arq);
}

//Modifica a string passada para salvar de acordo com as definições do projeto
int SalvarStringRegistro(char* str, FILE* arq)
{
    //String auxiliar para não alterar a original
    //Tamanho de 160 bytes porque é o tamanho do registro, então nunca será maior
    char* aux = calloc(160, sizeof(char));
    //Copia a string
    strcpy(aux, str);

    //Troca o primeiro \r e \n por \0
    aux[strcspn(aux, "\r")] = 0;
    aux[strcspn(aux, "\n")] = 0;

    //Pega o tamanho da string
    int tam = strlen(aux);
    //Coloca um # no final
    aux[tam] = '#';
    //Escreve a string, incluindo o #, não incluindo o \0
    fwrite(aux, sizeof(char), tam+1, arq);

    //Libera a string auxiliar
    free(aux);

    //Retorna a quantidade de bytes escritos
    return tam+1;
}

//Salva o dino passado, seguindo as definições do projeto
void SalvarRegistro(Dinossauro dino, FILE* arq)
{
    //Escreve os dados de tamanhos constantes
    fwrite(&dino.removido, sizeof(char), 1, arq);
    fwrite(&dino.encadeamento, sizeof(int), 1, arq);
    fwrite(&dino.populacao, sizeof(int), 1, arq);
    fwrite(&dino.tamanho, sizeof(int), 1, arq);
    fwrite(&dino.unidadeMedida, sizeof(char), 1, arq);
    fwrite(&dino.velocidade, sizeof(int), 1, arq);

    //Define quantos bytes do registro já foram ocupados
    int bytesOcupados = sizeof(char) * 2 + sizeof(int) * 4;

    //Escreve os dados de tamanhos variáveis e soma a quantidade de bytes ocupados
    bytesOcupados += SalvarStringRegistro(dino.nome, arq);
    bytesOcupados += SalvarStringRegistro(dino.especie, arq);
    bytesOcupados += SalvarStringRegistro(dino.habitat, arq);
    bytesOcupados += SalvarStringRegistro(dino.tipo, arq);
    bytesOcupados += SalvarStringRegistro(dino.dieta, arq);
    bytesOcupados += SalvarStringRegistro(dino.alimento, arq);

    //Coloca caracteres de lixo até que o registro tenha 160 bytes
    for(int i = bytesOcupados; i < 160; i++)
        fwrite("$", sizeof(char), 1, arq);
}

//Define qual o tipo de equivalente a string recebida (qual atributo de Dinossauro)
int TipoAchado(char* comando)
{
    //De 0 até 2, são inteiros ou caractere
    if(strcmp(comando, "populacao") == 0)
    {
        return 0;
    }
    if(strcmp(comando, "unidade") == 0)
    {
        return 1;
    }
    if(strcmp(comando, "velocidade") == 0)
    {
        return 2;
    }
    //3 é um float
    if(strcmp(comando, "tamanho") == 0)
    {
        return 3;
    }
    //Acima de 3 são strings
    if(strcmp(comando, "nome") == 0)
    {
        return 4;
    }
    if(strcmp(comando, "especie") == 0)
    {
        return 5;
    }
    if(strcmp(comando, "habitat") == 0)
    {
        return 6;
    }
    if(strcmp(comando, "tipo") == 0)
    {
        return 7;
    }
    if(strcmp(comando, "dieta") == 0)
    {
        return 8;
    }
    if(strcmp(comando, "alimento") == 0)
    {
        return 9;
    }
    //Se foi dado um atributo não existente ou escrito incorretamente
    return -1;
}

//Encontra o RRN do primeiro registro >= RRNinicial
//Devem serem passados o arquivo, o RRNinicial (onde começar a busca),
//o idBusca (qual atributo de Dinossauro) e o valS (valor do atributo procurado)
int EncontrarRRN(FILE* arq, int RRNinicial, int idBusca, char* valS)
{
    //Se não for um atributo válido
    if(idBusca == -1)
        //Avisa que não encontrou
        return -1;

    //Se foi dado um valor inválido
    if(valS == NULL || strcmp(valS, "") == 0)
        //Avisa que não encontrou
        return -1;

    //Para os valores constantes
    int valI = 0;
    float valF = 0;

    //Se for inteiro ou caractere
    if(idBusca < 3 || idBusca == 10)
    {
        valI = atoi(valS);
    }
    //Se for um float
    else if(idBusca == 3)
    {
        valF = atof(valS);
    }

    //Define o ponto inicial de pesquisa
    int RRN = RRNinicial;
    //Cria um Dinossauro nulo
    Dinossauro dino = CriaDinossauro();

    //Enquanto não tiver alcançado o fim do arquivo
    while(RRN < cab.proxRRN)
    {
        //Avança para o registo atual
        fseek(arq, 1600 + RRN * 160, SEEK_SET);

        //Para ler se foi removido
        fread(&dino.removido, sizeof(char), 1, arq);
        if(dino.removido == '1')
        {
            //Se foi removido, aumenta RRN e avança para o próximo registro
            RRN++;
            continue;
        }
        //Se não foi removido, retorna para o início do registro
        fseek(arq, 1600 + RRN * 160, SEEK_SET);

        //Dependendo do atributo procurado
        switch(idBusca)
        {
        //Se for a população
        case 0:
            //Avança para o byte inicial do atributo
            fseek(arq, 5, SEEK_CUR);
            //Lê o valor
            fread(&dino.populacao, sizeof(int), 1, arq);

            //Se for o valor procurado
            if(dino.populacao == valI)
            {
                //Libera o espaço alocado para dino
                LiberaDinossauro(dino);
                //Retorna onde encontrou
                return RRN;
            }
            break;
        //Se for a unidade de medida
        case 1:
            //Avança para o byte inicial do atributo
            fseek(arq, 13, SEEK_CUR);
            //Lê o valor
            fread(&dino.unidadeMedida, sizeof(char), 1, arq);

            //Se for o valor procurado
            if(dino.unidadeMedida == valI)
            {
                //Libera o espaço alocado para dino
                LiberaDinossauro(dino);
                //Retorna onde encontrou
                return RRN;
            }
            break;
        //Se for a velocidade
        case 2:
            //Avança para o byte inicial do atributo
            fseek(arq, 14, SEEK_CUR);
            //Lê o valor
            fread(&dino.velocidade, sizeof(int), 1, arq);

            //Se for o valor procurado
            if(dino.velocidade == valI)
            {
                //Libera o espaço alocado para dino
                LiberaDinossauro(dino);
                //Retorna onde encontrou
                return RRN;
            }
            break;
        //Se for o tamanho
        case 3:
            //Avança para o byte inicial do atributo
            fseek(arq, 9, SEEK_CUR);
            //Lê o valor
            fread(&dino.tamanho, sizeof(float), 1, arq);

            //Se for o valor procurado
            if(dino.tamanho == valF)
            {
                //Libera o espaço alocado para dino
                LiberaDinossauro(dino);
                //Retorna onde encontrou
                return RRN;
            }
            break;
        //Se for o nome
        case 4:
        //ou se for a espécie
        case 5:
        //ou se for o habitat
        case 6:
        //ou se for o tipo
        case 7:
        //ou se for a dieta
        case 8:
        //ou se for o alimento
        case 9:
            //Avança para o byte inicial do atributo
            fseek(arq, 18, SEEK_CUR);

            //Aloca o espaço para um auxiliar da leitura
            char* aux = calloc(160, sizeof(char));
            //Lê o valor
            fgets(aux, 161 - sizeof(int) * 4 - sizeof(char)*2, arq);
            //Separa o valor do atributo procurado do auxiliar
            //Salva em dino.nome de forma genérica
            SepararDado(aux, dino.nome, idBusca-4, '#');
            //Libera o auxiliar da leitura
            free(aux);


            //Se for o valor procurado
            if(strcmp(dino.nome, valS) == 0)
            {
                //Libera o espaço alocado para dino
                LiberaDinossauro(dino);
                //Retorna onde encontrou
                return RRN;
            }
            break;

        //Para o caso de querer registros não apagados
        case 10:
            //Libera o espaço alocado para dino
            LiberaDinossauro(dino);
            //Retorna onde encontrou
            return RRN;
            break;


        //Se não for um atributo válido (não deve chegar aqui)
        default:
            //Libera o espaço alocado para dino
            LiberaDinossauro(dino);
            //Retorna que não encontrou
            return -1;
            break;
        }
        //Se não for o registro procurado, avança para o próximo
        RRN++;
    }
    //Se não encontrou

    //Libera o espaço alocado para dino
    LiberaDinossauro(dino);
    //Retorna que não encontrou
    return -1;
}

//Cria a tabela usando os endereços de entrada e saída
void CreateTable(char* enderecoE, char* enderecoS)
{
    //Abre o arquivo de entrada no modo de leitura de binário
    FILE* entrada = fopen(enderecoE, "rb");

    //Se deu erro
    if(entrada == NULL)
    {
        //Alerta o erro e sai
        printf("Falha no processamento do arquivo.");
        return;
    }

    //Define os valores do cabeçário com os valores iniciais
    cab.status = '0';
    cab.topo = -1;
    cab.proxRRN = 0;
    cab.nroRegRem = 0;
    cab.nroPagDisco = 1;
    cab.qttCompacta = 0;

    //Cria o arquivo com a página do cabeçalho
    FILE* saida = CriarArquivo(enderecoS);

    //Se deu erro
    if(saida == NULL)
    {
        //Sai pois o erro foi avisado em CriarArquivo
        return;
    }

    //Dinossauro do registro atual
    Dinossauro dino;

    //Joga fora a primeira linha da entrada
    dino = CriaDinossauroCSV(entrada);

    //Loop infinito
    while(1)
    {
        //Cria um dinossauro com os dados do CSV
        dino = CriaDinossauroCSV(entrada);

        //Se chegou no fim do arquivo
        if(dino.removido == 'E')
        {
            //Libera o espaço alocado pro dino
            LiberaDinossauro(dino);
            //Encerra o loop
            break;
        }

        //Salva o registro no arquivo de saída
        SalvarRegistro(dino, saida);

        //Se estiver inserindo o registro em uma página nova
        if(cab.proxRRN % 10 == 0)
            //Aumenta a quantidade de páginas no cabeçalho
            cab.nroPagDisco++;

        //Define que o último registro tem um RRN maior
        cab.proxRRN++;

        //Libera o espaço do dino
        LiberaDinossauro(dino);
    }

    //Fecha o arquivo de entrada
    fclose(entrada);
    //Fecha o arquivo de saída, atualizando o cabeçalho
    FecharArquivo(saida, enderecoS);

    //Função de verificação do projeto
    binarioNaTela(enderecoS);
}

//Imprime os dados dos registros da tabela enderecoE não removidos logicamente
void SelectTable(char* enderecoE)
{
    //Abre o arquivo de entrada lendo o cabeçalho
    FILE* entrada = AbrirArquivo(enderecoE);

    //Se deu erro
    if(entrada == NULL)
    {
        //Sai pois o erro foi avisado em AbrirArquivo
        return;
    }
    //Se não há registros salvos
    if(cab.proxRRN == 0)
    {
        //Fecha o arquivo atualizando o cabeçalho
        FecharArquivo(entrada, enderecoE);
        //Avisa o erro e sai
        printf("Registro inexistente.");
        return;
    }

    //Cria um Dinossauro com o primeiro registro
    Dinossauro dino;
    //Para verificar se achou pelo menos um registro
    int existe = 0;

    //Loop infinito
    while(1)
    {
        //Lê o registro atual
        dino = CriaDinossauroBin(entrada);

        //Se não conseguiu ler
        if(dino.removido == 'E')
        {
            //Libera o espaço alocado
            LiberaDinossauro(dino);
            //Sai do loop
            break;
        }

        //Se o registro foi removido logicamente
        if(dino.removido == '1')
        {
            //Avança para o próximo registro
            fseek(entrada, 159, SEEK_CUR);
            //Libera o dino
            LiberaDinossauro(dino);
            continue;
        }

        //Guarda que achou um registro
        existe = 1;

        //Imprime o registro
        ImprimeDinossauro(dino);

        //Libera o espaço alocado pro Dinossauro
        LiberaDinossauro(dino);
    }
    //Se não achou nenhum registro
    if(!existe)
    {
        //Fecha o arquivo atualizando o cabeçalho
        FecharArquivo(entrada, enderecoE);
        //Avisa o erro e sai
        printf("Registro inexistente.");
        return;
    }

    //Imprime o número de páginas ocupadas
    printf("Numero de paginas de disco: %d\n\n", cab.nroPagDisco);

    //Fecha o arquivo, atualizando o cabeçalho
    FecharArquivo(entrada, enderecoE);
}

//Procura e imprime registros de acordo com valor especificado
void AcharRegistros(char* enderecoE, int qtd)
{
    //Abre o arquivo lendo o cabeçalho
    FILE* arq = AbrirArquivo(enderecoE);

    //Se deu erro
    if(arq == NULL)
    {
        //Sai pois o erro foi avisado em AbrirArquivo
        return;
    }

    //strings auxiliares
    char* comando = calloc(11, sizeof(char));
    char* valS = calloc(160, sizeof(char));

    //campo de busca
    int id = 0;

    //Para cada comando pedido
    for(int i = 0; i < qtd; i++)
    {
        //Pega o comando
        scanf("%s ", comando);
        //Define o tipo de busca
        id = TipoAchado(comando);

        //Se for uma string
        if(id > 3)
        {
            //Lê entre aspas
            scan_quote_string(valS);
            scanf("%*c");
        }
        //Senão
        else
        {
            //Lê sem aspas
            scanf("%s%*c", valS);
        }

        printf("Busca %d\n", i+1);

        //Se for um atributo inválido ou escrito incorretamente
        if(id == -1)
        {
            //Avisa o erro e avança pro próximo comando
            printf("Nome do campo invalido!");
            continue;
        }

        //Encontra o RRN do primeiro registro com o valor procurado
        int RRN = EncontrarRRN(arq, 0, id, valS);

        //Conta se houve algum dinossauro mostrado
        int counter = 0;

        //Se encontrou um registro
        while(RRN != -1)
        {
            //Avança para o começo do registro
            fseek(arq, 1600 + RRN * 160, SEEK_SET);

            //Cria um dinossauro com o registro
            Dinossauro dino = CriaDinossauroBin(arq);

            //Imprime o dino
            ImprimeDinossauro(dino);

            //Libera o espaço alocado
            LiberaDinossauro(dino);

            counter = 1;  // Diz que um dino foi achado

            //Se for nome, campo de nome único, então para
            if (id == 4){
                break;
            }

            //Procura o próximo registro com o valor procurado
            //Adiciona mais um para ir para o proximo, ao invés
            //de começar procura no atual e pegar o mesmo RRN
            RRN = EncontrarRRN(arq, RRN+1, id, valS);
        }

        if (!counter){ //Se nenhum dinossauro foi encontrado
            printf("Registro inexistente.\n\n");
        }

        //Quantas páginas foram lidas = quantidade de páginas salvas
        int nroPagDisco = cab.nroPagDisco;
        //Se estava procurando o nome e ele foi encontrado
        if(id == 4 && counter)
            //Qual página estava o registro
            nroPagDisco = 1 + RRN/10;

        //Imprime quantas páginas foram lidas
        printf("Numero de paginas de disco: %d\n\n", nroPagDisco);

        //Libera as strings auxiliares
        free(comando);
        free(valS);

        //Aloca novos espaços e reinicia as variáveis auxiliares
        comando = calloc(11, sizeof(char));
        valS = calloc(160, sizeof(char));
        id = 0;
        RRN = 0;
    }
    //Libera as string auxiliares
    free(comando);
    free(valS);

    //Fecha o arquivo, atualizando o cabeçalho
    FecharArquivo(arq, enderecoE);
}

//Remove logicamente um número de registros em enderecoE igual à qtd
void RemoverRegistros(char* enderecoE, int qtd)
{
    //Abre o arquivo lendo o cabeçalho
    FILE* arq = AbrirArquivo(enderecoE);

    //Se deu erro
    if(arq == NULL)
    {
        //Sai pois o erro foi avisado em AbrirArquivo
        return;
    }

    //strings auxiliares
    char* comando = calloc(11, sizeof(char));
    char* valS = calloc(160, sizeof(char));
    //id de busca
    int id = 0;

    //Para cada comando pedido
    for(int i = 0; i < qtd; i++)
    {
        //Pega o comando
        scanf("%s ", comando);
        //Define o tipo de busca
        id = TipoAchado(comando);

        //Se for uma string
        if(id > 3)
        {
            //Lê entre aspas
            scan_quote_string(valS);
            scanf("%*c");
        }
        //Senão
        else
        {
            //Lê sem aspas
            scanf("%s%*c", valS);
        }

        //Se for um atributo inválido ou escrito incorretamente
        if(id == -1)
        {
            //Avisa o erro e avança pro próximo comando
            printf("Nome do campo invalido!");
            continue;
        }

        //Encontra o RRN do primeiro registro com o valor procurado
        int RRN = 0;
        RRN = EncontrarRRN(arq, RRN, id, valS);

        //Se encontrou um registro
        while(RRN != -1)
        {
            //Avança para o começo
            fseek(arq, 1600 + RRN * 160, SEEK_SET);
            //Temporário para escrever
            char temp = '1';
            //Atualiza que foi removido logicamente
            fwrite(&temp, sizeof(char), 1, arq);
            //Salva o RRN do registro apagado anterior
            fwrite(&cab.topo, sizeof(int), 1, arq);

            //Substitui o restante do registro por lixo
            for(int i = 0; i < 155; i++)
                fwrite("$", sizeof(char), 1, arq);

            //Salva que aumentou a quantidade de registros removidos
            cab.nroRegRem++;
            //Salva qual o novo último registro removido
            cab.topo = RRN;

            //Procura o próximo registro com o valor procurado
            RRN = EncontrarRRN(arq, RRN, id, valS);
        }

        //Libera as strings auxiliares
        free(comando);
        free(valS);

        //Aloca novos espaços e reinicia as variáveis auxiliares
        comando = calloc(11, sizeof(char));
        valS = calloc(160, sizeof(char));
        id = 0;
        RRN = 0;
    }
    //Libera as string auxiliares
    free(comando);
    free(valS);

    //Fecha o arquivo, atualizando o cabeçalho
    FecharArquivo(arq, enderecoE);
    //Função de verificação do projeto
    binarioNaTela(enderecoE);
}

//Insere um número de registros em enderecoE igual à qtd
//Ele irá salvar no local do último registro removido, ou então adicionará no final
void InsertInto(char* enderecoS, int qtd)
{
    //Abre o arquivo lendo o cabeçalho
    FILE* arq = AbrirArquivo(enderecoS);

    //Se deu erro
    if(arq == NULL)
    {
        //Sai pois o erro foi avisado em AbrirArquivo
        return;
    }

    //string auxiliar
    char* aux = calloc(200, sizeof(char));
    //Dinossauro para armazenar os dados
    Dinossauro dino = CriaDinossauro();

    //Para cada registro à ser inserido
    for(int i = 0; i < qtd; i++)
    {
        //Para cada atributo do registro
        for(int j = 0; j < 10; j++)
        {
            //Lê o valor do atributo
            scan_quote_string(aux);
            //Se foi digitado NULO
            if(strcmp(aux, "") == 0)
                //Avança para o próximo atributo
                continue;

            //Para escolher qual atibuto definir
            switch(j)
            {
            case 0:
                strcpy(dino.nome, aux);
                break;
            case 1:
                strcpy(dino.dieta, aux);
                break;
            case 2:
                strcpy(dino.habitat, aux);
                break;
            case 3:
                dino.populacao = atoi(aux);
                break;
            case 4:
                strcpy(dino.tipo, aux);
                break;
            case 5:
                dino.velocidade = atoi(aux);
                break;
            case 6:
                dino.unidadeMedida = aux[0];
                break;
            case 7:
                dino.tamanho = atof(aux);
                break;
            case 8:
                strcpy(dino.especie, aux);
                break;
            case 9:
                strcpy(dino.alimento, aux);
                break;
            }
        }

        //Se um registro já foi removido logicamente
        if(cab.nroRegRem > 0)
        {
            //Pega o começo do atributo de encadeamento do último registro removido logicamente
            fseek(arq, 1600 + 160 * cab.topo + 1, SEEK_SET);
            //Pega o RRN do registro removido logicamente anterior
            fread(&cab.topo, sizeof(int), 1, arq);
            //Vai para o começo do registro
            fseek(arq, -5, SEEK_CUR);
            //Define que há um registro removido logicamente a menos
            cab.nroRegRem--;
        }
        else
        {
            //Pega o começo do registro a ser inserido no fim
            fseek(arq, 1600 + 160 * cab.proxRRN, SEEK_SET);

            //Se começará uma nova página
            if(cab.proxRRN % 10 == 0)
                //Define que há uma nova página
                cab.nroPagDisco++;

            //Define que o último registro tem um RRN maior
            cab.proxRRN++;
        }

        //Salva o novo registro no local definido
        SalvarRegistro(dino, arq);

        //Libera o espaço alocado e cria um novo dino nulo
        LiberaDinossauro(dino);
        dino = CriaDinossauro();
    }
    //Libera os espaços alocados
    free(aux);
    LiberaDinossauro(dino);

    //Fecha o arquivo, atualizando o cabeçário
    FecharArquivo(arq, enderecoS);
    //Função de verificação do projeto
    binarioNaTela(enderecoS);
}

void Compactar(char* enderecoS){

    //Abre o arquivo lendo o cabeçalho
    FILE* arq = AbrirArquivo(enderecoS);

    //Define novo cabeçalho
    cab.status = '0';
    cab.topo = -1;
    //cab.proxRRN = 0;
    cab.nroRegRem = 0;
    cab.nroPagDisco = 1;
    cab.qttCompacta++;

    //cria um arquivo temporário para manipulação
    FILE* novo = CriarArquivo("t1.bin");

    //Se deu erro
    if(arq == NULL || novo == NULL)
    {
        //Sai pois o erro foi avisado em AbrirArquivo ou CriarArquivo
        return;
    }

    //RRN do arquivo de leitura
    int RRN = 0;
    //Encontra o primeiro registro não removido
    RRN = EncontrarRRN(arq, 0, 10, " ");

    //RRN do arquivo de registro
    int RRNnovo = 0;

    //---Copia e exclusão---//

    //Se encontrou um registro
    while(RRN != -1)
    {
        //Avança para o começo
        fseek(arq, 1600 + RRN * 160, SEEK_SET);

        Dinossauro dino = CriaDinossauroBin(arq);

        SalvarRegistro(dino, novo);

        //Se começará uma nova página
        if(RRNnovo % 10 == 0)
            //Aumenta o número de páginas no cabeçalho
            cab.nroPagDisco++;

        //Diz que um dino foi adicionado
        RRNnovo++;

        LiberaDinossauro(dino);

        //Procura o próximo registro não removido
        RRN = EncontrarRRN(arq, RRN+1, 10, " ");
    }
    //------//
    //Fecha o arquivo com o cabeçalho incorreto e o deleta
    FecharArquivo(arq, enderecoS);
    remove(enderecoS);

    //Salva a nova quantidade de registros
    cab.proxRRN = RRNnovo;

    //Fecha o arquivo, atualizando o cabeçalho
    FecharArquivo(novo, "t1.bin");
    //Substitui o antigo pelo novo compactado
    rename("t1.bin", enderecoS);

    //Função de verificação do projeto
    binarioNaTela(enderecoS);
}
