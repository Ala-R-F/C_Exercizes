#include <iostream>
#include <fstream>
#include <string>



std::string conteudo(std::string nome){
    std::ifstream arq(nome);
    std::string aux;
    std::string total;
    while(getline(arq, aux)){
         total.append(aux + "\n");
    }
    return total;

}

int main()
{
    std::cout << conteudo("dados.txt");
    return 0;
}
