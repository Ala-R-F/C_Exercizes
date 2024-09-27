#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i <= 2*n; i++){
        cout << i;
        if (i <2*n){
            cout <<", ";
        }

    }
    return 0;
}
