#include <iostream>
#include "leitor.h"
#include "exibidor.h"
#include <string>

using namespace std;

int main() {
    string caminho = "java_files/class_file/Sumç.class";
   

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