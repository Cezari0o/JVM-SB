#include "interpreter.h"

int execution_engine::run() {

    std::string initial_class_name = this->initial_class_ref->get_class_name();
    std::pair<std::string, std::string> n_and_t = make_pair("main", "([Ljava/lang/String;)V");

    method_info main_met;
    try {
        main_met = (this->my_interpreter->my_method_area->get_method(initial_class_name, n_and_t));

    } catch(const Exception &e) {
        cerr << "Erro ao carregar metodo main!";
        cerr << "Classe inicial: " << initial_class_name << "\n";
        cerr << "Erro encontrado: " << e.what() << "\n";
        delete my_interpreter;
        exit(EXIT_FAILURE);
    } catch(const std::exception &e) {
        cerr << "Erro desconhecido!\n";
        cerr << "Erro: " << e.what() << "\n";
        delete my_interpreter;
        exit(EXIT_FAILURE);
    }

    std::vector<Any> args;
    this->my_interpreter->execute_method(initial_class_name, main_met, args);

    return 0;
}