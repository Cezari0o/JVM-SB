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
#include "interpreter.h"

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

    // caminho = arg;
    // ClassFile teste = readClassFile(caminho);

    interpreter a(caminho);
    cout << "-----------------------------------------------------------------------------------------";
    cout << "Arquivo executado com sucesso!";
    cout << "-----------------------------------------------------------------------------------------\n\n";

    // showClassFile(teste, cout);    

    return 0; //sales = vendas
}