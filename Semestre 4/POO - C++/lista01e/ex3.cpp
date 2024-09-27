#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a, b, c;

    float ma, mg, mq, mh;

    cin >> a;
    cin >> b;
    cin >> c;

    ma = (a+b+c)/3;
    mh = 3 / (1/a + 1/b + 1/c);
    mg = 1.0/3.0;
    mg = pow((a*b*c), (mg));
    mq = (pow(a,2) + pow(b,2) + pow(c,2))/3;
    mq = pow(mq, 0.5);

    cout << "ma " << ma << " mh " << mh << " mg " << mg << " mq " << mq << endl;



    cout << mh << endl;
    cout << mq << endl;

    return 0;
}
