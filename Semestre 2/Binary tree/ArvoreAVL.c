#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h" //inclui os Protótipos

struct NO{
    int x;
    int y;
    int z;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("No [%d] %d %d: H(%d) fb(%d)\n",(*raiz)->x,(*raiz)->y,(*raiz)->z,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void printRoot(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("Root: %d %d %d\n",(*raiz)->x, (*raiz)->y, (*raiz)->z);
    }
}

void sucY(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if((*raiz)->dir == NULL)
        return;
    struct NO* atual = *raiz;
    struct NO* aux = (*raiz)->dir;
    while(aux!= NULL){
        atual = aux;
        aux = aux->esq;
    }

    printf("%d",atual->y);

}



int consulta_ArvAVL(ArvAVL *raiz, int valor, int coord){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;

    int comparado, printar = 0;
    while(atual != NULL){

        if (coord == 1){
            comparado = atual->x;
        }
        else if (coord == 2){
            comparado = atual->y;
        }
        else {
            printar = 1;
            comparado = atual->z;
        }

        if(valor == comparado){
            if (printar)
                printf("YES");
            *raiz = atual;
            return 1;
        }
        if(printar)
            printf("%d ", atual->z);
        if(valor > comparado)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    if (printar)
        printf("NO");
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A){//LL
    //printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    //printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int x, int y, int z, int coord){
    int res;
    if(*raiz == NULL){//árvore vazia ou nó folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->x = x;
        novo->y = y;
        novo->z = z;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    //printf("205");


    struct NO *atual = *raiz;
    int valor, comparado;
    int raizesq = NULL, raizdir = NULL;

    if (coord == 1){
        valor = x;
        comparado = atual->x;
        if ((*raiz)->dir != NULL){
            raizdir = (*raiz)->dir->x;
        }
        if ((*raiz)->esq != NULL){
            raizesq = (*raiz)->esq->x;
        }
    }
    if (coord == 2){
        valor = y;
        comparado = atual->y;
        if ((*raiz)->dir != NULL){
            raizdir = (*raiz)->dir->y;
        }
        if ((*raiz)->esq != NULL){
            raizesq = (*raiz)->esq->y;
        }
    }
    else if (coord == 3) {
        valor = z;
        comparado = atual->z;
        if ((*raiz)->dir != NULL){
            raizdir = (*raiz)->dir->z;
        }
        if ((*raiz)->esq != NULL){
            raizesq = (*raiz)->esq->z;
        }
    }

    //printf("\n 240");
    /* mudar*/
    if(valor < comparado){
        if((res = insere_ArvAVL(&(atual->esq), x, y, z, coord)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < raizesq ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > comparado){
            if((res = insere_ArvAVL(&(atual->dir), x, y, z, coord)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if(raizdir < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO** atual, int coord){
    struct NO *no1 = *atual;
    struct NO *no2 = (*atual)->esq;


    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }

    if(coord == 1)
        printf("%d ", no1->x);
    else if(coord == 2)
        printf("%d ", no1->y);
    else
        printf("%d", no1->z);

    return no1;
}
