#include "interpreter.h"

interpreter::interpreter(const std::string &initial_class_name) {

    my_method_area = new method_area();
    my_java_stack  = new jvm_stack();
    my_pc          = new pc_register();
    my_heap        = new heap();
    
    my_method_area->load_class("java/lang/Object");
    my_method_area->load_class(initial_class_name);
    
    initial_class_ref = &(my_method_area->get_class(initial_class_name)); 

    // Depois de carregar a classe, tenho que executar o metodo <clinit> dela
}

interpreter::~interpreter() {
    delete my_method_area;
    delete my_heap;
    delete my_java_stack;
    delete my_pc;
}