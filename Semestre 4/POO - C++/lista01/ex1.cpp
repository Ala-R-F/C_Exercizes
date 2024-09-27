#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    for(int i = (3 * 5 * 17 * 11 * 7); i <= n; i+= (3 * 5 * 17 * 11 * 7)){
        cout << i << endl;
    }


    return 0;
}
