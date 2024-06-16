/////
/*

    Trabalho Ed2 - 3

    Aluno: Lucien Rodrigues

*/
/////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
    int index;
    char* palavra; //30+1 para incluir o '\0'
    int qtd;
};


typedef struct item Item;

void printTable(Item* tabela, int s){
    for(int i = 0; i< s; i++){
        if (tabela[i].qtd >0){
            printf("\nItem[%d]: %s %d",tabela[i].index, tabela[i].palavra, tabela[i].qtd);
        }
    }
}

int hash(char* palavra, int s){ //Função que mapeia o primeiro lugar que a palavra deveria ocupar

    int v = 0;
    for(int i = 0; i < strlen(palavra);i++){ //Para cada caractere
        v += v*3 + (palavra[i]); //utiliza o ascii do caractere
        v = v%s; //Calcula a sobra, achando um lugar dentro da tabela
    }
    //printf("\nHash feito");
    return v;
}

int procurarHash(Item* tabela, char* palavra, int s, int c1, int c2, int iteracao){ //Acha o hash, lidando com colisões

    int index = (hash(palavra, s) + c1*iteracao + c2*iteracao*iteracao)%s; //(h(w) + c1*i + c2*i^2)%s

    if (tabela[index].qtd != -2){//Se há algo, ou não há porem há é uma bandeira de deleção previa
        if (!strcmp(tabela[index].palavra,palavra) && tabela[index].qtd != -1){ //Vê se a palavra foi excluida alemd e se é igual
            return index;
        }
        else {
            //printf("\ncolisao");
            return procurarHash(tabela,palavra, s, c1, c2,iteracao+1); //recursão para o proximo passo, aumentando iteração
        }
    }
    else if (tabela[index].qtd == -2){
        return -1;//Não achou palavra, entrou em nulo não utilizado antes
    }
}

int inserirHash(Item* tabela, char* palavra, int s, int c1, int c2, int iteracao){ //Lida com inserção e colisões
    int index = (hash(palavra, s) + c1*iteracao + c2*iteracao*iteracao)%s; //(h(w) + c1*i + c2*i^2)%s
    int existe = -2;

    if (tabela[index].qtd != -2 && tabela[index].qtd != -1){//Se há algo ou e não é uma bandeira de deleção
        if (!strcmp(tabela[index].palavra,palavra)){ //Aumenta quantidade se for igual
            tabela[index].qtd++;
            //printf("\nAumentando [%s] para [%d]", tabela[index].palavra, tabela[index].qtd);
            return 1;
        }
        else {
            //printf("\ncolisao");
            inserirHash(tabela,palavra, s, c1, c2,iteracao+1);
        }
    }
    else  { //Se não há nada ou já teve algo mas foi deletado

        if (tabela[index].qtd == -1){//Se foi algo deletado,
            existe = procurarHash(tabela, palavra, s, c1, c2, iteracao); //Será menos 1 se não existir
        }
        if (existe>0){//"existe" negativo quer dizer que não achou na tabela inteira ou o lugar achado não era deletado para começar
            index = existe; //Troca o index para onde ele viu que a palavra existe
        }

        char* d = malloc(31*sizeof(char));

        strcpy(d, palavra);
        //printf("\ntemp a ser inserido: %s", d);


        //Coloca os valores no item
        (tabela[index]).palavra = d;
        (tabela[index]).qtd = 1;
        (tabela[index]).index = index;

        //printTable(tabela,s);
        return 1;
    }

    return 1;
}



int main()
{
    char a, frase[120001];
    int s, c1, c2, index, t;

    scanf("%d %d %d", &s, &c1, &c2);

    /* Valores teste
    s = 100;
    c1 = 1;
    c2 = 1;*/


    struct item tabela[s]; //Cria tabela hash
    for(int i = 0; i< s; i++){ //Cria todos com quantidade nula, qtd irá ser chave para varias operações
        tabela[i].qtd = -2;
    }

    //printf("\nDiga t: ");
    scanf("%d\n", &t); //Escolhe opção

    while(t!=0){

        //----- T = 1 Recebe string----

        if (t ==1){
            int cont = 0; //Contador de em qual caractere a str esta

            while(1){
                scanf("%c", &a); //Pega caractere por caractere, para poder comparar com \n
                //printf("[%c]", a);
                if (a == '\n'){ //Termina a frase lida
                    frase[cont] = '\0'; //Adiciona terminador de str no final
                    break;
                }
                frase[cont] = a;
                cont++;
            }


            //------Acha cada palavra individual-----

            //Primeira palavrqa
            char* palavra = strtok(frase, " "); //Divide por espaço
            //printf("strtok:%s", palavra);

            inserirHash(tabela, palavra, s, c1, c2, 0);

            //cont = 1;
            //Segunda palavra em diante
            while(palavra!=NULL) { //Vê o resto da string até acabar
                palavra = strtok(NULL, " "); //Divide por espaço
                //printf("\n\nstrtok:%s", palavra);

                if (palavra==NULL){
                    break;
                }


                //Adiciona palavra no dicionario
                inserirHash(tabela, palavra, s, c1, c2, 0);
                //printf(" cont dess einsert %d", cont);
                //cont++;
            }
        }
        //-*-*-*-*-*-*-*-*-*-*-*-* fim T = 1






        //----- T = 2 Quantidade e mais frequente ----

        if(t == 2){



            //----- Imprime a palavra mais frequente-----

            //printf("\n--------\nn");

            int max = 0, indexDoMax = -1, total = 0;

            for(int i = 0; i< s; i++){
                if (tabela[i].qtd!= -2){

                    //Conta as palavras durante o loop
                    if(tabela[i].qtd!= -1){//Não é uma palavra deletada
                        total++;
                    }

                    //Acha a maior durante o loop
                    if (tabela[i].qtd > max){
                        indexDoMax = i;
                        max = tabela[i].qtd;
                    }
                    else if (tabela[i].qtd == max){ //encontra ordem alfabetica se houver duas iguais
                        if (strcmp(tabela[i].palavra, tabela[indexDoMax].palavra)<0){//se a antiga for alfabeticamente antes do que a nova
                            indexDoMax = i;
                            max = tabela[i].qtd;
                        }
                    }
                }
            }

            if (total == 0){
                printf("nenhuma palavra encontrada");
            }
            else{
                printf("foram encontradas %d palavras diferentes\npalavra mais frequente = %s, encontrada %d vezes\n", total, tabela[indexDoMax].palavra, tabela[indexDoMax].qtd);
            }
        }

        //-*-*-*-*-*-*-*-*-*-*-*-* fim T = 2



        //----- T = 3 Encontra palavras na tabela ------
        //----- T = 4 Remove palavra encontrada ------


        //Como são quase iguais, estão na mesma sessão mas com condições para só uma acontecer


        if (t == 3 || t == 4){
            char procurada[31];
            int encontradoHash, n;
            //printf("Diga a qtd de procuradas:");

            scanf("%d", &n);

            for(int i = 0; i < n; i++){
                scanf("%s", procurada);
                //printf("\nProcurando : %s", procurada);

                encontradoHash = procurarHash(tabela, procurada,s,c1,c2,0);

                if(encontradoHash!=-1){

                    if (t == 3){ //Só imprime quando pedir para apenas encontrar
                        //printf("\nItem[%d]: %s %d",tabela[encontradoHash].index, tabela[encontradoHash].palavra, tabela[encontradoHash].qtd);
                        printf("%s encontrada %d\n", tabela[encontradoHash].palavra, tabela[encontradoHash].qtd);
                    }
                    else if (t == 4){//Quando pedir para remover
                        printf("%s removida\n", procurada);
                        tabela[encontradoHash].qtd = -1; //Deixa marca de que foi deletado antes, para ajudar na procura
                    }
                }
                else {//Se não foi encontrada
                    printf("%s nao encontrada\n", procurada);
                }
            }
        }




        //----- T = 5 Imprime tabela ----

        if(t == 5){

            printf("imprimindo tabela hash\n");
            int flag = 1;
            for(int i = 0; i< s; i++){
                if (tabela[i].qtd != -2 && tabela[i].qtd != -1){
                    //printf("\nItem[%d]: %s %d",tabela[i].index, tabela[i].palavra, tabela[i].qtd);
                    printf("%s %d\n", tabela[i].palavra, tabela[i].index);
                    flag = 0; //Deixa marcado que pelo menos uma palavra foi achada
                }
            }
            if (!flag){ //Se hou palavras
                //printf("nada");
            }
            printf("fim da tabela hash\n");
        }
        //-*-*-*-*-*-*-*-*-*-*-*-* fim T = 5

        scanf("%d\n", &t); //Vê o próximo t

    }





    return 0;
}
