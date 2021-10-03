#include "interpreter.h"

interpreter::interpreter(const std::string &initial_class_name) {

    my_method_area = new method_area();
    my_java_stack  = new jvm_stack();
    my_pc          = new pc_register();
    my_heap        = new heap();
    
    ClassFile *object = new ClassFile;
    *object = readClassFile("java/lang/Object.class");
    my_method_area->insert_new_class(object);

    if(DEBUG_MODE) {
        std::cout << "Nome da sua classe: " << initial_class_name << "\n"; 
    }
    
    my_method_area->load_class(initial_class_name);
    
    initial_class_ref = &(my_method_area->get_class(get_class_from_path(initial_class_name))); 

    // Depois de carregar a classe, tenho que executar o metodo <clinit> dela
}


std::string get_class_from_path(const std::string &path) {
    char separator = '/';

    size_t temp_num = path.find_last_of(separator);

    temp_num = (temp_num == std::string::npos? 0 : temp_num + 1);
    std::string class_name = path.substr(temp_num);
    class_name = class_name.substr(0, class_name.find_last_of('.'));

    return class_name;

}

interpreter::~interpreter() {
    delete my_method_area;
    delete my_heap;
    delete my_java_stack;
    delete my_pc;
}