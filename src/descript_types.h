/*!
* \file \src\descript_types.h
* \version 0.1
* \date 12/10/2021
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef DESCRIPT_TYPES_H_
#define DESCRIPT_TYPES_H_

enum FIELD_TYPES {
    // BASE_TYPE = 1,
    OBJECT_TYPE,
    ARRAY_TYPE,
    // ARRAY_REF_TYPE,
    // ARRAY_BASE_TYPE,
    STRING_TYPE,
    CLASS_REF_TYPE
};

enum ARRAY_TYPES {
    T_BOOLEAN   = 4,
    T_CHAR      = 5,
    T_FLOAT     = 6,
    T_DOUBLE    = 7,
    T_BYTE      = 8,
    T_SHORT     = 9,
    T_INT       = 10,
    T_LONG      = 11
};


#endif