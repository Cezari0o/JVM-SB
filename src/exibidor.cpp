#include "exibidor.h"

void showAttr(const attribute_info &att, std::ostream &outstream, const std::vector<cp_info> &cp);

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

std::string getAccessFlagString(u2 flags, int type) {

    // type -> class_file = 0, fields = 1, method = 2, 

    std::vector<std::pair<u2, std::vector<std::string>>> stringMask = {
        {0x0001,  {"ACC_PUBLIC", "ACC_PUBLIC", "ACC_PUBLIC"}},
        {0x0002,  {"ACC_PRIVATE", "ACC_PRIVATE", "ACC_PRIVATE"}},
        {0x0004,  {"ACC_PROTECTED", "ACC_PROTECTED", "ACC_PROTECTED"}},
        {0x0008,  {"ACC_STATIC", "ACC_STATIC", "ACC_STATIC"}},
        {0x0010,  {"ACC_FINAL", "ACC_FINAL", "ACC_FINAL"}},
        {0x0020,  {"ACC_SUPER", "", "ACC_SYNCHRONIZED"}},
        {0x0040,  {"ACC_BRIDGE", "ACC_VOLATILE", "ACC_BRIDGE"}},
        {0x0080,  {"ACC_VARARGS", "ACC_TRANSIENT", "ACC_VARARGS"}},
        {0x0100,  {"ACC_NATIVE", ""," ACC_NATIVE"}},
        {0x0200,  {"ACC_INTERFACE", "",""}},
        {0x0400,  {"ACC_ABSTRACT", "", "ACC_ABSTRACT"}},
        {0x0800,  {"ACC_STRICT", "", "ACC_STRICT"}},
        {0x1000,  {"ACC_SYNTHETIC", "ACC_SYNTHETIC", "ACC_SYNTHETIC"}},
        {0x2000,  {"ACC_ANNOTATION", "", ""}},
        {0x4000,  {"ACC_ENUM", "ACC_ENUM", ""}}
    };


    for(auto &it : stringMask) {
        if(flags == it.first) {
            return it.second[type];
        }
    }

    return "ACC_FLAG_PUBLIC";
}

std::string constantToString(const cp_info &cinfo, const vector<cp_info> &cp, bool is_recursive) {
    std::string result = "";
    int temp;

    switch (cinfo.tag){
        case Utf8_info_value:

            if(not is_recursive) {
                result += "<Utf8_info>\n";
            }

            result += getUtf8Const(cinfo);
            break;
        
        case Int_info_value:
            result += "<Integer> \nvalor: " + to_string((int) cinfo.Const.Integer_info.bytes);
            
            if(not is_recursive) {
                result += "<Integer_info>\n";

                result += "Bytes: " + std::to_string(cinfo.Const.Integer_info.bytes); // <- Arrumar
                result += "Integer : ";
            }

            result += std::to_string((int) cinfo.Const.Integer_info.bytes);
            break;

        case Float_info_value:
            if(not is_recursive) {
                result += "<Float_info>\n";
                result += "Byte: " + std::to_string(cinfo.Const.Float_info.bytes) + "\n"; // <- Arrumar
                result += "Float: ";
            }

            result += std::to_string(getFloatVal(cinfo)); // <- Arrumar
            break;

        case Long_info_value:

            if(not is_recursive) {
                result = "<Long_info>\n";
                result += "High bytes: ";
                result += std::to_string((int) cinfo.Const.Long_info.high_bytes) + "\n"; // <- Arrumar
                result += "Low bytes: ";
                result += std::to_string((int) cinfo.Const.Long_info.low_bytes) + "\n"; // <- Arrumar
            }

            result += std::to_string(getLongVal(cinfo));
            break;

        case Double_info_value:
            
            if(not is_recursive){
                result += "<Double_info>\n";
                result += "High bytes: ";
                result += std::to_string((int) cinfo.Const.Double_info.high_bytes) + "\n"; // <- Arrumar
                result += "Low bytes: ";
                result += std::to_string((int) cinfo.Const.Double_info.low_bytes) + "\n"; // <- Arrumar
            }
            
            result += std::to_string(getDoubleVal(cinfo));
            break;

        case Class_info_value:

            if(not is_recursive) {
                result = "<Class_info>\n\n";
                result += "Nome da classe: #";
                result += std::to_string(cinfo.Const.Class_info.name_index) + " ";
            }

            result += constantToString(cp[cinfo.Const.Class_info.name_index - 1], cp, true);
            break;

        case String_info_value:

            if(not is_recursive) {
                result += "<String>\n";// +    
                result += "String: #";
                result += std::to_string(cinfo.Const.String_info.string_index) + " ";
            }

            result += constantToString(cp[cinfo.Const.String_info.string_index - 1], cp, true);
            break;

        case FieldRef_info_value:

            if(not is_recursive) {
                result += "<FieldRef_info>\n";// +
            }

            result += "Nome da Classe: #" + std::to_string(cinfo.Const.Fieldref_info.class_index) + " ";
            result += constantToString(cp[cinfo.Const.Fieldref_info.class_index - 1], cp, true);
            result += "\nName and Type: #";
            result += std::to_string(cinfo.Const.Fieldref_info.name_and_type_index) + " ";
            result += constantToString(cp[cinfo.Const.Fieldref_info.name_and_type_index -1], cp, true);
            break;

        case MethodRef_info_value:

            if(not is_recursive) {
                result += "<MethodRef_info>\n";// +
            }

            result += "Nome da Classe: #" + std::to_string(cinfo.Const.Methodref_info.class_index) + " ";
            result += constantToString(cp[cinfo.Const.Methodref_info.class_index - 1], cp, true);
            result += "\nName and Type: #";
            result += std::to_string(cinfo.Const.Methodref_info.name_and_type_index) + " ";
            result += constantToString(cp[cinfo.Const.Methodref_info.name_and_type_index -1], cp, true);
            break;

        case Intface_Ref_info_value:
            
            if(not is_recursive) {
                result += "<InterfaceMethodRef_info>\n";// +
            }

            result += "Nome da Classe: #" + std::to_string(cinfo.Const.InterfaceMethodref_info.class_index) + " ";
            result += constantToString(cp[cinfo.Const.InterfaceMethodref_info.class_index - 1], cp, true);
            result += "\nName and Type: #";
            result += std::to_string(cinfo.Const.InterfaceMethodref_info.name_and_type_index);
            result += constantToString(cp[cinfo.Const.InterfaceMethodref_info.name_and_type_index -1], cp, true);
            break;

        case NameAType_info_value:

            if(not is_recursive) {
                result += "<NameAndType_info>\n"; // +
                result += "Name: #" + std::to_string(cinfo.Const.NameAndType_info.name_index) + " "; 
                result += constantToString(cp[cinfo.Const.NameAndType_info.name_index - 1], cp, true);
                result += "\nDescriptor: #" + std::to_string(cinfo.Const.NameAndType_info.descriptor_index) + " "; 
                result += constantToString(cp[cinfo.Const.NameAndType_info.descriptor_index - 1], cp, true);
            }
            
            else {
                result += constantToString(cp[cinfo.Const.NameAndType_info.name_index - 1], cp, true) + ": " +
                constantToString(cp[cinfo.Const.NameAndType_info.descriptor_index - 1], cp, true); 
            }
            
            break;
            
        case Method_Hand_info_value:

            if(not is_recursive) {
                result += "<Method Handle>\n";
            }
            result += "Reference kind: " + std::to_string(cinfo.Const.MethodHandle_info.reference_kind); // <- Arrumar
            result += "\nReference index: #" + std::to_string(cinfo.Const.MethodHandle_info.reference_index) + " ";
            result += constantToString(cp[cinfo.Const.MethodHandle_info.reference_index - 1], cp, true);
            break;
            
        case Method_Type_info_value:

            if(not is_recursive) {
                result += "<MethodType_info>\n";
                result += "Descriptor index: # " + std::to_string(cinfo.Const.MethodType_info.descriptor_index) + " ";
            }

            result += getUtf8Const(cp[cinfo.Const.MethodType_info.descriptor_index - 1]);
            break;
            
        case Inv_Dyn_info_value:

            if(not is_recursive) {
                result += "<Invoke Dynamic> \n";
            }

            result += "Bootstrap Method Attribute Index: " + 
            std::to_string(cinfo.Const.InvokeDynamic_info.bootstrap_method_attr_index) + "\n";
            result += "Name and type: #" +
            std::to_string(cinfo.Const.InvokeDynamic_info.name_and_type_index) + " " +
            constantToString(cp[cinfo.Const.InvokeDynamic_info.name_and_type_index - 1], cp, true);

            break;
            
        default:
            showExcept(" Constante invalida!\nTag: " + to_string(cinfo.tag));
            break;
    }

    return result;
}

void showConstantPool(const ClassFile &cf, std::ostream &outstream) {
    int counter = 0;
    bool jump_next = false;

    outstream << "-- Dados da tabela de constant pool --\n";
    for(const cp_info &it : cf.constant_pool) {

        if(jump_next) {
            jump_next = false;
            outstream << "[" << ++counter <<  "] " << " (large numeric continued)\n\n";
            continue;
        }
        else {
            outstream << "[" << ++counter <<  "] " << constantToString(it, cf.constant_pool, false) << "\n\n";
            if(it.tag == Long_info_value or it.tag == Double_info_value) {
                jump_next = true;
            }

        }
    }
}

void showGeneralInformation(const ClassFile &cf, std::ostream &outstream) {
    
    // Setando flags para printar em hexa
    outstream << "-- Dados Gerais do Arquivo -- \n";
    outstream.setf(ios_base::hex, ios_base::basefield);
    outstream.setf(ios_base::showbase);

    outstream << "Magic number: " << cf.magic << endl;
    outstream << "Flags de acesso: " << cf.access_flags << " " << getAccessFlagString(cf.access_flags, CLASS_FILE_TYPE) << endl;

    // Resetando as flags
    outstream.unsetf(ios_base::basefield);
    outstream.unsetf(ios_base::showbase);

    outstream << "Minor version: " << cf.minor_version << endl;
    outstream << "Major version: " << cf.major_version << endl;
    outstream << "Constant pool count: " << cf.constant_pool_count << endl;    
    outstream << "Classe do arquivo: cp_info #" << cf.this_class << " <" << 
    constantToString(cf.constant_pool[cf.this_class - 1], cf.constant_pool, true) << ">\n";
    outstream << "Super classe : cp_info #" << cf.super_class << " <" << 
    constantToString(cf.constant_pool[cf.super_class - 1], cf.constant_pool, true) << ">\n";
    outstream << "Quant. de Interfaces : " << cf.interfaces_count << endl;
    outstream << "Quant. de Fields : " << cf.fields_count << endl;
    outstream << "Quant. de Metodos : " << cf.methods_count << endl;
    outstream << "Quant. de Atributos : " << cf.attributes_count << endl;
}

void showInterfaces(const ClassFile &cf, std::ostream &outstream){
    outstream << "-- Interfaces --\n\n";
    if(cf.interfaces_count>0){
        for(u2 i =0; i<cf.interfaces_count;i++){
            outstream << "[" << i << "] cp_info#" << cf.interfaces[i] << endl;
            outstream << "Super interface: " << 
            constantToString(cf.constant_pool.at(cf.interfaces[i] - 1), cf.constant_pool, true) << "\n\n";
        }
    }
    outstream << endl;

}

std::string getStringOpcode(const u1 &opcode, const std::vector<cp_info> &cp) {
    std::vector<std::pair<u2, std::string>> mnemonicos = init_opcode_list();

    for(int i = 0; i < mnemonicos.size(); i++) {
        if(mnemonicos.at(i).first == opcode) {
            return mnemonicos.at(i).second;
        }
    }

    return "Null";
}

void printCode(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    
    outstream << "<Code>\n\n";
    outstream << "Max Stacks:  " << att.attr.Code.max_stack << endl; // (ㆆ_ㆆ)
    outstream << "Max Local:   " << att.attr.Code.max_locals << endl; // (ง︡'-'︠)ง
    outstream << "Code Length: " << att.attr.Code.code_length << endl; // ╍●‿●╍
    outstream << "Bytecode:    " << endl;

    outstream.setf(ios_base::internal, ios_base::adjustfield);
    for(int i = 0; i < att.attr.Code.code_length; i++) {
        outstream << getTabs(2) << (unsigned int) i << " " << 
        getStringOpcode(att.attr.Code.code[i], cp) << endl;
    }
    outstream.unsetf(ios_base::adjustfield);

    outstream << "Exception Table Length: " << att.attr.Code.exception_table_length << endl;

    if(att.attr.Code.exception_table_length > 0) {
        outstream << "\nTabela de excecoes: \n";
        for(int it = 0; it < att.attr.Code.exception_table_length; it++) {
            auto except = att.attr.Code.except_tb_array[it];
            outstream << "Excecao" << "[" << it <<"] " << endl <<
            getTabs(1) << "start_pc: " << except.start_pc << endl;
            outstream << getTabs(1) << "end_pc: " << except.end_pc << endl;
            outstream << getTabs(1) << "handler_pc: " << except.handler_pc << endl;
            outstream << getTabs(1) << "catch_type: " << except.catch_type << endl; 
        }
        outstream << endl;
    }

    outstream << "Attributes Count: " << att.attr.Code.attributes_count << endl;

    if(att.attr.Code.attributes_count > 0) {
        outstream << "<- Code Attributes: ->\n" << endl;
        for(int i = 0; i < att.attr.Code.attributes_count; i++) {
            showAttr(att.attr.Code.attributes[i], outstream, cp);
        }
        outstream << endl;
    }

}

void printConstValue(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream){
    outstream << "<Constant Attribute>\n";
    outstream << constantToString(cp[att.attr.ConstValue.constValue_index - 1], cp, false) << endl;
}

void printExceptions(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream){
    outstream << "<Exceptions>\n";
    outstream << "Number of Exceptions:  " << att.attr.Exceptions.number_of_exceptions << endl;

    if(att.attr.Exceptions.number_of_exceptions > 0) {
        outstream << "Tabela de excecoes que podem ser lancadas:\n";
        for(int it = 0; it < att.attr.Exceptions.number_of_exceptions; it++) {
            outstream << "Tipo [" << it << "] : ";
            outstream << constantToString(cp[att.attr.Exceptions.exception_index_table_array[it] - 1], cp, true) << endl;
        }
    }
    
}

void printSourceFile(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {    
    outstream << "<Source File>\n";
    outstream << "Source File Index: " << att.attr.SourceFile.sourcefile_index << endl;
    outstream << "Nome do arquivo: " << 
    constantToString(cp[att.attr.SourceFile.sourcefile_index -1], cp , true);
}

void printLocalVariableTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    outstream << "<Local Variable Table>\n";
    outstream << "Local Variable Table Length: " << att.attr.LocalVariableTable.local_variable_table_length << endl;

    if(att.attr.LocalVariableTable.local_variable_table_length > 0) {
        outstream << "Tabela de Variaveis locais: \n";

        for(int it = 0; it < att.attr.LocalVariableTable.local_variable_table_length; it++) {
            auto temp = att.attr.LocalVariableTable.lv_tb_array[it];

            outstream << "Number: " << it << endl;
            outstream << "Start_pc: #" << temp.start_pc << endl;
            outstream << "Length: " << temp.length << endl;
            outstream << "Name index: #" << temp.name_index << " " << 
            constantToString(cp[temp.name_index - 1], cp, true) << endl;
            
            outstream << "Descriptor index: #" << temp.descriptor_index << " " <<
            constantToString(cp[temp.descriptor_index - 1], cp, true) << endl;
            outstream << "Variable index: #" << temp.index << "\n\n"; 
        }
    }
}

void printLineNumberTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    outstream << "<Line Number Table>\n";
    outstream << "Line Number Table Length: " << att.attr.LineNumberTable.line_number_table_length << endl;

    if(att.attr.LineNumberTable.line_number_table_length > 0){
        outstream << "Tabela de Número de Linhas: \n";

        for(int it = 0; it < att.attr.LineNumberTable.line_number_table_length; it++){
            auto temp = att.attr.LineNumberTable.l_num_table_array[it];

            outstream << "Number: " << it << endl;
            outstream << "Start_pc: #" << temp.start_pc << endl;
            outstream << "Line Number: #" << temp.line_number << "\n\n";
        } 
    }
}

void showAttr(const attribute_info &att, std::ostream &outstream, const std::vector<cp_info> &cp) {
    
    std::string attr_name = getUtf8Const(cp.at(att.att_name_idx - 1));

    outstream << "\n\nInformacao Geral\n";
    outstream << "\nIndice do nome do atributo: #" << att.att_name_idx << " <" <<
    attr_name << ">\n";
    outstream << "\nTamanho do atributo :" << att.att_length << endl;

    if(func_show_map.count(attr_name)) {
        func_show_map[attr_name](att, cp, outstream);
    }
}

void showMethods(const ClassFile &cf, std::ostream &outstream) {
    
    if(cf.methods_count > 0) {
        outstream << "\n\n--- Methods ---\n";
        
        for(int i = 0; i < cf.methods_count; i++) {
            std::string method_name = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).name_index - 1));
            std::string method_descriptor = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).descriptor_index - 1));

            outstream << "[" << i << "] " << method_name << endl;
            outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
            outstream.setf(ios_base::showbase);
            outstream << "Flags de acesso : "<< cf.methods[i].access_flags << " " 
            << getAccessFlagString(cf.methods[i].access_flags, METHOD_TYPE) << endl;
            outstream.unsetf(ios_base::basefield);
            outstream.unsetf(ios_base::showbase);
            
            outstream << "Descriptor: " << method_descriptor << endl;
            outstream << "Num. de Atributos : " << cf.methods[i].attributes_count << endl;
            

            if(cf.methods[i].attributes_count > 0) {
                outstream << "--> Atributos do metodo: \n";

                for(int j = 0; j < cf.methods[i].attributes_count; j++)
                {
                    showAttr(cf.methods[i].attributes[j], outstream, cf.constant_pool);
                }
            }
        }
    }

}

void showFields(const ClassFile &cf, std::ostream &outstream){
    outstream << "\n\n--- Fields ---\n";
    if(cf.fields_count>0){

        for(u2 i =0; i<cf.fields_count;i++){
            std::string field_name = getUtf8Const(cf.constant_pool.at(cf.fields.at(i).name_index - 1));
            std::string field_descriptor = getUtf8Const(cf.constant_pool.at(cf.fields.at(i).descriptor_index - 1));

            outstream << "\n[" << i << "] " << field_name << endl;
            outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
            outstream.setf(ios_base::right, ios_base::adjustfield);
            outstream.setf(ios_base::showbase);
            outstream << "Flags de acesso : "<< cf.fields[i].access_flags << " " << 
            getAccessFlagString(cf.fields[i].access_flags, FIELD_TYPE) << endl;
            // Resetando as flags
            outstream.unsetf(ios_base::basefield);
            outstream.unsetf(ios_base::showbase);
            outstream.unsetf(ios_base::adjustfield);

            outstream << "Descriptor: " << field_descriptor << endl;
            outstream << "Num. de Atributos :" << cf.fields[i].attributes_count << endl;

            if(cf.fields[i].attributes_count > 0) {
                outstream << "--> Atributos do field: \n";
                for(int j = 0; j < cf.fields[i].attributes_count; j++)
                {
                    showAttr(cf.fields[i].attributes[j], outstream, cf.constant_pool);
                }

            }
            outstream << endl;
        }
    }

}

void showAttributes(const ClassFile &cf, std::ostream &outstream, const std::vector<cp_info> &cp) {

   
    if(cf.attributes_count > 0) {
        outstream << "\n\n--- Attributes ---\n\n";

        for(int i = 0; i < cf.attributes_count; i++) {
            // attribute_info* att = new attribute_info;
            showAttr(cf.attributes[i], outstream, cp); 
        }
    }
    
}// fizemo
//vlw 
void showClassFile(const ClassFile &myClassFile, std::ostream &outstream) {
    std::setlocale(LC_ALL, "");

    outstream << "\n--- Exibindo os dados lidos do arquivo class ---\n\n";
    showGeneralInformation(myClassFile, outstream);
    outstream << endl;
    showConstantPool(myClassFile, outstream);
    showInterfaces(myClassFile, outstream);
    showFields(myClassFile, outstream);
    showMethods(myClassFile, outstream);
    showAttributes(myClassFile, outstream, myClassFile.constant_pool);
    outstream << "\n\n--- Fim da exibicao ---\n";
}
