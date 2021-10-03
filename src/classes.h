/**
 * @file classes.h
 * 
 * @brief Contem as definicoes de classes e estruturas usadas para leitura de arquivos .class
 * 
 */

#ifndef CLASSES_H_
#define CLASSES_H_

#include "someTools.h"
#include <map>
#include <vector>
#include <cmath>

// Estruturas auxiliares de atributos


/**
 * @struct exception_table
 * @brief Define uma estrutura auxiliar para atributos
 * @sa attribute_info
 * @global
 */
typedef struct {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table;

/**
 * @struct line_number_table
 * @brief Define uma estrutura auxiliar para atributos
 * @sa attribute_info
 * @global
 */
typedef struct {
    u2 start_pc;
    u2 line_number;
} line_number_table;

/**
 * @struct local_variable_table
 * @brief Define uma estrutura auxiliar para atributos
 * @sa attribute_info
 * @global
 */
typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} local_variable_table;

/**
 * @struct attribute_info
 * @brief Representa a estrutura de um atributo, de acordo a especificacao da documentacao da JVM 8
 * @global
 */
typedef struct attribute_info {
    
    ~attribute_info();

    u2 att_name_idx;
    u4 att_length;
    std::string att_name;

    union {
        struct {
            u2 constValue_index;
        } ConstValue;

        struct {
            u2 max_stack;
            u2 max_locals;
            u4 code_length;
            u1* code;
            u2 exception_table_length;
            exception_table* except_tb_array; // >-<
            u2 attributes_count;
            struct attribute_info* attributes;

        } Code;

        struct {
            u2 number_of_exceptions;
            u2* exception_index_table_array;
        } Exceptions;

        // struct { // Ainda nao feito...
        //     u2 number_of_entries;
        //     // stack_map_frame entries[number_of_entries];
        // } StackMapTable;

        struct {
            u2 line_number_table_length;
            line_number_table* l_num_table_array;
        } LineNumberTable;

        struct {
            u2 local_variable_table_length;
            local_variable_table* lv_tb_array;

        } LocalVariableTable;

        struct {
            u2 sourcefile_index;
        } SourceFile;

        u1* info;

    } attr;

    attribute_info() = default;
    attribute_info(const attribute_info &at) {
        *this = at;
    }

    attribute_info &operator=(const attribute_info&attribute);

} attribute_info;

/**
 * @struct field_info
 * @brief Representa a estrutura de um field do arquivo .class, especificado de acordo com a documentacao da JVM 8
 * @global
 */
typedef struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;
    // std::vector<attribute_info> attributes;
    
    field_info() = default;
    field_info(const field_info& f) {
        *this = f;
    }

    field_info &operator=(const field_info &f) {
        this->access_flags = f.access_flags;
        this->name_index = f.name_index;
        this->descriptor_index = f.descriptor_index;
        this->attributes_count = f.attributes_count;

        this->attributes = new attribute_info[this->attributes_count];
        
        for(u2 i = 0; i < this->attributes_count; i++) {
            this->attributes[i] = f.attributes[i];
        }

        return *this;
    }

} field_info;
    
/**
 * @struct method_info
 * @brief Representa a estrutura de um metodo do arquivo .class, especificado de acordo com a documentacao da JVM 8
 * @global
 */
typedef struct method_info {

    ~method_info();
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info* attributes;

    method_info() = default;
    method_info(const method_info &m) {
        *this = m;
    }

    method_info &operator=(const method_info &m) {
        this->access_flags = m.access_flags;
        this->name_index = m.name_index;
        this->descriptor_index = m.descriptor_index;
        this->attributes_count = m.attributes_count;

        this->attributes = new attribute_info[this->attributes_count];
        
        for(u2 i = 0; i < this->attributes_count; i++) {
            this->attributes[i] = m.attributes[i];
        }

        return *this;
    }
} method_info;


/**
 * @struct cp_info
 * @brief Contem a definicao das estruturas presentes no pool de constantes.
 * @global
 * 
 */
typedef struct cp_info {
    u1 tag;

    ~cp_info();
    union {
      struct{
         u2 name_index;
      } Class_info;               //valor = 7
      
      struct{
          u2 class_index;
          u2 name_and_type_index;
      } Fieldref_info;            //valor = 9

      struct {
          u2 class_index;
          u2 name_and_type_index;
      } Methodref_info;           //valor = 10

      struct{
          u2 class_index;         
          u2 name_and_type_index;
      } InterfaceMethodref_info;  //valor = 11

      struct{
          u2 string_index;
      }String_info;               //valor = 8

      struct{                   
          u4 bytes;
      }Integer_info;              //valor = 3  

      struct{
          u4 bytes;
      }Float_info;                //valor = 4

      struct{
          u4 high_bytes;
          u4 low_bytes;
      }Long_info;                 //valor = 5

      struct{
          u4 high_bytes;
          u4 low_bytes;
      }Double_info;               //valor = 6

      struct{
          u2 name_index;
          u2 descriptor_index;
      }NameAndType_info;          //valor = 12

      struct{   
          u2 length;
          u1* bytes;
      }Utf8;                      //valor = 1

      struct{
          u1 reference_kind;
          u2 reference_index;
      } MethodHandle_info;         // valor  = 15

      struct{
          u2 descriptor_index;
      } MethodType_info;           // valor = 16
    
      struct{
          u2 bootstrap_method_attr_index;
          u2 name_and_type_index;
      }InvokeDynamic_info;        // valor = 18
    } Const;


    cp_info() = default;
    cp_info(const cp_info &cp) {
        *this = cp;
    }

    cp_info& operator=(const cp_info &cp);

} cp_info;


/**
 * @class ClassFile
 * 
 * @brief Armazena os dados contidos em um arquivo .class.
 *
 *  
 * @author	Gabriel Cesário 
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 */
class ClassFile {
    public:
      u4 magic;
      u2 minor_version;
      u2 major_version;
      u2 constant_pool_count;
      std::vector<cp_info> constant_pool;
      u2 access_flags;
      u2 this_class;
      u2 super_class;
      u2 interfaces_count;
      std::vector<u2> interfaces;
      u2 fields_count;
      std::vector<field_info> fields;
      u2 methods_count;
      std::vector<method_info> methods;
      u2 attributes_count;
      std::vector<attribute_info> attributes; 
};

/**
 * @brief Verifica se o indice recebido é valido para no pool de constantes
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	idx   	O indice para o pool de constantes.	
 * @param	cp      O pool de constantes, na forma de um vetor.
 * @return	True se o acesso e valido, false caso contrario
 */
bool validConstPoolAccess(const u2 &idx, const std::vector<cp_info> &cp);

/**
 * @brief Funcao que retorna a string extraida da constante recebida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	const_info Contem a constante no formato UTF8 da struct cp_info.
 * @warning A estrutura deve ser uma constante em UTF8.
 * @return	Uma string extraida dos bytes da constante em utf8.
 * @retval<string> A string eh uma instanciacao da string usada em c++.
 * @sa http://www.cplusplus.com/reference/string/string/
 */
std::string getUtf8Const(const cp_info &const_info);
/**
 * @brief Retorna o valor double presente na constante recebida.
 *
 * 
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	const_info Contem o valor em IEE 754 representado o valor em ponto flutuante precisao dupla da constante.
 * @return	O valor double da constante.
 * @retval<double> O valor retornado foi montado da constante
 */
double getDoubleVal(const cp_info &const_info);
/**
 * @brief Monta o valor float presente na constante recebida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	const_info	Contem o valor em IEE 754 representado o valor em ponto flutuante da constante
 * @return	Valor float da constante.
 * @sa getDoubleVal
 */
float getFloatVal(const cp_info &const_info);

/**
 * @brief Retorna o valor long presente na constante
 * 
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @param const_info Contem o valor long da constante recebida
 * @return Valor long montado.
 */
long long getLongVal(const cp_info &const_info);


typedef void attr_del_func(attribute_info*);

// Funcoes para deletar atributos
void delConstant(attribute_info*);
void delCode(attribute_info*);
void delExceptions(attribute_info*);
void delSourceFile(attribute_info*);
void delLineNumberTable(attribute_info*);
void delLocalVariableTable(attribute_info*);

std::initializer_list<std::string> get_attributes_name();

static std::map<std::string, attr_del_func*> del_map = {
                                                        {"ConstantValue", delConstant},
                                                        {"Code", delCode},                                                
                                                        {"Exceptions", delExceptions},
                                                        {"SourceFile", delSourceFile},
                                                        {"LineNumberTable", delLineNumberTable},
                                                        {"LocalVariableTable", delLocalVariableTable}
                                            };


#endif