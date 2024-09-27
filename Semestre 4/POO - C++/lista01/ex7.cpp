
#include <iostream>
#include <stdio.h>

using namespace std;

int seq(int n, int k, int *ini){
    int soma = 0;
    if (n >= k){
        for(int i = n-k; i <n; i++){
            soma += (ini[i]*ini[i]);
        }
    }
    else{
        soma = ini[n];
    }
    return soma;
}



int main()
{
    int a, b;
    int t[] = {1, -2, 1};

    cin >>a >> b;
    cout << seq(a,b,t) << endl;
    return 0;
}
