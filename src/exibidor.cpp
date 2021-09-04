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
            //getUtf8Const(cp[cinfo.Const.String_info.string_index - 1]);
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
            //getUtf8Const(cp[cinfo.Const.Fieldref_info.class_index - 1]);
            break;

        case MethodRef_info_value:
            // temp = cp[cinfo.Const.Methodref_info.class_index - 1].Const.Class_info.name_index - 1;

            if(not is_recursive) {
                result += "<MethodRef_info>\n";// +
            }

            result += "Nome da Classe: #" + std::to_string(cinfo.Const.Methodref_info.class_index) + " ";
            result += constantToString(cp[cinfo.Const.Methodref_info.class_index - 1], cp, true);
            result += "\nName and Type: #";
            result += std::to_string(cinfo.Const.Methodref_info.name_and_type_index) + " ";
            result += constantToString(cp[cinfo.Const.Methodref_info.name_and_type_index -1], cp, true);
            //getUtf8Const(cp[temp]);
            // "\nclass_index = " + to_string(cinfo.Const.Methodref_info.class_index);
            // falta coisa aqui
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
            //getUtf8Const(cp[cinfo.Const.InterfaceMethodref_info.class_index - 1]);
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
            
            // getUtf8Const(cp[cinfo.Const.NameAndType_info.name_index- 1])
            // + "\nDescritor: " +
            // getUtf8Const(cp[cinfo.Const.NameAndType_info.descriptor_index - 1]);
            break;
            
        case Method_Hand_info_value:

            if(not is_recursive) {
                result += "<Method Handle>\n";
            }
            result += "Reference kind: " + std::to_string(cinfo.Const.MethodHandle_info.reference_kind); // <- Arrumar
            result += "\nReference index: #" + std::to_string(cinfo.Const.MethodHandle_info.reference_index) + " ";
            result += constantToString(cp[cinfo.Const.MethodHandle_info.reference_index - 1], cp, true);
            // getUtf8Const(cp[cinfo.Const.MethodHandle_info.reference_index - 1])
            // + "\nTipo: " +
            // getUtf8Const(cp[cinfo.Const.MethodHandle_info.reference_kind - 1]);
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
    // std::string someTabs = getTabs(1);
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
    outstream << "Flags de acesso: " << cf.access_flags << endl;

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
    outstream << "-- Interfaces --\n";
    if(cf.interfaces_count>0){
        for(u2 i =0; i<cf.interfaces_count;i++){
            outstream << cf.interfaces[i] << endl;
        }
    }
    
}

void printCode(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    
    outstream << "<Code>\n";
    outstream << "Max Stacks:  " << att.attr.Code.max_stack << endl; // (ㆆ_ㆆ)
    outstream << "Max Local:   " << att.attr.Code.max_locals << endl; // (ง︡'-'︠)ง
    outstream << "Code Length: " << att.attr.Code.code_length << endl; // ╍●‿●╍
    // outstream << "Code:        " << att.code << endl;
    outstream << "Exeption Table Length: " << att.attr.Code.exception_table_length << endl;
    // outstream << "Except tb Array:  " << att.attr.Ex << endl;
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
    outstream << "Number of Exeptions:  " << att.attr.Exceptions.number_of_exceptions << endl;

    
    // outstream << "Exception Index Table Array: " << att.attr.Exceptions.exception_table_length << endl;
}

void printSourceFile(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {    
    outstream << "<Source File>\n";
    outstream << "Source File Index: " << att.attr.SourceFile.sourcefile_index << endl;
}

void printLocalVariableTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    outstream << "<Local Variable Table>\n";
    outstream << "Local Variable Table Length: " << att.attr.LocalVariableTable.local_variable_table_length << endl;
    //outstream << "Local Variable table Array:  " << lv_tb_array << endl; 
}

void printLineNumberTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream) {
    outstream << "<Line Number Table>\n";
    outstream << "Line Number Table Length: " << att.attr.LineNumberTable.line_number_table_length << endl;
    //outstream << "Line Number table Array:  " << l_num_table_array << endl; //array
}

void showAttr(const attribute_info &att, std::ostream &outstream, const std::vector<cp_info> &cp) {

    // if(!validConstPoolAccess(att->att_name_idx, cp)) {
    //     std::string msg = "[Atributos] Indice de acesso invalido para o pool de constantes\n";
    //     msg += "idx acessado = " + std::to_string((unsigned int) att->att_name_idx);
    //     showExcept(msg);
    // }
    
    std::string attr_name = getUtf8Const(cp.at(att.att_name_idx - 1));

    // if("Code" != attr_name) {
    //     std::string alo = "Code";
    //     outstream << attr_name << " <-atributo" << endl;
    //     outstream << attr_name.size() << endl;
    //     outstream << "Ta errado kkkkkk se fudeu " << endl;

    //     for(int i = 0; i < attr_name.size(); i++) {
    //         outstream << (int) attr_name[i] << " ";
    //     }
    //     outstream << endl;
    //     for(int i = 0; i < alo.size(); i++) {
    //         outstream << (int) alo[i] << " ";
    //     }
    //     outstream << endl;
    //     showExcept("Flw");
    // }

    if(func_show_map.count(attr_name)) {
        func_show_map[attr_name](att, cp, outstream);
    }

    else {
        outstream << "Nome : " << attr_name << endl;
    }

}

void showMethods(const ClassFile &cf, std::ostream &outstream) {
    
    if(cf.methods_count > 0) {
        outstream << "--- Methods ---\n";
        
        for(int i = 0; i < cf.methods_count; i++) {
            std::string method_name = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).name_index - 1));
            std::string method_descriptor = getUtf8Const(cf.constant_pool.at(cf.methods.at(i).descriptor_index - 1));

            outstream << "[" << i << "] " << method_name << endl;
            outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
            outstream.setf(ios_base::showbase);
            outstream << "Flags de acesso : "<< cf.methods[i].access_flags << endl;
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

    // Resetando as flags

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
            outstream << "Flags de acesso : "<< cf.fields[i].access_flags << endl;
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

    // outstream.setf(ios_base::hex, ios_base::basefield); // <- Pra printar em hexa as flags
    // outstream.setf(ios_base::showbase);
    
    if(cf.attributes_count > 0) {
        outstream << "\n\n--- Attributes ---\n\n";

        for(int i = 0; i < cf.attributes_count; i++) {
            // attribute_info* att = new attribute_info;
            showAttr(cf.attributes[i], outstream, cp); 
        }
    }
    
}// fizemo

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
