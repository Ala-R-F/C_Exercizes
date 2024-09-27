#include <iostream>

using namespace std;


int main()
{
    int n, numero = 0;
    while(true){
        if(!(cin >> n)){
            break;
        }
        numero = numero^n;
        //cout << std::bitset<32>(numero) << " e " << contador << endl;

    }
    //cout << std::bitset<32>(numero) << endl;
    cout << numero << endl;

    return 0;
}
