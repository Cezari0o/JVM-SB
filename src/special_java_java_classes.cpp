#include "special_java_classes.h"

void java_special::PrintStream::print(Any &obj) {

    if(obj.is<Object*>()) {

        switch (obj.as<Object*>()->get_type()) {

        case FIELD_TYPES::ARRAY_TYPE:

            if(obj.as<Object*>()->single_value.as<Array_t*>()->my_data.front().is<char>()) {

                for(auto &it : obj.as<Object*>()->single_value.as<Array_t*>()->my_data) {
                    PrintStream::print(it);
                }
            } else {
                std::cout << '[';
                for(auto &it : obj.as<Object*>()->single_value.as<Array_t*>()->my_data) {
                    PrintStream::print(it);
                    std::cout << ", ";
                }
                std::cout << ']';
            }

            break;
        
        case FIELD_TYPES::STRING_TYPE:
            std::cout << obj.as<Object*>()->single_value.as<std::string>();
            break;

        case FIELD_TYPES::OBJECT_TYPE:

            std::cout << obj.as<Object*>()->get_class_name() << "@" << obj.as<Object*>();
            break;


        case FIELD_TYPES::CLASS_REF_TYPE:
            std::cout << obj.as<Object*>()->single_value.as<std::string>();
        default:
            std::cout << "object not found";
        }
    } else {
        std::string data_to_string = get_string_from_base_type(obj);
        std::cout << data_to_string;
    }
}

std::string java_special::PrintStream::get_string_from_base_type(Any &obj) {

    std::stringstream buffer_str; 

    if(obj.is<bool>()) {
        buffer_str << (obj.as<bool>() == true? "true" : "false");
    } else if(obj.is<u1>()) {
        buffer_str << (int) obj.as<u1>();
    } else if(obj.is<double>()) {
        buffer_str << obj.as<double>();
    } else if(obj.is<float>()) {
        buffer_str << obj.as<float>();
    } else if(obj.is<int>()) {
        buffer_str << obj.as<int>();
    } else if(obj.is<long>()) {
        buffer_str << obj.as<long>();
    }  else if(obj.is<short>()) {
        buffer_str << obj.as<short>();
    } else if(obj.is<u1>()) {
        buffer_str << obj.as<u1>();
    }

    return buffer_str.str();
}

void java_special::find_and_exec_method(const std::string &method_name, std::vector<Any> &args) {

    if(method_name == "print"){
        PrintStream::print(args.front());
    } else if(method_name == "println") {
        PrintStream::println(args.front());
    }

}


bool java_special::is_from_java_lang(const std::string class_name, const std::pair<std::string, std::string> &name_and_type) {
    std::vector<std::string> special_names = {
                                "println",
                                "print",
                                "out",
                                "System",
                                "PrintStream",
                                "append",
                                "toString"
                                };

    for(const std::string &s : special_names) {

        if(class_name.find(s) != std::string::npos or name_and_type.first.find(s) != std::string::npos) {
            return true;
        }
    }

    return false;
}
