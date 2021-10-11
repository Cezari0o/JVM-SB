#include "exibidor.h"

const ClassFile* classFileRef;

void showAttr(const attribute_info &att, std::ostream &outstream, const std::vector<cp_info> &cp);


std::string getToShowAccessFlagsStrings(u2 flags, int type) {
    std::stringstream buffer_str;

    std::vector<std::string> flags_acesso = getAccessFlagString(flags, type);
    buffer_str << " ["; 
    for(size_t i = 0; i < flags_acesso.size(); i++) {
        auto f = flags_acesso[i];
        buffer_str << f << (i == flags_acesso.size() - 1? "" : ", ");
    }
    buffer_str << "]\n";
    
    return buffer_str.str();
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
            outstream << "[" << ++counter <<  "] ";
            std::vector<std::string> constString =  constantToString(it, cf.constant_pool, false);

            for(std::string line : constString)
                outstream << line << endl;
            outstream << endl;

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

    outstream.setf(std::ios_base::uppercase);
    outstream << "Magic number: " << cf.magic << endl;
    outstream << "Flags de acesso: " << cf.access_flags << getToShowAccessFlagsStrings(cf.access_flags, CLASS_FILE_TYPE) << endl;
    outstream.unsetf(std::ios_base::uppercase);

    // Resetando as flags
    outstream.unsetf(ios_base::basefield);
    outstream.unsetf(ios_base::showbase);
    outstream.setf(std::ios::fixed);
    auto prec = outstream.precision();
    outstream.precision(0);

    int major_v = cf.major_version - 44;
    string major_v_str = getMajorVersionString(cf.major_version);
    outstream << "Minor version: " << cf.minor_version << endl;
    outstream << "Major version: " << cf.major_version << " [" << 
    (major_v < 10? "1." + major_v_str : major_v_str) << "]" << endl;
    outstream.precision(prec);
    outstream << "Constant pool count: " << cf.constant_pool_count << endl;    
    outstream << "Classe do arquivo: cp_info #" << cf.this_class << " <" << 
    constantToString(cf.constant_pool[cf.this_class - 1], cf.constant_pool).front() << ">\n";
    outstream << "Super classe : cp_info #" << cf.super_class << " <" << 
    constantToString(cf.constant_pool[cf.super_class - 1], cf.constant_pool).front() << ">\n";
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
            constantToString(cf.constant_pool.at(cf.interfaces[i] - 1), cf.constant_pool, true).front() << "\n\n";
        }
    }
    outstream << endl;

}

void printCode(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    
    outstream << "<Code>\n\n";
    outstream << "Max Stacks:  " << att.attr.Code.max_stack << endl; // 
    outstream << "Max Local:   " << att.attr.Code.max_locals << endl; // 
    outstream << "Code Length: " << att.attr.Code.code_length << endl; // 
    outstream << "Bytecode:    " << endl;

    outstream.setf(ios_base::internal, ios_base::adjustfield);
    int bytes_len = 0;
    for(u4 i = 0; i < att.attr.Code.code_length; i += bytes_len) {
        // outstream << getTabs(2) << (unsigned int) i << " " << 
        // getStringOpcode(att.attr.Code.code[i], cp) << endl;

        auto temp = getInstructToPrint(att.attr.Code.code[i],
            i, att.attr.Code.code, *classFileRef, 2
            /* opcde, vetor de bytecode, constant_pool, classfile*/);
        bytes_len = temp.first;

        outstream << getTabs(2) << (unsigned int) i << " " << temp.second << endl;

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
    outstream << "Valor: " << 
    constantToString(cp[att.attr.ConstValue.constValue_index - 1], cp).front() << endl;
}

void printExceptions(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream){
    outstream << "<Exceptions>\n";
    outstream << "Number of Exceptions:  " << att.attr.Exceptions.number_of_exceptions << endl;

    if(att.attr.Exceptions.number_of_exceptions > 0) {
        outstream << "Tabela de excecoes que podem ser lancadas:\n";
        for(int it = 0; it < att.attr.Exceptions.number_of_exceptions; it++) {
            outstream << "Tipo [" << it << "] : ";
            outstream << constantToString(cp[att.attr.Exceptions.exception_index_table_array[it] - 1], cp, true).front() << endl;
        }
    }
    
}

void printSourceFile(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {    
    outstream << "<Source File>\n";
    outstream << "Source File Index: " << att.attr.SourceFile.sourcefile_index << endl;
    outstream << "Nome do arquivo: " << 
    constantToString(cp[att.attr.SourceFile.sourcefile_index -1], cp , true).front() << endl;
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
            constantToString(cp[temp.name_index - 1], cp, true).front() << endl;
            
            outstream << "Descriptor index: #" << temp.descriptor_index << " " <<
            constantToString(cp[temp.descriptor_index - 1], cp, true).front() << endl;
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
            << getToShowAccessFlagsStrings(cf.methods[i].access_flags, METHOD_TYPE) << endl;
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
            outstream << "Flags de acesso : "<< cf.fields[i].access_flags <<
            getToShowAccessFlagsStrings(cf.fields[i].access_flags, FIELD_TYPE) << endl;
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
    
}

void showClassFile(const ClassFile &myClassFile, std::ostream &outstream) {
    std::setlocale(LC_ALL, "");
    outstream.setf(std::ios::fixed);
    outstream.precision(6);

    classFileRef = &myClassFile;
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
