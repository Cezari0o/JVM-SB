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

    // if(teste.magic == 0xCAFEBABE)
    //     cout << "0xCAFEBABE\n";

    // cout << teste.magic << endl;
    // cout << teste.minor_version << endl;
    // cout << teste.major_version << endl;
    // cout << teste.constant_pool_count << endl;

    showClassFile(teste, cout);    

    return 0; //sales = vendas
}