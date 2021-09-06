/**
 * @file main.cpp
 * 
 * @brief Le o arquivo e passa para as demais funcoes.
 */
#include <iostream>
#include <string>
#include "leitor.h"
#include "exibidor.h"
#include "someTools.h"

using namespace std;

int main(int arg_count, char* argument_vector[]) {
    string caminho;

    if(arg_count != 2) {
        string msg = "Numero de argumentos invalido\n";
        msg += "Digite --help para obter ajuda.\n";
        showExcept(msg);
    }

    string arg = argument_vector[1];

    if(arg == "--help" or arg == "-h") {
        showHelp(cout);
        return 0;
    }

    // std::cout << "Digite o caminho do arquivo: ";
    // std::cin >> caminho;

    caminho = argument_vector[1];
    ClassFile teste = readClassFile(caminho);

    showClassFile(teste, cout);    

    return 0; //sales = vendas
}