#include "leitor.h"


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
                cp[i].Const.Long_info.low_bytes = read4Byte(file);
                break;

            case Double_info_value:
                cp[i].Const.Double_info.high_bytes = read4Byte(file);
                cp[i].Const.Double_info.low_bytes = read4Byte(file);

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

        if(tag == Long_info_value or tag == Double_info_value)
            i++;

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
    std::vector<field_info> fields;

    if(total_fields > 0) {
        fields.resize(total_fields);

        for(int i = 0; i < fields.size(); i++) {
            field_info* f = new field_info;

            f->access_flags     = read2Byte(file);
            f->name_index       = read2Byte(file);
            f->descriptor_index = read2Byte(file);
            f->attributes_count = read2Byte(file);
            f->attributes       = new attribute_info[f->attributes_count];

            for(int j = 0; j < f->attributes_count; j++) {
                attribute_info* attr_f = readAttr(file, cp);
                
                f->attributes[j] = *attr_f;

                delete attr_f;
            }

            fields.at(i) = *f;

            delete f;
        }
    }


    return fields;
}

std::vector<method_info> readmethods(std::fstream &file, const u2 &total_methods, const vector<cp_info> &cp){
    std::vector<method_info> methods;
    
    if(total_methods > 0) {
        methods.resize(total_methods);

        for(int i = 0; i < methods.size(); i++) {
            method_info* m = new method_info;

            m->access_flags     = read2Byte(file);
            m->name_index       = read2Byte(file);
            m->descriptor_index = read2Byte(file);
            m->attributes_count = read2Byte(file);
            m->attributes       = new attribute_info[m->attributes_count];

            for(int j = 0; j < m->attributes_count; j++) {
                attribute_info* attr_m = readAttr(file, cp);
                
                m->attributes[j] = *attr_m;

                delete attr_m;
            }

            methods.at(i) = *m;

            delete m;
        }
    }

    return methods;
}

std::vector<attribute_info> readClassFileAttributes(std::fstream &file, const u2 &totalAttr, const std::vector<cp_info> &cp) {
    std::vector<attribute_info> someAttributes(totalAttr);

    for(int i = 0; i < totalAttr; i++) {
        attribute_info* attr_cf;

        attr_cf = readAttr(file, cp);
        
        someAttributes[i] = *attr_cf;

        delete attr_cf;
    }

    return someAttributes;
}

ClassFile readClassFile(const string &path){
    fstream file;
    ClassFile myClass;

    file.open(path, std::fstream::in | std::fstream::binary);

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
    myClass.fields              = readFields(file, myClass.fields_count, myClass.constant_pool);

    myClass.methods_count       = read2Byte(file);
    myClass.methods             = readmethods(file, myClass.methods_count, myClass.constant_pool);

    myClass.attributes_count    = read2Byte(file);
    myClass.attributes          = readClassFileAttributes(file, myClass.attributes_count, myClass.constant_pool);

    file.close();

    return myClass;
}
