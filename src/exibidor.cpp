#include "exibidor.h"


std::string getTabs(int count) {
    std::string tabs = "";

    if(count == 0)
        return "";

    if(count == 1)
        return "\t";

    if(count % 2 == 1)
        tabs = getTabs(count / 2) + getTabs(count / 2) + "\t";
    else
        tabs = getTabs(count / 2) + getTabs(count / 2);

    return tabs;
}

std::string getUtf8Const(const cp_info &const_info) {

    char* hello = new char[(const_info.Const.Utf8.length + 1)];
    hello = ((char*) const_info.Const.Utf8.bytes) + '\0';
    std::string  utf8_const(hello);

    return utf8_const;

    
    // char* getString = new char[const_info.Const.Utf8.length + 1];
    // for(int i = 0; i < const_info.Const.Utf8.length; i++) {
    //     u1 b = const_info.Const.Utf8.bytes[i];

    //     if(~(b) & (1 << 7)) {

    //         cout << ((~b) & (1 << 7)) << endl;
    //         utf8_const.push_back(b);
    //     }
    //     else if(0xE0 & b) { // 3 bytes
    //         u1 b1 = const_info.Const.Utf8.bytes[i + 1];
    //         u1 b2 = const_info.Const.Utf8.bytes[i + 2];

    //         hello = ((b & 0xf) << 12) + ((b1 & 0x3f) << 6) + (b2 & 0x3f);
    //         char n_char = ((b & 0xf) << 12) + ((b1 & 0x3f) << 6) + (b2 & 0x3f);
    //         utf8_const.push_back(n_char);
    //         i += 2;

    //     }
    //     else { // 2 bytes
    //         u1 b1 = const_info.Const.Utf8.bytes[i + 1];
    //         hello = ((b & 0x1f) << 6) + (b1 & 0x3f);
    //         char n_char = ((b & 0x1f) << 6) + (b1 & 0x3f);
    //         utf8_const.push_back(n_char);
    //         i += 1;
    //     }


    // }

        // if(utf8_const.find("Sum") != utf8_const.npos) {

        //     cout << const_info.Const.Utf8.length << endl;
        //     for(int i = 0; i < const_info.Const.Utf8.length; i++) {
        //         cout << const_info.Const.Utf8.bytes[i];
        //         cout << (int) const_info.Const.Utf8.bytes[i];
        //     }
        //     cout << endl;

        //     // cout << (int) utf8_const.back() << endl;
        //     exit(EXIT_FAILURE);
        // }
    // char* utf8_const = (char *) const_info.Const.Utf8.bytes;
    // cout << "Tag = " << (u2) const_info.tag << endl;
    // for(int i = 0; i < const_info.Const.Utf8.length; i++) {
    //     cout << (int) utf8_const[i] << " ";
    // }
    // cout << endl;

}

std::string constantToString(const cp_info &cinfo, const vector<cp_info> &cp) {
    std::string result = "";
    int temp;

    switch (cinfo.tag){
        case Utf8_info_value:
            result += "<Utf8 Const> \nconstante: " +
            getUtf8Const(cinfo);
            break;
        
        case Int_info_value:
            result += "<Integer> \nvalor: " + to_string((int) cinfo.Const.Integer_info.bytes);
            break;

        case Float_info_value:
            result += "<Float> \n";
            break;

        case Long_info_value:
            result += "<Long> \nvalue: " + 
            to_string(((long long) cinfo.Const.Long_info.high_bytes) << 32 + 
            cinfo.Const.Long_info.low_bytes);
            break;

        case Double_info_value:
            result += "<Double> \n";
            break;

        case Class_info_value:
            result += "<Class> \nnome: " +
            getUtf8Const(cp[cinfo.Const.Class_info.name_index - 1]);
            break;

        case String_info_value:
            result += "<String> \nvalor: " +
            getUtf8Const(cp[cinfo.Const.String_info.string_index - 1]);
            break;

        case FieldRef_info_value:
            result += "<Field Ref> \n Declarado em: " +
            getUtf8Const(cp[cinfo.Const.Fieldref_info.class_index - 1]);
            // falta coisa aqui
            break;

        case MethodRef_info_value:
            temp = cp[cinfo.Const.Methodref_info.class_index - 1].Const.Class_info.name_index - 1;
            result += "<Method Ref> \nDeclarado em: " +
            getUtf8Const(cp[temp]);
            // "\nclass_index = " + to_string(cinfo.Const.Methodref_info.class_index);
            // falta coisa aqui
            break;

        case Intface_Ref_info_value:
            result += "<Interface Method Ref> \n Declarado em: "  +
            getUtf8Const(cp[cinfo.Const.InterfaceMethodref_info.class_index - 1]);
            break;

        case NameAType_info_value:
            result += "<Name and Type > \n Nome: " +
            getUtf8Const(cp[cinfo.Const.NameAndType_info.name_index- 1])
            + "\nDescritor: " +
            getUtf8Const(cp[cinfo.Const.NameAndType_info.descriptor_index - 1]);
            break;
            
        case Method_Hand_info_value:
            result += "<Method Handle> \n";
            break;
            
        case Method_Type_info_value:
            result += "<Method Type> \n";

            break;
            
        case Inv_Dyn_info_value:
            result += "<Invoke Dynamic> \n";

            break;
            
        default:
            showExcept(" Constante invalida!\nTag: " + to_string(cinfo.tag));
            break;
    }

    return result;
}

void showConstantPool(const ClassFile &cf, std::ostream &outstream) {
    int counter = 0;
    // std::string someTabs = getTabs(1);

    outstream << "-- Dados da tabela de constant pool --\n";
    for(const cp_info &it : cf.constant_pool) {
        outstream << "[" << counter++ <<  "] " << constantToString(it, cf.constant_pool) << "\n\n";
    }
}

void showGeneralInformation(const ClassFile &cf, std::ostream &outstream) {
    
    // Setando flags para printar em hexa
    outstream << "-- Dados Gerais do Arquivo -- \n";
    outstream.setf(ios_base::hex, ios_base::basefield);
    outstream.setf(ios_base::showbase);

    outstream << "Magic number: " << cf.magic << endl;
    outstream << "Flags de acesso: " << cf.access_flags << endl;

    // Resetando as flags
    outstream.unsetf(ios_base::basefield);
    outstream.unsetf(ios_base::showbase);

    outstream << "Minor version: " << cf.minor_version << endl;
    outstream << "Major version: " << cf.major_version << endl;
    outstream << "Numero de Constantes no pool : " << cf.constant_pool_count - 1 << endl;    
    outstream << "Classe do arquivo: " << cf.this_class << endl; // Indice para o pool de constantes
    outstream << "Super classe : " << cf.super_class << endl; // Indice para o pool de constantes
    outstream << "Total de Interfaces : " << cf.interfaces_count << endl;
}

void showClassFile(const ClassFile &myClassFile, std::ostream &outstream) {
    std::setlocale(LC_ALL, "");

    cout << "--- Exibindo os dados lidos do arquivo class ---\n\n";
    showGeneralInformation(myClassFile, outstream);
    cout << endl;
    showConstantPool(myClassFile, outstream);
    // showInterfaces(myClassFile);
    // showFields(myClassFile);
    // showMethods(myClassFile);
    // showAttributes(myClassFile);
    cout << "\n--- Fim da exibicao ---\n";
}