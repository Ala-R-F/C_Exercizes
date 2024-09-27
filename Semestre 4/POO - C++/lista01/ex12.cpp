#include <iostream>
#include <stdio.h>

using namespace std;

int pow(int b, int e, int m){
    int resultado = b;

    for(int i = 1; i < e; i++){
        resultado = resultado * b;
    }
    return resultado%m;

}

int main()
{
    int b,e,m;

    cin >> b;
    cin >> e;
    cin >> m;
    cout << pow(b,e,m);
    return 0;
}
