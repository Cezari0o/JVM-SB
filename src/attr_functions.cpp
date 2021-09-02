#include "attr_functions.h"

int readConstant(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp) {

    if(att.att_length != 2)
        showExcept("Tamanho de Constante invalida!");

    att.attr.ConstValue.constValue_index = read2Byte(file);

    if(!validConstPoolAccess(att.attr.ConstValue.constValue_index, cp))
        showExcept("[Constant] Indice de acesso invalido para o pool de constantes");

    return true;
}

int readCode(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp) {

    att.attr.Code.max_stack  = read2Byte(file);
    att.attr.Code.max_locals = read2Byte(file);

    att.attr.Code.code_length = read4Byte(file);
    if(not (att.attr.Code.code_length > 0 and att.attr.Code.code_length < 65536)) {
        showExcept("[Code] Tamanho do atributo code_length invalido. Tam = " + to_string(att.attr.Code.code_length));
    }

    att.attr.Code.code = readBytes(att.attr.Code.code_length, file);
    att.attr.Code.exception_table_length = read2Byte(file);

    if(att.attr.Code.exception_table_length > 0) {
        att.attr.Code.except_tb_array = new exception_table[att.attr.Code.exception_table_length];
        
        for(int i = 0; i < att.attr.Code.exception_table_length; i++) {
            exception_table et;

            et.start_pc =   read2Byte(file);
            et.end_pc =     read2Byte(file);
            et.handler_pc = read2Byte(file);
            et.catch_type = read2Byte(file); 
            
            if(not (et.start_pc < et.end_pc))
                showExcept("[Code] Tratador de excessao tem start_pc > end_pc!");

            att.attr.Code.except_tb_array[i] = et;
        }

    }

    att.attr.Code.attributes_count = read2Byte(file);

    if(att.attr.Code.attributes_count > 0) {
        att.attr.Code.attributes = new attribute_info[att.attr.Code.attributes_count];

        for(int i = 0; i < att.attr.Code.attributes_count; i++) {
            attribute_info* alo;

            alo = readAttr(file, cp);

            att.attr.Code.attributes[i] = alo;
        }
    }

    return true;
}

int readExceptions(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp) {

    att.attr.Exceptions.number_of_exceptions = read2Byte(file);

    u2 num_of_exceptions = att.attr.Exceptions.number_of_exceptions;

    if(num_of_exceptions > 0) {
        att.attr.Exceptions.exception_index_table_array = new u2[num_of_exceptions];

        for(int i = 0; i < num_of_exceptions; i++) {

            att.attr.Exceptions.exception_index_table_array[i] = read2Byte(file);

            if(not validConstPoolAccess(att.attr.Exceptions.exception_index_table_array[i], cp)) {
                showExcept("[Exceptions] Indice invalido para o pool de constantes!");
            }
        }
    }

    return true;
}

// int readStackMapTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp) {
    
//     return false; // false porque eu nao fiz
// }

int readLineNumberTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp) {

    att.attr.LineNumberTable.line_number_table_length = read2Byte(file);

    u2 ln_table_length = att.attr.LineNumberTable.line_number_table_length;
    
    if(ln_table_length > 0) {
        att.attr.LineNumberTable.l_num_table_array = new line_number_table[ln_table_length];

        for(int i = 0; i < ln_table_length; i++) {
            line_number_table ln_tb;

            ln_tb.start_pc = read2Byte(file);
            ln_tb.line_number = read2Byte(file);

            att.attr.LineNumberTable.l_num_table_array[i] = ln_tb;
        }
    }

    return true;
}

int readLocalVariableTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp) {

    att.attr.LocalVariableTable.local_variable_table_length = read2Byte(file);

    u2 lvTBlength = att.attr.LocalVariableTable.local_variable_table_length;

    if(lvTBlength > 0) {
        att.attr.LocalVariableTable.lv_tb_array = new local_variable_table[lvTBlength];

        for(int i = 0; i < lvTBlength; i++) {
            local_variable_table tb;

            tb.start_pc         = read2Byte(file);
            tb.length           = read2Byte(file);
            tb.name_index       = read2Byte(file);
            tb.descriptor_index = read2Byte(file);
            tb.index            = read2Byte(file);

            att.attr.LocalVariableTable.lv_tb_array[i] = tb;
        }
    }

    return true;
}

int readSourceFile(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp) {

    att.attr.SourceFile.sourcefile_index = read2Byte(file);

    return true;
}

attribute_info* readAttr(std::fstream &file, const std::vector<cp_info> &cp) {
    attribute_info* att = new attribute_info;

    att->att_name_idx = read2Byte(file);
    att->att_length   = read4Byte(file);

    if(!validConstPoolAccess(att->att_name_idx, cp)) {
        std::string msg = "[Atributos] Indice de acesso invalido para o pool de constantes\n";
        msg += "idx acessado = " + to_string((unsigned int) att->att_name_idx);
        showExcept(msg);
    }

    std::string attr_name = getUtf8Const(cp.at(att->att_name_idx - 1));
    
    if(func_map.count(attr_name)) {
        func_map[attr_name](file, *att, cp);
    }

    else {

        for(int i = 0; i < att->att_length; i++) { // Lendo somente para ajuste do ponteiro de arquivo
            read1Byte(file);
        }
        // Decidir o que fazer para atributos nao implementados
        // Nao lancar excessoes !!!
    }
}