#include "leitor.h"

// Mostra o erro no terminal e encerra o programa
void showExcept(const string &msg) {

    cerr << "Erro: " << msg << "\n";
    cerr << "Terminando o programa\n";
    exit(EXIT_FAILURE);
}

bool isIdxtoCP(const u2 &idx, const std::vector<cp_info> &cp) {
    return idx >= 1 and idx < cp.size() + 1;
}

// Le a quantidade de bytes presentes em total_bytes do arquivo apontado por 
// file, e armazena no array byteArray
u1* readBytes(u4 total_bytes, fstream &file) {
    u1 *byteArray = new u1[total_bytes];

    for(int it = 0; it < total_bytes; it++) {
        byteArray[it] = read1Byte(file);
        // cout << byteArray[it] << endl;
        // if(byteArray[it] == 0 or byteArray[it] >= ((u1)240) and byteArray[it] <= ((u1)255))
        //     showExcept("Byte lido de constante em UTF-8 invalido!");
    }

    return byteArray;
}

vector<cp_info> readConstantPool(fstream &file, u2 cp_count) {

    if(cp_count < 1)
        showExcept("Constant_pool_count invalido!");

    vector<cp_info> cp(cp_count - 1);

    for(int i = 0; i < cp.size(); i++) {
        u1 tag = read1Byte(file);

        switch (tag) {
            case Class_info_value:
                cp[i].Const.Class_info.name_index = read2Byte(file);
                break;
            
            case Utf8_info_value:
                cp[i].Const.Utf8.length = read2Byte(file);

                cp[i].Const.Utf8.bytes = readBytes(cp[i].Const.Utf8.length, file);
                
                // throw "Nao feito ainda"; // <-- Erro // Basta arrumar então
                break;
                
            case Int_info_value:
                cp[i].Const.Integer_info.bytes = read4Byte(file);
                break;
            
            case Float_info_value:
                cp[i].Const.Float_info.bytes = read4Byte(file);
                break;

            case Long_info_value:
                cp[i].Const.Long_info.high_bytes = read4Byte(file);
                cp[i++].Const.Long_info.low_bytes = read4Byte(file);
                break;

            case Double_info_value:
                cp[i].Const.Double_info.high_bytes = read4Byte(file);
                cp[i++].Const.Double_info.low_bytes = read4Byte(file);
                break;

            case String_info_value:
                cp[i].Const.String_info.string_index = read2Byte(file);
                break;

            case FieldRef_info_value:
                cp[i].Const.Fieldref_info.class_index = read2Byte(file);
                cp[i].Const.Fieldref_info.name_and_type_index = read2Byte(file);
                break;

            case MethodRef_info_value:
                cp[i].Const.Methodref_info.class_index = read2Byte(file);
                cp[i].Const.Methodref_info.name_and_type_index = read2Byte(file);
                break;
                
            case Intface_Ref_info_value:
                cp[i].Const.InterfaceMethodref_info.class_index = read2Byte(file);
                cp[i].Const.InterfaceMethodref_info.name_and_type_index = read2Byte(file);
                break;
              
            case NameAType_info_value:
                cp[i].Const.NameAndType_info.name_index = read2Byte(file);
                cp[i].Const.NameAndType_info.descriptor_index = read2Byte(file);
                break;
              
            case Method_Hand_info_value:
                cp[i].Const.MethodHandle_info.reference_kind = read1Byte(file);
                cp[i].Const.MethodHandle_info.reference_index = read2Byte(file);
                break;
              
            case Method_Type_info_value:
                cp[i].Const.MethodType_info.descriptor_index = read1Byte(file);
                break;
              
            case Inv_Dyn_info_value:
                cp[i].Const.InvokeDynamic_info.bootstrap_method_attr_index = read2Byte(file);
                cp[i].Const.InvokeDynamic_info.name_and_type_index = read2Byte(file);
                break;

            default:
                cout << "tag: " << tag << "\n";
                showExcept("Byte de tag invalido!");
                break;
        }
        cp[i].tag = tag;
    }

    return cp;
}

vector<u2> readInterfaces(fstream &file, u2 interfaces_count, u2 const_pool_count) {
    vector<u2> interfaces_idx(interfaces_count);

    for(u2 &it : interfaces_idx) {
        it = read2Byte(file);

        if(not (it >= 1 and it < const_pool_count)) {
            string msg = "Indice no array de interfaces nao eh uma entrada valida no pool ";
            msg = msg + " de constantes"; 
            showExcept(msg);
        }
    }

    return interfaces_idx;
}

std::vector<field_info> readFields(std::fstream &file, const u2 &total_fields, const vector<cp_info> &cp) {
    std::vector<field_info> fields(total_fields);

    showExcept("Nao testado ainda");
    for(int i = 0; i < fields.size(); i++) {
        field_info* f = new field_info;

        f->acces_flags      = read2Byte(file);
        f->name_index       = read2Byte(file);
        f->descriptor_index = read2Byte(file);
        f->attributes_count = read2Byte(file);
        // f->attributes       = readAttr(file, cp);
        fields.at(i) = *f;
    }

    return fields;
}

ClassFile readClassFile(const string &path){
    fstream file;
    ClassFile myClass;

    file.open(path, fstream::in);

    if(!file.is_open()) {
        showExcept("Nao foi possivel abrir o arquivo");
    }

    myClass.magic = read4Byte(file);

    if(myClass.magic != 0xCAFEBABE)
        showExcept("O arquivo lido nao eh um arquivo class");

    myClass.minor_version       = read2Byte(file);
    myClass.major_version       = read2Byte(file);
    myClass.constant_pool_count = read2Byte(file);
    myClass.constant_pool       = readConstantPool(file, myClass.constant_pool_count);
    myClass.access_flags        = read2Byte(file);
    myClass.this_class          = read2Byte(file);
    myClass.super_class         = read2Byte(file);
    myClass.interfaces_count    = read2Byte(file);
    
    myClass.interfaces          = readInterfaces(file, myClass.interfaces_count, myClass.constant_pool_count);

    myClass.fields_count        = read2Byte(file);
    // myClass.fields              = readFields(file, myClass.fields_count);
    file.close();

    return myClass;
}

u1 read1Byte(fstream &file) {
    u1 byte;
    char my_byte[1];

    file.read(&my_byte[0], sizeof(u1));

    // Se leu fim de arquivo, ou se falhou em ler do arquivo
    if(!file)
        showExcept("Falha em ler do arquivo class");

    byte = (u1) my_byte[0];

    return byte;
}

u2 read2Byte(fstream &file){
    u2 byte2;
    
    byte2 = read1Byte(file);
    byte2 = (byte2 << 8) | read1Byte(file);
}

u4 read4Byte(fstream &file){
    u4 byte4;
    byte4 = read2Byte(file);
    byte4 = (byte4 << 16) | read2Byte(file);
    // 1111 0010 0000 0000
    return byte4;
}

/*
Formato big-endian
static u2 u2Read(FILE *fd) {
 u2 toReturn = getc(fd);
 toReturn = (toReturn << 8) | (getc(fd));
 return toReturn;
} 

*/