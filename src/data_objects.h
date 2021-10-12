/*!
* \file \src\data_objects.h
* \version 0.1
* \date 12/10/2021
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef DATA_OBJECTS_H_
#define DATA_OBJECTS_H_

/*! Importation of librairies*/
#include <map>
#include <sstream>
#include <vector>
#include "any.h"
#include "descript_types.h"
#include "except.h"

class Array_t {

    private:
        int my_type;
        size_t array_size = 0;

    public:
        std::vector<Any> my_data;

        Array_t() = default;
        Array_t(int size) { this->my_data.resize(size); }

        Array_t(size_t size, int type) { 
            this->my_type = type;
            my_data.resize(size);     
        }

        ~Array_t() = default;

        int get_type() { return this->my_type; }

        size_t size() { return this->my_data.size(); }

        template<class T>
        T &at(size_t idx) { return this->my_data.at(idx).as<T>(); }

        template<class T>
        T &operator[](size_t idx) { return this->my_data.at(idx).as<T>(); }
};

class Field_t {

    private:
        int data_type = 0;

    public:
        Any data;

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

    Field_t &operator=(const Field_t &f) {
        this->data = f.data;
        return (*this);
    }
};


class Object {

    private:
    std::string class_name;
    std::string my_name; // <- ???
    int type;

    public:
    std::map<std::string, class Field_t*> my_fields;

    // template<class T>
    // void delete_field(Field_t* field) {
    //     Any h;
    //     h.~Any
    // }

    Any single_value; // <- Para uso por outros tipos de classes, como Arrays por exemplo
    int my_number;

    template<class T>
    T &get_value() { return single_value.as<T>(); };

    Object(const std::string &class_name) { this->class_name = class_name; }
    Object(const std::string &class_name, Any value) {
        this->single_value = value;
        this->class_name = class_name;
    }

    Object(const std::string &class_name, Any value, bool type): Object(class_name, value) {
        this->type = type;       
    }
    Object() = default;
    
    int get_type() { return type; }
    void set_type(int type) { this->type = type; }

    ~Object() {

        // for_each(this->my_fields.begin(), this->my_fields.end(), 
        // [] (pair<const std::string, Field_t*> &value) {
        //     Field_t* field_to_del = value.second;
        //     delete field_to_del;
        // });

        for(auto &it : this->my_fields) {
            delete it.second;
        }

        if(single_value.is<Array_t*>()) {
            Array_t* to_del = single_value.as<Array_t*>();
            delete to_del;
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

#endif