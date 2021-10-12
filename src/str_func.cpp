#include "str_func.h"

template<typename T>
std::string getEmbracers(const T &item) {
    std::stringstream ss;

    ss << "  < " << item << " >  ";

    return ss.str();
}

std::string getArrayType(u1 n_type) {
    std::map<u1, std::string> types = {
        {4, "T_BOOLEAN"},
        {5, "T_CHAR"},
        {6, "T_FLOAT"},
        {7, "T_DOUBLE"},
        {8, "T_BYTE"},
        {9, "T_SHORT"},
        {10,"T_INT"},
        {11,"T_LONG"}
    };

    return types[n_type];
}

std::string getStringOpcode(const u1 &opcode, const std::vector<cp_info> &cp) {
    std::vector<std::pair<u2, std::string>> mnemonicos = init_opcode_list();

    for(size_t i = 0; i < mnemonicos.size(); i++) {
        if(mnemonicos.at(i).first == opcode) {
            return mnemonicos.at(i).second;
        }
    }

    return "nop";
}

// to querendo fazer retornar um vetor de string nessa funcao
std::vector<std::string> constantToString(const cp_info &cinfo, const vector<cp_info> &cp, bool summarize) {
    // std::string result = "";
    std::stringstream temp;
    std::vector<string> buffer;

    switch (cinfo.tag){
        case Utf8_info_value:

            if(not summarize) {
                buffer.push_back("<Utf8_info>");
            }

            buffer.push_back(getUtf8Const(cinfo));
            break;
        
        case Int_info_value:
            
            if(not summarize) {
                buffer.push_back("<Integer_info>");

                temp.setf(std::ios::hex, std::ios::basefield);
                temp.setf(std::ios::showbase);
                temp << "Bytes: " << cinfo.Const.Integer_info.bytes;
                temp.unsetf(std::ios::showbase);
                temp.unsetf(std::ios::basefield);

                buffer.push_back(temp.str());
                buffer.push_back("Integer : " + std::to_string((int) cinfo.Const.Integer_info.bytes));
            }

            else {
                buffer.push_back(std::to_string((int) cinfo.Const.Integer_info.bytes));
            }
            break;

        case Float_info_value:
            if(not summarize) {
                buffer.push_back("<Float_info>");

                temp.setf(std::ios::hex, std::ios::basefield);
                temp.setf(std::ios::showbase);
                temp << "Bytes: " << (cinfo.Const.Float_info.bytes);
                temp.unsetf(std::ios::showbase);
                temp.unsetf(std::ios::basefield);

                buffer.push_back(temp.str());
                buffer.push_back("Float: " + std::to_string(getFloatVal(cinfo)));
            }

            else {
                buffer.push_back(std::to_string(getFloatVal(cinfo)));
            }

            break;

        case Long_info_value:

            if(not summarize) {
                buffer.push_back( "<Long_info>" );

                temp.setf(std::ios::hex, std::ios::basefield); // <- Setando flags
                temp.setf(std::ios::showbase);
                
                    temp << "High bytes: " << ( (int) cinfo.Const.Long_info.high_bytes );
                    buffer.push_back(temp.str());

                    temp.str("");

                    temp << "Low bytes: " << ( (int) cinfo.Const.Long_info.low_bytes ); // <- Arrumar
                    buffer.push_back(temp.str());
                
                temp.unsetf(std::ios::showbase);
                temp.unsetf(std::ios::basefield);


                buffer.push_back("Long: " + std::to_string(getLongVal(cinfo)) );

            }

            else {
                buffer.push_back( std::to_string(getLongVal(cinfo)) );
            }

            break;

        case Double_info_value:
            
            if(not summarize){
                buffer.push_back( "<Double_info>" );

                temp.setf(std::ios::hex, std::ios::basefield); // <- Setando flags
                temp.setf(std::ios::showbase); // <-

                    temp << "High bytes: ";
                    temp << ((int) cinfo.Const.Double_info.high_bytes);
                    buffer.push_back(temp.str());
                    
                    temp.str(""); // <- Limpando o buffer

                    temp << "Low bytes: ";
                    temp << ((int) cinfo.Const.Double_info.low_bytes);
                    buffer.push_back(temp.str());

                temp.unsetf(std::ios::showbase);
                temp.unsetf(std::ios::basefield);

                buffer.push_back( "Double: " + std::to_string(getDoubleVal(cinfo)) );

            }

            else {
                buffer.push_back(std::to_string(getDoubleVal(cinfo)));
            }
            
            break;

        case Class_info_value:

            if(not summarize) {
                buffer.push_back("<Class_info>");
                temp << "Nome da classe: #" << (cinfo.Const.Class_info.name_index) << " ";
                temp << constantToString(cp[cinfo.Const.Class_info.name_index - 1], cp, true).front();
                buffer.push_back(temp.str());
            }

            else {
                buffer.push_back( constantToString(cp[cinfo.Const.Class_info.name_index - 1], cp, true).front() );
            }

            break;

        case String_info_value:

            if(not summarize) {
                buffer .push_back( "<String>" );    
                temp << "String: #" << (cinfo.Const.String_info.string_index) << " ";
                temp << constantToString(cp[cinfo.Const.String_info.string_index - 1], cp, true).front();
                
                buffer.push_back( temp.str() );
            }

            else {
                buffer.push_back( constantToString(cp[cinfo.Const.String_info.string_index - 1], cp, true).front() );
            }

            break;

        case FieldRef_info_value:

            if(not summarize) {
                buffer.push_back( "<FieldRef_info>" );
                temp <<  "Nome da Classe: #" << (cinfo.Const.Fieldref_info.class_index) << " ";
                temp << constantToString(cp[cinfo.Const.Fieldref_info.class_index - 1], cp, true).front();
                
                buffer.push_back( temp.str() );
                temp.str("");

                temp << "Nome e Tipo: #" << (cinfo.Const.Fieldref_info.name_and_type_index) << " ";
                temp << constantToString(cp[cinfo.Const.Fieldref_info.name_and_type_index -1], cp, true).front();

                buffer.push_back( temp.str() );
                temp.str("");

            }

            else {
                buffer.push_back( constantToString(cp[cinfo.Const.Fieldref_info.class_index - 1], cp, true).front() );

                for(std::string &it : constantToString(cp[cinfo.Const.Fieldref_info.name_and_type_index -1], cp, true)) {
                    buffer.push_back( it );
                }
            }

            break;

        case MethodRef_info_value:

            if(not summarize) {
                buffer.push_back( "<MethodRef_info>" );
                
                temp <<  "Nome da Classe: #" << (cinfo.Const.Methodref_info.class_index) << " ";
                temp << constantToString(cp[cinfo.Const.Methodref_info.class_index - 1], cp, true).front();
                
                buffer.push_back( temp.str() );
                temp.str("");

                temp << "Nome e Tipo: #" << (cinfo.Const.Methodref_info.name_and_type_index) << " ";
                temp << constantToString(cp[cinfo.Const.Methodref_info.name_and_type_index -1], cp, true).front();

                buffer.push_back( temp.str() );
                temp.str("");


            }

            else {
                buffer.push_back( constantToString(cp[cinfo.Const.Methodref_info.class_index - 1], cp, true).front() );

                for(std::string &it : constantToString(cp[cinfo.Const.Methodref_info.name_and_type_index -1], cp, true)) {
                    buffer.push_back( it );
                }
            }

            break;

        case Intface_Ref_info_value:
            
            if(not summarize) {
                buffer .push_back("<InterfaceMethodRef_info>");
                temp <<  "Nome da Classe: #" << (cinfo.Const.InterfaceMethodref_info.class_index) << " ";
                temp << constantToString(cp[cinfo.Const.InterfaceMethodref_info.class_index - 1], cp, true).front();
                
                buffer.push_back( temp.str() );
                temp.str("");

                temp << "Nome e Tipo: #" << (cinfo.Const.InterfaceMethodref_info.name_and_type_index) << " ";
                temp << constantToString(cp[cinfo.Const.InterfaceMethodref_info.name_and_type_index -1], cp, true).front();

                buffer.push_back( temp.str() );
                temp.str("");

                
            }

            else {
                buffer.push_back( constantToString(cp[cinfo.Const.InterfaceMethodref_info.class_index - 1], cp, true).front() );

                for(std::string &it : constantToString(cp[cinfo.Const.InterfaceMethodref_info.name_and_type_index -1], cp, true)) {
                    buffer.push_back( it );
                }
            }

            break;

        case NameAType_info_value:

            if(not summarize) {
                buffer .push_back( "<NameAndType_info>" );
                temp << "Nome: #" << (int) (cinfo.Const.NameAndType_info.name_index) << " ";
                temp << constantToString(cp[cinfo.Const.NameAndType_info.name_index - 1], cp, true).front();
                 
                buffer.push_back( temp.str() );
                temp.str(""); 

                temp << "Descritor: #" << (cinfo.Const.NameAndType_info.descriptor_index) << " "; 
                temp << constantToString(cp[cinfo.Const.NameAndType_info.descriptor_index - 1], cp, true).front();
                buffer.push_back( temp.str() );
                temp.str(""); 
            }
            
            else {
                buffer .push_back( constantToString(cp[cinfo.Const.NameAndType_info.name_index - 1], cp, true).front() );
                buffer.push_back(
                constantToString(cp[cinfo.Const.NameAndType_info.descriptor_index - 1], cp, true).front() 
                                ); 
            }
            
            break;
            
        case Method_Hand_info_value:

            if(not summarize) {
                buffer .push_back( "<Method Handle>" );

                temp << "Reference kind: " << (int) (cinfo.Const.MethodHandle_info.reference_kind); // <- Arrumar
                buffer.push_back( temp.str() );
                temp.str("");

                temp << "Reference index: #" << (int) (cinfo.Const.MethodHandle_info.reference_index) << " ";

                buffer.push_back( temp.str() );
                temp.str("");

                std::vector<std::string> ref_strings = 
                constantToString(cp[cinfo.Const.MethodHandle_info.reference_index - 1], cp, true);

                for(std::string s : ref_strings) {
                    buffer.push_back(s);
                }
            }

            else {
                buffer.push_back(std::to_string( (int) cinfo.Const.MethodHandle_info.reference_kind) );

                buffer.push_back( std::to_string( (int) cinfo.Const.MethodHandle_info.reference_index) );

                std::vector<std::string> ref_strings = 
                constantToString(cp[cinfo.Const.MethodHandle_info.reference_index - 1], cp, true);

                for(std::string s : ref_strings) {
                    buffer.push_back(s);
                }

            }

            break;
            
        case Method_Type_info_value:

            if(not summarize) {
                buffer.push_back( "<MethodType_info>" );
                temp << "Descriptor index: #" << (cinfo.Const.MethodType_info.descriptor_index) << " ";
                temp << getUtf8Const(cp[cinfo.Const.MethodType_info.descriptor_index - 1]);

                buffer.push_back( temp.str() );
                temp.str("");
            }

            else {
                buffer.push_back( getUtf8Const(cp[cinfo.Const.MethodType_info.descriptor_index - 1]) );
            }

            break;
            
        case Inv_Dyn_info_value:

            if(not summarize) {
                buffer .push_back( "<Invoke Dynamic>" );
                temp << "Bootstrap Method Attribute Index: ";
                temp << (cinfo.Const.InvokeDynamic_info.bootstrap_method_attr_index);

                buffer.push_back( temp.str() );
                temp.str("");

                auto strings = constantToString(cp[cinfo.Const.InvokeDynamic_info.name_and_type_index - 1], cp, false);
                
                for(const std::string &s : strings) {
                    buffer.push_back(s);
                }
            }

            else {
                
                buffer.push_back( std::to_string(cinfo.Const.InvokeDynamic_info.bootstrap_method_attr_index) );
                auto strings = constantToString(cp[cinfo.Const.InvokeDynamic_info.name_and_type_index - 1], cp, true);
                
                for(const std::string &s : strings) {
                    buffer.push_back(s);
                }
            }

            break;
            
        default:
            showExcept(" Constante invalida!\nTag: " + to_string(cinfo.tag));
            break;
    }

    return buffer;
}

std::vector<std::string> getAccessFlagString(u2 flags, int type) {

    // type -> class_file = 0, fields = 1, method = 2, 

    std::vector<std::pair<u2, std::vector<std::string>>> stringMask = {
        {0x0001,  {"ACC_PUBLIC",     "ACC_PUBLIC",       "ACC_PUBLIC"}},
        {0x0002,  {"ACC_PRIVATE",    "ACC_PRIVATE",      "ACC_PRIVATE"}},
        {0x0004,  {"ACC_PROTECTED",  "ACC_PROTECTED",    "ACC_PROTECTED"}},
        {0x0008,  {"ACC_STATIC",     "ACC_STATIC",       "ACC_STATIC"}},
        {0x0010,  {"ACC_FINAL",      "ACC_FINAL",        "ACC_FINAL"}},
        {0x0020,  {"ACC_SUPER",      "",                 "ACC_SYNCHRONIZED"}},
        {0x0040,  {"ACC_BRIDGE",     "ACC_VOLATILE",     "ACC_BRIDGE"}},
        {0x0080,  {"ACC_VARARGS",    "ACC_TRANSIENT",    "ACC_VARARGS"}},
        {0x0100,  {"ACC_NATIVE",     "",                 " ACC_NATIVE"}},
        {0x0200,  {"ACC_INTERFACE",  "",                 ""}},
        {0x0400,  {"ACC_ABSTRACT",   "",                 "ACC_ABSTRACT"}},
        {0x0800,  {"ACC_STRICT",     "",                 "ACC_STRICT"}},
        {0x1000,  {"ACC_SYNTHETIC",  "ACC_SYNTHETIC",    "ACC_SYNTHETIC"}},
        {0x2000,  {"ACC_ANNOTATION", "",                 ""}},
        {0x4000,  {"ACC_ENUM",       "ACC_ENUM",         ""}}
    };

    std::vector<std::string> flags_str;
    for(const auto &it : stringMask) {

        if(it.first & flags) {
            try {
                flags_str.push_back(it.second.at(type));
            } catch (...) {
                continue;
            }
        }

    }

    return flags_str;

}

std::string getMajorVersionString(u2 major_version) {

    return std::to_string(major_version - 44);
}

std::pair<int, std::string> getInstructToPrint(const u1 &opcode, size_t idx, u1* bytecode, const ClassFile &cf, size_t tabs_count) {
    // aqui que rola a magia
    std::pair<int, std::string> result;
    std::stringstream buffer_str;
    int quant_bytes = 0;
    buffer_str << getStringOpcode(opcode, cf.constant_pool) << " ";


    if(opcode >= 0 and opcode <= 15) { // Constantes

        quant_bytes = 1;
    }

    else if(opcode == 16) { // bipush
        
        int value = (char) bytecode[idx + 1];

        buffer_str << getEmbracers(value);
        quant_bytes = 2;
    }

    else if(opcode == 17) { // sipush
        
        int value = (short) (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        buffer_str << getEmbracers(value);
        quant_bytes = 3;
    }

    else if(opcode == 18) { // ldc
        
        buffer_str << "( ";
        
        auto constInfoStr = constantToString(cf.constant_pool[bytecode[idx + 1] - 1], cf.constant_pool, true);

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " )\n" : ", ");
        }

        quant_bytes = 2;
    }

    else if(opcode >= 19 and opcode <= 20) { // ldc_w and ldc2_w
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        buffer_str << "( ";
        auto constInfoStr = constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true);

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " )\n" : ", ");
        }

        quant_bytes = 3;
    }


    else if((opcode >= 21 and opcode <= 25) or (opcode >= 54 and opcode <= 58)) { // *load and *store
        int idx_value = bytecode[idx + 1];

        buffer_str << getEmbracers(idx_value);
        quant_bytes = 2;
    }

    else if((opcode >= 26 and opcode <= 53) or (opcode >= 59 and opcode <= 86)) { // *load_<n> and *store_<n>

        quant_bytes = 1;
    }
    
    else if(opcode >= 87 and opcode <= 95) { // Todas as stacks instructions

        quant_bytes = 1;
    }


    else if(opcode >= 96 and opcode <= 131) { // math
        quant_bytes = 1;
    }

    else if(opcode == 132) { // iinc (math)
        int idx_value = bytecode[idx + 1];
        int increment = bytecode[idx + 2];
        buffer_str << "local variable [" << idx_value << "] += " << increment;

        quant_bytes = 3;
    }
    
    else if(opcode >= 133 and opcode <= 147) { // Conversions
        
        quant_bytes = 1;
    }

    else if(opcode >= 148 and opcode <= 152) { // *cmp*
        quant_bytes = 1;
    }

    else if(opcode >= 153 and opcode <= 158) { // if<cond>
        int branch_byte = (short) (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        buffer_str.setf(std::ios_base::showpos);
        buffer_str << " " << branch_byte;
        buffer_str.unsetf(std::ios_base::showpos);
        quant_bytes = 3;
    }

    else if(opcode >= 159 and opcode <= 166) { // if_icmp<cond>
        int branch_byte = (short) ((bytecode[idx + 1] << 8) | bytecode[idx + 2]);

        buffer_str.setf(std::ios_base::showpos); // <- Pra mostrar sinal positivo
        buffer_str << " " << branch_byte;
        buffer_str.unsetf(std::ios_base::showpos);
        quant_bytes = 3;
    }

    else if(opcode >= 167 and opcode <= 168) { // control

        int branch_byte = (short) (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        buffer_str.setf(std::ios_base::showpos); // <- Pra mostrar sinal positivo
        buffer_str << " " << branch_byte;
        buffer_str.unsetf(std::ios_base::showpos);
        quant_bytes = 3;
    }

    else if(opcode == 169) { // ret
        int idx_byte = bytecode[idx + 1];

        buffer_str << getEmbracers(idx_byte);
        quant_bytes = 2;
    }

    else if(opcode == 170) { // tableswitch
        int fidx = idx;
        int align_bytes = 4 - (idx % 4);
        
        idx += align_bytes;
        // cout << idx << "\n";
        int default_b = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
        idx += 4;
        int low_b = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
        idx += 4;
        int high_b = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
        idx += 4;

        int total_offsets = high_b - low_b + 1;
        // std::cout << total_offsets << " " << idx << "\n";
        if(total_offsets < 1)
            showExcept("A tableswitch no byte em " + std::to_string(fidx) + " possui highbytes < lowbytes.");

        std::vector<int> offsets(total_offsets);
        for(size_t it = 0; it < offsets.size(); it++) {
            offsets.at(it) = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
            idx += 4;
        }

        buffer_str << 0 << " to " << offsets.size() - 1 << "\n";
        for(size_t it = 0; it < offsets.size(); it++) {
            buffer_str << getTabs(1 + tabs_count) << it << ":\t" << fidx + offsets[it];
            
            buffer_str.setf(std::ios::showpos);
            buffer_str << " (" << offsets[it] << ")\n"; 
            buffer_str.unsetf(std::ios::showpos);
        }
        buffer_str << getTabs(1 + tabs_count) << "default:\t" << fidx + default_b;
        
        buffer_str.setf(std::ios::showpos);
            buffer_str << " (" << default_b << ")\n"; 
        buffer_str.unsetf(std::ios::showpos);

        // Byte da instrucao + bytes de alinhamento + bytes de default, low e high + bytes de cada offset
        quant_bytes = align_bytes + 12 + offsets.size() * 4; 
    }
    
    else if(opcode == 171) { // lookupswitch
        int fidx = idx;
        int align_bytes = 4 - (idx % 4);
        
        idx += align_bytes;
        int default_b = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
        idx += 4;
        int npairs_b = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
        idx += 4;

        // std::cout << total_offsets << " " << idx << "\n";
        if(npairs_b < 0)
            showExcept("A lookupswitch no byte em " + std::to_string(fidx) + " possui npairs < 0.");

        std::vector<std::pair<int, int>> pairs(npairs_b);
        for(size_t it = 0; it < pairs.size(); it++) {
            pairs.at(it).first = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
            idx += 4;
            pairs.at(it).second = (bytecode[idx] << 24) | (bytecode[idx + 1] << 16) | (bytecode[idx + 2] << 8) | bytecode[idx + 3];
            idx += 4; 
        }

        buffer_str << pairs.size() << "\n";
        buffer_str << getTabs(tabs_count) << "Indexacao da lookup switch\n";
        for(const auto &it : pairs) {
            buffer_str << getTabs(tabs_count + 1) << it.first << " -> " << fidx + it.second;

            buffer_str.setf(std::ios::showpos);
                buffer_str << " (" << it.second << ")\n";
            buffer_str.unsetf(std::ios::showpos);
            
        }

        buffer_str << getTabs(1 + tabs_count) << "default:\t" << fidx + default_b;
        
        buffer_str.setf(std::ios::showpos);
            buffer_str << " (" << default_b << ")\n"; 
        buffer_str.unsetf(std::ios::showpos);

        quant_bytes = align_bytes + 8 + pairs.size() * 8;
    }

    else if(opcode >= 172 and opcode <= 177) { // returns

        quant_bytes = 1;
    }

    else if(opcode >= 178 and opcode <= 184) { // get/put-> static, field; invoke -> virtual, special
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        auto constInfoStr = constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true);

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }
        quant_bytes = 3;

    }

    else if(opcode == 185) { // invokeinterface
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true);

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }

        buffer_str << getTabs(tabs_count + 1) << " count =  " << bytecode[idx + 3]; 
        quant_bytes = 5;
    }

    else if(opcode == 186) { //  invokedynamic
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = (constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true));

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }

        quant_bytes = 5;
    }

    else if(opcode  == 187) { // new
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = (constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true));

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }


        quant_bytes = 3;
    }

    else if(opcode == 188) { // newarray
        buffer_str << getEmbracers(getArrayType(bytecode[idx + 1]));

        quant_bytes = 2;
    }

    else if(opcode == 189) { // anewarray
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = (constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true));

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }

        quant_bytes = 3;
    }
    
    else if(opcode >= 190 and opcode <= 191) {
        quant_bytes = 1;
    }

    else if(opcode >= 192 and opcode <= 193) {
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = (constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true));

        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }

        quant_bytes = 3;    
    }

    else if(opcode >= 194 and opcode <= 195) {
        quant_bytes = 1;
    }

    else if(opcode == 196) { // wide
        u1 next_op = bytecode[idx + 1];
        int idx_value = (bytecode[idx + 2] << 8) | bytecode[idx + 3];

        if(next_op != 132) { // Estende loads e stores
            buffer_str << " --> "<< getStringOpcode(next_op, cf.constant_pool) << " " << idx_value;
            quant_bytes = 4;
        }
        else { // Estende iinc
            int increment = (bytecode[idx + 4] << 8) | bytecode[idx + 5];
            buffer_str << " --> " << getStringOpcode(next_op, cf.constant_pool) << 
            " local variable [" << idx_value << "] += " << increment;
            quant_bytes = 6;
        }
    }

    else if(opcode == 197) { // multinewarray
        int idx_value = (bytecode[idx + 1] << 8) | bytecode[idx + 2];
    
        auto constInfoStr = (constantToString(cf.constant_pool[idx_value - 1], cf.constant_pool, true));
        for(size_t i = 0; i < constInfoStr.size(); i++) {
            buffer_str << constInfoStr[i] << (i == constInfoStr.size() - 1? " \n" : ", ");
        }

        buffer_str << getTabs(tabs_count + 1) << "dimensoes: " <<  (int) bytecode[idx + 3];

        quant_bytes = 4;
    }

    else if(opcode >= 198 and opcode <= 199) { // ifnull e ifnonnull
        int branch_byte = (short) (bytecode[idx + 1] << 8) | bytecode[idx + 2];

        buffer_str.setf(std::ios_base::showpos); // <- Pra mostrar sinal positivo
        buffer_str << " " << branch_byte;
        buffer_str.unsetf(std::ios_base::showpos);
        quant_bytes = 3;
    }

    else if(opcode >= 200 and opcode <= 201) {
        int branch_byte = (bytecode[idx + 1] << 24) | (bytecode[idx + 2] << 16) | (bytecode[idx + 3] << 8) | bytecode[idx + 4];
    
        buffer_str.setf(std::ios_base::showpos); // <- Pra mostrar sinal positivo
        buffer_str << " " << branch_byte;
        buffer_str.unsetf(std::ios_base::showpos);
        quant_bytes = 5;
    }

    if(quant_bytes == 0)
        quant_bytes = 1;
    
    result = make_pair(quant_bytes, buffer_str.str());

    return result;
}

std::string getTabs(int count) {
    std::string tabs = "";

    if(count == 0)
        return "";

    if(count == 1)
        return "\t";

    for(int i = 0; i < count; i++) {
        tabs.push_back('\t');
    }

    return tabs;
}


std::string getClassName(const ClassFile &cf) {
    std::string class_name;

    if(cf.this_class == 0)
        return "java/lang/Object";

    auto cp = cf.constant_pool;

    class_name = constantToString(cp[cf.this_class - 1], cp).front();

    return class_name;
}