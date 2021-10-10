#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "data_areas.h"
#include "leitor.h"
#include "except.h"
#include "instrucoes.h"
#include <string>
#include <sstream>

std::string get_class_from_path(const std::string &path);

class interpreter {

    private:

        std::map<u1, instruct*> instructions;

        void show_error(const Exception &e) {

            std::cerr << "Erro na execucao!\n";
            std::cerr << "Excecao encontrada: " << e.get_exception_name() << "\n";
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Terminando a execucao do programa!";

            this->~interpreter();
        };

        class class_space* initial_class_ref; 

        void init_class() { this->init_class(this->initial_class_ref->get_class_name()); };
    public:

        class method_area* my_method_area;
        class heap*        my_heap;
        class jvm_stack*   my_java_stack;
        class pc_register* my_pc;

        void init_class(const std::string &class_name);
        void execute_method(const std::string &class_name, const method_info &m);

        interpreter(const std::string &initial_class_name);
        ~interpreter();

};

#endif