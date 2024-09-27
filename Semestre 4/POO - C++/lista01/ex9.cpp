#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
    double x1,x2,y1,y2, resul;
    cin >> x1>>y1>>x2>>y2;
    resul = pow(  (  pow((x1-x2), 2) + pow((y1-y2), 2)), 0.5);


    cout << setprecision(5) << resul << endl;
    return 0;
}
