#include <iostream>
#include <stdio.h>


using namespace std;

int soma(double a, double b){

    return (int) (a+b);

}

int main()
{
    double a, b;
    cin >>a >> b;
    cout << soma(a,b) << endl;
    return 0;
}
