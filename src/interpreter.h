/*!
* \file \src\interpreter.h
* \version 0.1
* \date 12/10/2021
* \brief 
* \remarks None
* 
*/

#ifndef EXECUTION_ENGINE_H_
#define EXECUTION_ENGINE_H_

/*! Importation of librairies*/
#include "data_areas.h"
#include "leitor.h"
#include "except.h"
#include "instrucoes.h"
#include <string>
#include <sstream>

std::string get_class_from_path(const std::string &path);

/**
 * execution_engine.
 *
 * @author	Unknown
 * @since	v0.0.1
 * @version	v1.0.0	Tuesday, October 12th, 2021.
 * @global
 */
class execution_engine {

    interpreter* my_interpreter;
    class_space* initial_class_ref;

    public:
        execution_engine(const std::string &initial_class_name) {
            this->my_interpreter = interpreter::get_instance(initial_class_name);
            this->initial_class_ref = my_interpreter->initial_class_ref;
        };

        ~execution_engine() {
            delete my_interpreter;
        }

        int run();
};

#endif