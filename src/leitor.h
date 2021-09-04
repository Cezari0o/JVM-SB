#ifndef LEITOR_H_
#define LEITOR_H_

// #include <iostream>
// #include <vector>
// #include <string>
// #include <map>
// #include <util>
#include <bits/stdc++.h>
#include "classes.h"
#include "attr_functions.h"

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

ClassFile readClassFile(const std::string &path);

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
