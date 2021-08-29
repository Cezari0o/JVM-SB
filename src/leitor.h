#ifndef LEITOR_H_
#define LEITOR_H_

// #include <iostream>
// #include <vector>
// #include <string>
#include <bits/stdc++.h>

using namespace std;

#define Utf8_info_value        1
#define Int_info_value         3
#define Float_info_value       4
#define Long_info_value        5
#define Double_info_value      6
#define Class_info_value       7
#define String_info_value      8
#define FieldRef_info_value    9
#define MethodRef_info_value   10
#define Intface_Ref_info_value 11
#define NameAType_info_value   12
#define Method_Hand_info_value 15
#define Method_Type_info_value 16
#define Inv_Dyn_info_value     18

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;
typedef unsigned long u8;

typedef struct {
    u1 tag;

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
          u2 high_bytes;
          u2 low_bytes;
      }Double_info;               //valor = 6

      struct{
          u2 name_index;
          u2 descriptor_index;
      }NameAndType_info;          //valor = 12

      struct{   
          u2 length;
          u1 bytes[];
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
} cp_info;


class ClassFile {
    public:
      u4 magic;
      u2 minor_version;
      u2 major_version;
      u2 constant_pool_count;
      vector<cp_info> constant_pool;
      u2 access_flags;
      u2 this_class;
      u2 super_class;
      u2 interfaces_count;
      vector<u2> interfaces;
      u2 fields_count;
      // field_info fields [fields_count];
      u2 methods_count;
      // method_info methods [methods_count];
      // u2 attributes_count;
      // attribute_info attributes [attributes_count];
};

ClassFile readClassFile(const string &path);


// Lembrar de tirar caso nao use em outros arquivos
u1 readByte(fstream &fp);

u2 read2Byte(fstream &fp);

u4 read4Byte(fstream &fp);


#endif

//class ClassFile {
// u4 magic;
// u2 minor_version;
// u2 major_version;
// u2 constant_pool_count;
// cp_info constant_pool [constant_pool_count-1];
// u2 access_flags;
// u2 this_class;
// u2 super_class;
// u2 interfaces_count;
// u2 interfaces [interfaces_count];
// u2 fields_count;
// field_info fields [fields_count];
// u2 methods_count;
// method_info methods [methods_count];
// u2 attributes_count;
// attribute_info attributes [attributes_count];
// } ;

//CakeCase ©2021-2021
