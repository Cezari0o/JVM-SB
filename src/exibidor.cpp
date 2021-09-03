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
            getUtf8Const(cp[cinfo.Const.MethodHandle_info.reference_index - 1])
            + "\nTipo: " +
            getUtf8Const(cp[cinfo.Const.MethodHandle_info.reference_kind - 1]);
            break;
            
        case Method_Type_info_value:
            result += "<Method Type> \n";
            getUtf8Const(cp[cinfo.Const.MethodType_info.descriptor_index - 1]);
            break;
            
        case Inv_Dyn_info_value:
            result += "<Invoke Dynamic> \n";
            getUtf8Const(cp[cinfo.Const.InvokeDynamic_info.name_and_type_index - 1]);
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
    outstream << "Constant pool count: " << cf.constant_pool_count << endl;    
    outstream << "Classe do arquivo: " << cf.this_class << endl; // Indice para o pool de constantes
    outstream << "Super classe : " << cf.super_class << endl; // Indice para o pool de constantes
    outstream << "Total de Interfaces : " << cf.interfaces_count << endl;
    outstream << "Total de Fields : " << cf.fields_count << endl;
    outstream << "Total de Métodos : " << cf.methods_count << endl;
}

void showInterfaces(const ClassFile &cf, std::ostream &outstream){
    outstream << "-- Interfaces --\n";
    if(cf.interfaces_count>0){
        for(u2 i =0; i<cf.interfaces_count;i++){
            outstream << cf.interfaces[i] << endl;
        }
    }
    
}

void showFields(const ClassFile &cf, std::ostream &outstream){
    outstream << "-- Fields --\n";
    outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
    outstream.setf(ios_base::showbase);
    if(cf.fields_count>0){
        for(u2 i =0; i<cf.fields_count;i++){
            std::string field_name = getUtf8Const(cf.constant_pool.at(cf.fields.at(i).name_index - 1));
            std::string field_descriptor = getUtf8Const(cf.constant_pool.at(cf.fields.at(i).descriptor_index - 1));

            outstream << "[" << i << "] " << field_name << endl;
            outstream << "Flags de acesso : "<< cf.fields[i].access_flags << endl;

            outstream << "Descriptor: " << field_descriptor << endl;
            outstream << "Num. de Atributos :" << cf.fields[i].attributes_count << endl;

        }
    }

    // Resetando as flags
    outstream.unsetf(ios_base::basefield);
    outstream.unsetf(ios_base::showbase);
}

void showMethods(const ClassFile &cf, std::ostream &outstream) {
    outstream << "-- Methods --\n";
    outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
    outstream.setf(ios_base::showbase);
    
    if(cf.methods_count > 0) {
        
        for(int i = 0; i < cf.methods_count; i++) {
            std::string method_name = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).name_index - 1));
            std::string method_descriptor = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).descriptor_index - 1));

            outstream << "[" << i << "] " << method_name << endl;
            outstream << "Flags de acesso : "<< cf.methods[i].access_flags << endl;
            outstream << "Descriptor: " << method_descriptor << endl;
            outstream << "Num. de Atributos :" << cf.methods[i].attributes_count << endl;
            // P(r)intar os atributos
        }
    }

    // Resetando as flags
    outstream.unsetf(ios_base::basefield);
    outstream.unsetf(ios_base::showbase);

}

void showAttributes(const ClassFile &cf, std::ostream &outstream){}//faz ai

void showClassFile(const ClassFile &myClassFile, std::ostream &outstream) {
    std::setlocale(LC_ALL, "");

    outstream << "--- Exibindo os dados lidos do arquivo class ---\n\n";
    showGeneralInformation(myClassFile, outstream);
    outstream << endl;
    showConstantPool(myClassFile, outstream);
    showInterfaces(myClassFile, outstream);
    showFields(myClassFile, outstream);
    showMethods(myClassFile, outstream);
    // showAttributes(myClassFile, outstream);
    outstream << "\n--- Fim da exibicao ---\n";
}