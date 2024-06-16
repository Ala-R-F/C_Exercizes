#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main(){
    ArvAVL* ax,ay,az;
    int res,i;
    //int N = 10, dados[10] = {50,25,10,5,7,3,30,20,8,15};
    //int N = 11, dados[11] = {50,25,10,5,5,7,3,30,20,8,15};
    //int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6};

    ax = cria_ArvAVL();
    ay = cria_ArvAVL();
    az = cria_ArvAVL();

    int x,y,z;

    FILE *arquivo = fopen("dados.txt", "r");
    if(!arquivo)
        printf("Erro na abertura");

    while(1)
    {
        fscanf(arquivo, "%d", &x);
        fscanf(arquivo, "%d", &y);
        fscanf(arquivo, "%d", &z);
        if (x == 0 && y == 0 && z == 0) break;
        insere_ArvAVL(ax,x,y,z,1);
        insere_ArvAVL(ay,x,y,z,2);
        insere_ArvAVL(az,x,y,z,3);

    }


    scanf("%d", &res);

    if (res == 1){
        printf("%d %d", altura_ArvAVL(ax), totalNO_ArvAVL(ax));
    }
    else if (res == 2){
        scanf("%d", &res);
        consulta_ArvAVL(az, res, 3);
    }
    else if (res == 4){
        procuraMenor(ax,1);
        procuraMenor(ay,2);
        procuraMenor(az,3);
    }
    else if (res == 3){
        scanf("%d", &res);
        consulta_ArvAVL(ay, res, 2);
        sucY(ay);
    }

    libera_ArvAVL(ax);
    libera_ArvAVL(ay);
    libera_ArvAVL(az);


    return 0;
}
