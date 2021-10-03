#ifndef DATA_OBJECTS_H_
#define DATA_OBJECTS_H_

#include <map>
#include <sstream>
#include <vector>
#include "any.h"
#include "except.h"

class Object {

    private:
    std::string class_name;
    std::string my_name; // <- ???
    std::map<std::string, class Field_t*> my_fields;
    Any single_value; // <- Para uso por outros tipos de classes, como Arrays por exemplo

    public:

    template<class T>
    T &get_value() { return single_value.as<T>(); };

    Object(const std::string &class_name) { this->class_name = class_name; }
    Object(const std::string &class_name, Any value) {
        this->single_value = value;
        this->class_name = class_name;
    }
    Object();
    
    ~Object() {
        for(auto &it : this->my_fields) {
            delete it.second;
        }

        if(single_value.is<Array_t*>()) {
            delete single_value.as<Array_t*>();
        }
    };

    std::string get_class_name() { return this->class_name; }

    void add_field(const std::string &field_name, Field_t* field_data) { this->my_fields[field_name] = field_data; };

    template<class T>
    void add_field(const std::string &field_name, const T &value) {
        Field_t *field_with_value = new Field_t(value);

        this->my_fields[field_name] = field_with_value;
    }


    template<class T>
    T &get_field(const std::string &field_name) { 
        if(my_fields.count(field_name) > 0)
            return my_fields[field_name]->get_d<T>();

        std::stringstream error_buffer;

        error_buffer << "O nome do field nao foi encontrado neste objeto!\n";
        error_buffer << "Field requisitado: " << field_name;
        error_buffer << "Nome da classe: " << this->class_name;

        throw ItemNotFoundError(error_buffer.str());
    };
};

class Field_t {

    private:
        Any data;
        int data_type = 0;

    public:

    Field_t() = default;

    template<class T>
    Field_t(const T &value) { this->data = value; }
    ~Field_t() { if (this->data.is<Array_t *>()) {
                    delete this->data.as<Array_t *>();
                 }
               };

    template<class T>
    T &get_d() { return this->data.as<T>(); }

    template<class T>
    T &set_field(const T &value) {  this->data = value;
                                    return this->get_d<T>();
                                 }

    template<class T>
    T &operator=(const T &value) { return this->set_field(value); }
};


class Array_t {

    private:
        std::vector<Any> my_data;
        int my_type;

    public:

        Array_t(int type) { this->my_type = type; }

        Array_t(int type, size_t size) { 
            this->my_type = type;
            my_data.resize(size);     
        }

        ~Array_t() = default;

        int get_type() { return this->my_type; }

        size_t size() { return this->my_data.size(); }

        template<class T>
        T &at(size_t idx) { return this->my_data.at(idx).as<T>(); }

        template<class T>
        T &operator[](size_t idx) { return this->at(idx); }
};

#endif