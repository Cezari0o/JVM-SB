#include "exibidor.h"


void showGeneralInformation(const ClassFile &cf) {
    
    // Setando flags para printar em hexa
    cout.setf(ios_base::hex, ios_base::basefield);
    cout.setf(ios_base::showbase);

    cout << "Magic number: " << cf.magic << "\n";
    cout << "Flags de acesso: " << cf.access_flags << "\n";

    // Resetando as flags
    cout.unsetf(ios_base::basefield);
    cout.unsetf(ios_base::showbase);

    cout << "Minor version: " << cf.minor_version << "\n";
    cout << "Major version: " << cf.major_version << "\n";
    cout << "Numero de Constantes no pool : " << cf.constant_pool_count << "\n";    
    cout << "Classe do arquivo: " << cf.this_class << "\n"; // Indice para o pool de constantes
    cout << "Super classe : " << cf.super_class << "\n"; // Indice para o pool de constantes
    cout << "Total de Interfaces : " << cf.interfaces_count << "\n";
}

void showClassFile(const ClassFile &myClassFile) {

    cout << "--- Exibindo os dados lidos do arquivo class ---\n";
    showGeneralInformation(myClassFile);
    cout << "--- Fim da exibicao ---\n";
    // showConstantPool(myClassFile);
    // showInterfaces(myClassFile);
    // showFields(myClassFile);
    // showMethods(myClassFile);
    // showAttributes(myClassFile);
}