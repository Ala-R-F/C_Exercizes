#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdio.h>


using namespace std;

std::string raizes(double a, double b, double c){
    double delta = pow(b,2) - 4*a*c;
    //cout << delta << endl;


    if (delta < 0 || (a==0 && b==0)){
        return "Nenhuma";
    }
    else if (c == 0){
        return "Infinitas";
    }
    else if (a == 0){
        return to_string( ((-c)/b) );
    }

    delta = sqrt(delta);
    //cout <<delta<<endl;


    double x1 = ((-b) + delta)/(2*a);
    double x2 = ((-b)- delta) / (2*a);
    //cout << x1 << " e " << x2 << endl;


    if (x1 == x2){
        return to_string(x1);
    }

    string resposta;
    
    resposta.append(to_string(x1));
    resposta.append(" e ");
    resposta.append(to_string(x2));
    return resposta;

}


int main()
{
    double a,b,c;
    cin >> a;
    cin >> b;
    cin >> c;


    cout << raizes(a,b,c);

    return 0;
}
