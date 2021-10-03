#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "data_areas.h"
#include "leitor.h"
#include <string>

class interpreter {

    private:

        class class_space* initial_class_ref; 
        class method_area* my_method_area;
        class heap*        my_heap;
        class jvm_stack*   my_java_stack;
        class pc_register* my_pc;

    public:

        interpreter(const std::string &initial_class_name);
        ~interpreter();

};

#endif