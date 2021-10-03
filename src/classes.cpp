#include "classes.h"

std::string getUtf8Const(const cp_info &const_info)
{

    std::string utf8_const;

    for (int i = 0; i < const_info.Const.Utf8.length; i++)
    {
        utf8_const.push_back(const_info.Const.Utf8.bytes[i]);
    }


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

bool validConstPoolAccess(const u2 &idx, const std::vector<cp_info> &cp)
{
    return idx >= 1 and idx < cp.size() + 1;
}


double getDoubleVal(const cp_info &const_info)
{
    
    unsigned long long bits = ((unsigned long long)const_info.Const.Double_info.high_bytes << 32) | ((unsigned long long) const_info.Const.Double_info.low_bytes);

    if(bits == 0x7ff0000000000000L)
        return INFINITY;// infinito positivo 

    if(bits == 0xfff0000000000000L)
        return - INFINITY;// infinito negativo 

    if(bits >= 0x7ff0000000000001L and bits <= 0x7fffffffffffffffL or bits >= 0xfff0000000000001L and bits <= 0xffffffffffffffffL)
        return nan(""); //NaN


    int s = ((bits >> 63) == 0) ? 1 : -1;
    int e = (int)((bits >> 52) & 0x7ffL);
    long long m = (e == 0) ?
    (bits & 0xfffffffffffffL) << 1 :
    (bits & 0xfffffffffffffL) | 0x10000000000000L;

    return s * m * pow(2, e - 1075);
}


long long getLongVal(const cp_info &const_info) {

    return ((unsigned long long) const_info.Const.Long_info.high_bytes << 32) | ((unsigned long long) const_info.Const.Long_info.low_bytes);
}

float getFloatVal(const cp_info &const_info)
{
    unsigned int bits = const_info.Const.Float_info.bytes;

    if(bits == 0x7f800000)
        return INFINITY;// infinito positivo 

    if(bits == 0xff800000)
        return -INFINITY;// infinito negativo 

    if(bits >= 0x7f800001 and bits <= 0x7fffffff or bits >= 0xff800001 and bits <= 0xffffffff)
        return nanf(""); //NaN

    int s = ((bits >> 31) == 0) ? 1 : -1;
    int e = ((bits >> 23) & 0xff);
    int m = (e == 0) ?
    (bits & 0x7fffff) << 1 :
    (bits & 0x7fffff) | 0x800000;

    return s * m * pow(2, e - 150);
}


cp_info::~cp_info()  {

    if(this->tag == 1) // Constante == Utf8
        delete[] this->Const.Utf8.bytes;
}

cp_info& cp_info::operator=(const cp_info &cp) {

    this->tag = cp.tag;

    if(cp.tag == 1) { // UTF8_CONST_INFO = 1
        u2 bytes_size = cp.Const.Utf8.length;
        this->Const.Utf8.length = bytes_size;
        this->Const.Utf8.bytes = new u1[bytes_size];


        for(u2 i = 0; i < bytes_size; i++) {
            this->Const.Utf8.bytes[i] = cp.Const.Utf8.bytes[i];
        }
    }

    else {
        this->Const = cp.Const;
    }

    return *this;
}

method_info::~method_info() {

    // delete[] this->attributes;
}

// Isso tudo num serve de nada kkkk.
attribute_info::~attribute_info() {

    // std::cout << "oi, voce deletou " << this->att_name;
    // getchar();
    if(del_map.count(this->att_name) > 0) {
        del_map[this->att_name](this);
    }

}

attribute_info &attribute_info::operator=(const attribute_info &attribute) {
    // attr_names = {"ConstantValue,"
                // "Code",
                // "Exceptions",
                // "SourceFile",
                // "LineNumberTable",
                // "LocalVariableTable"
                // };


    if(attribute.att_name == "Code") {
        this->attr.Code.max_stack = attribute.attr.Code.max_stack;
        this->attr.Code.max_locals = attribute.attr.Code.max_locals;
        this->attr.Code.code_length = attribute.attr.Code.code_length;

        this->attr.Code.code = new u1[this->attr.Code.code_length];

        for(u4 i = 0; i < this->attr.Code.code_length; i++) {
            this->attr.Code.code[i] = attribute.attr.Code.code[i];
        }

        this->attr.Code.exception_table_length = attribute.attr.Code.exception_table_length;

        this->attr.Code.except_tb_array = new exception_table[this->attr.Code.exception_table_length];

        for(u2 i = 0; i < this->attr.Code.exception_table_length; i++) {
            this->attr.Code.except_tb_array[i] = attribute.attr.Code.except_tb_array[i];
        }
        
        this->attr.Code.attributes_count = attribute.attr.Code.attributes_count;

        this->attr.Code.attributes = new attribute_info[this->attr.Code.attributes_count];

        for(u2 i = 0; i < this->attr.Code.attributes_count; i++) {
            this->attr.Code.attributes[i] = attribute.attr.Code.attributes[i];
        }

    }

    else if(attribute.att_name == "Exceptions") {
        this->attr.Exceptions.number_of_exceptions = attribute.attr.Exceptions.number_of_exceptions;

        this->attr.Exceptions.exception_index_table_array = new u2[this->attr.Exceptions.number_of_exceptions];

        for(u2 i = 0; i < this->attr.Exceptions.number_of_exceptions; i++) {
            this->attr.Exceptions.exception_index_table_array[i] = attribute.attr.Exceptions.exception_index_table_array[i];
        }
    }

    else if(attribute.att_name == "LineNumberTable") {
        this->attr.LineNumberTable.line_number_table_length = attribute.attr.LineNumberTable.line_number_table_length;

        this->attr.LineNumberTable.l_num_table_array = new line_number_table[this->attr.LineNumberTable.line_number_table_length];

        for(u2 i = 0; i < this->attr.LineNumberTable.line_number_table_length; i++) {
            this->attr.LineNumberTable.l_num_table_array[i] = attribute.attr.LineNumberTable.l_num_table_array[i];
        }
    } else if(attribute.att_name == "LocalVariableTable") {
        this->attr.LocalVariableTable.local_variable_table_length = attribute.attr.LocalVariableTable.local_variable_table_length;

        this->attr.LocalVariableTable.lv_tb_array = new local_variable_table[this->attr.LocalVariableTable.local_variable_table_length];

        for(u2 i = 0; i < this->attr.LocalVariableTable.local_variable_table_length; i++) {
            this->attr.LocalVariableTable.lv_tb_array[i] = attribute.attr.LocalVariableTable.lv_tb_array[i];
        }
    } else {

        this->attr = attribute.attr;
    }

    return *this;
}


void delConstant(attribute_info* att) {

    return;
}

void delCode(attribute_info* att) {

    // delete[] att->attr.Code.code;
    // delete[] att->attr.Code.except_tb_array;
    // delete[] att->attr.Code.attributes;
}

void delExceptions(attribute_info * att) {

    // delete[] att->attr.Exceptions.exception_index_table_array;
}

void delLineNumberTable(attribute_info* att) {

    // delete[] att->attr.LineNumberTable.l_num_table_array;
}

void delLocalVariableTable(attribute_info* att) {

    // delete[] att->attr.LocalVariableTable.lv_tb_array;
}

void delSourceFile(attribute_info* att) {

    return;
}


std::initializer_list<std::string> get_attributes_name() {
    return {"ConstantValue,"
            "Code",
            "Exceptions",
            "SourceFile",
            "LineNumberTable",
            "LocalVariableTable"
            };

}