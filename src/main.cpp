/**
 * @file main.cpp
 * 
 * @brief Le o arquivo e passa para as demais funcoes.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "leitor.h"
#include "exibidor.h"
#include "someTools.h"
#include "interpreter.h"

using namespace std;

int main(int arg_count, char* argument_vector[]) {
    string caminho;
    vector<string> arguments(arg_count);

    if(arg_count > 3) {
        string msg = "Numero de argumentos invalido\n";
        msg += "Digite --help para obter ajuda.\n";
        showExcept(msg);
    }

    for(int i = 0; i < arg_count; i++){
        arguments[i] = argument_vector[i];
    }

    string arg = arguments[1];

    if(arg == "--help" or arg == "-h") {
        showHelp(cout);
        return 0;
    }

    if(DEBUG_MODE) {
        cout << "Argumentos lidos da entrada: \n";
        for(const auto &it : arguments) {
            cout << it << "\n";
        }
        cout << "\n";
    }

    // std::cout << "Digite o caminho do arquivo: ";
    // std::cin >> caminho;


    if(find(arguments.begin(), arguments.end(), "-l") != arguments.end()) {
        caminho = arg;
        ClassFile teste = readClassFile(caminho);
        showClassFile(teste, cout);    
    }

    else {
        cout << "-----------------------------------------------------------------------------------------\n";
        cout << "---------------------------------- Execucao da JVM --------------------------------------\n";
        caminho = arguments[1];
        
        if(DEBUG_MODE) {
            cout << "Seu caminho:" << caminho << "\n\n";
        }

        execution_engine* exec_eng = new execution_engine(caminho);

        exec_eng->run();
        cout << "\n\n-----------------------------------------------------------------------------------------";
        cout << "--------------------------- Arquivo executado com sucesso! -----------------------------\n";
        cout << "-----------------------------------------------------------------------------------------\n\n";

    }



    return 0; //sales = vendas
}