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

    this->instructions = get_instructions();

    // sort(this->instructions.begin(), this->instructions.end(), to_sort_instruct_method);

    throw ItemNotFoundError(" Tem que iniciar as classes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    // Depois de carregar a classe, tenho que executar o metodo <clinit> dela
    this->init_class(initial_class_name);
}


std::string get_class_from_path(const std::string &path) {
    char separator = '/';

    size_t temp_num = path.find_last_of(separator);

    temp_num = (temp_num == std::string::npos? 0 : temp_num + 1);
    std::string class_name = path.substr(temp_num);
    class_name = class_name.substr(0, class_name.find_last_of('.'));

    return class_name;

}

void interpreter::init_class(const std::string &class_name) {
    const method_info *class_initializer;

    try {
        class_initializer = &(this->my_method_area->get_method(class_name, {"<clinit>", "()V"}));

    } catch(const Exception &e) {
        return;
    }

    this->execute_method(class_name, *class_initializer);    
}

interpreter::~interpreter() {
    delete my_method_area;
    delete my_heap;
    delete my_java_stack;
    delete my_pc;
}

void interpreter::execute_method(const std::string &class_name, const method_info &m) {
    frame *new_frame;

    try {
        this->my_method_area->load_class(class_name);
    } catch(const Exception &e) {
        this->show_error(e);
        exit(EXIT_FAILURE);
    }

    class_space &method_class = this->my_method_area->get_class(class_name);
    // Tem que executar o iniciador da classe antes de prosseguir
    this->init_class(class_name);
    attribute_info* code_data = nullptr;

    for(u2 i = 0; i < m.attributes_count; i++) {
        
        if(m.attributes[i].att_name == "Code") {
            code_data = &(m.attributes[i]);
        }
    }

    if(code_data == nullptr) {
        std::stringstream buffer;
        std::string method_name, method_descriptor;

        buffer << "Metodo nao encontrado!\n";
        buffer << "Nome: " << method_name << "\n";
        buffer << "Classe: " << method_class.get_class_name() << "\n";

        throw ItemNotFoundError(buffer.str());
    }

    new_frame = new frame(*code_data, &method_class);

    this->my_java_stack->push(new_frame);

    while(this->my_pc->get_pc() < code_data->attr.Code.code_length) {
        //instrucao pah;
        //pah = alguma coisa;

        u1 next_op = code_data->attr.Code.code[this->my_pc->get_pc()];

        instruct* next_instruction;

        if(this->instructions.count(next_op) > 0) { // Achando a instrucao
            next_instruction = this->instructions[next_op];
        }
        else {
            std::cout << "[Warn] Instruction was not found, something may be missing!\n";
            std::cout << "Instruction op: " << next_op;
            this->my_pc->increment_pc();
            continue;
        }

        // Executa a instrucao
        my_pc->increment_pc(
            next_instruction
                (this->my_method_area, this->my_heap, this->my_java_stack, &this->my_java_stack->top(),
                code_data->attr.Code.code, this->my_pc->get_pc(), false)
        );

    }

}