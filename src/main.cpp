#include <iostream>
#include <string>
#include "leitor.h"
#include "exibidor.h"

using namespace std;

int main() {
    string caminho;
   
    std::cout << "Digite o caminho do arquivo: ";
    std::cin >> caminho;

    ClassFile teste = readClassFile(caminho);

    showClassFile(teste, cout);    

    return 0; //sales = vendas
}