/**
 * @file special_java_classes.h
 * 
 * @brief Contem a definicao de algumas classes que simulam acoes do pacote java, como impressao no terminal.
 * 
 * @global
 */
#ifndef SPECIAL_JAVA_CLASSES_H_
#define SPECIAL_JAVA_CLASSES_H_

#include "any.h"
#include <iostream>
#include <string>
#include "someTools.h"
#include "data_objects.h"
#include <sstream>
#include <utility>

namespace java_special {

    bool is_from_java_lang(const std::string &class_name, const std::pair<std::string, std::string> &name_and_type);
    bool is_from_java_lang(const std::string &str);

    void find_and_exec_method(const std::string &method_name, std::vector<Any> &args);
    class PrintStream {

        PrintStream() = default;

        static std::string get_string_from_base_type(Any &obj);

        public:


        static void println(Any &obj) { 

            PrintStream::print(obj);
            std::cout << '\n';
        };
        static void println(){ std::cout << "\n"; };

        static void print(Any &obj);
    };





};




#endif