#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

int main()
{
    float gastoF, dadoF;
    float troco;
    cin >> gastoF;
    cin >> dadoF;

    int gasto = (int)(gastoF*100), dado = (int)(dadoF*100);

    troco = (dado - gasto)/100;
    cout << fixed;
    cout << setprecision(2) << "Troco: R$ " << troco << endl;

    int notas[] = {200*100, 100*100, 50*100, 20*100, 10*100, 5*100, 2*100, 1*100, 50, 25, 10, 5, 1};
    int notasdadas[] = {0,0,0,0,0,0,0,0,0,0,0, 0,0};

    int contador = 0;
    while(troco > 0){
        if (notas[contador] <= troco){
            notasdadas[contador]++;
            troco -= notas[contador];
        }
        else{
            contador++;
        }
    }


    for(int i = 0; i< 13; i++){
        cout << notasdadas[i] << " de R$ " << setprecision(2) << (( (float)(notas[i]) )/100) <<endl;
    }
    return 0;
}
