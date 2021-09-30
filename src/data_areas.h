#ifndef DATA_AREAS_H_
#define DATA_AREAS_H_

#include <vector>
#include <stack>
#include <map>
#include <string>

#include "classes.h"
#include "any.h"
#include "except.h"
#include "str_func.h"
#include "data_objects.h"
#include "leitor.h"
#include "access_flags.h"
#include "descript_types.h"

class pc_register {

    private:
        int pc = 0;

    public:
        void set_pc(const int &v) { this->pc = v;}
        pc_register();
        ~pc_register() = default;
        int get_pc() const ;
        
        void increment_pc();
        void increment_pc(const int &);

        int get_next_pc(const int &);

        void operator+(const int &v) { this->increment_pc(v); }
        void operator=(const int &v) { this->set_pc(v); }
        void operator=(const pc_register &pc_v) { this->set_pc(pc_v.get_pc()); }
};

class jvm_stack {

    class frame* top_frame = nullptr;

    size_t stack_size = 0;
    static const size_t max_stack_size = 1e5;

    public:

        jvm_stack() = default;
        ~jvm_stack();
        size_t size() { return this->stack_size; };

        void push(class frame*);
        void pop();
        class frame &top() { return *(this->top_frame); };

};

class class_space {

    private:
        std::string class_name = "";

        ClassFile *my_classfile;
        std::vector<cp_info> *runtime_cp;


        std::map<std::string, Field_t*> fields_data; // <- Contem os fields estaticos

        
    public:

        const std::vector<method_info> *methods_info;
        const std::vector<field_info>  *fields_info;

        Field_t *get_class_field(const std::string &name);
        method_info get_method(const std::string &name, const std::string &descriptor) ;
        method_info get_method(const u2 &name_idx, const u2 &descriptor_idx) ;

        std::string get_class_name() const { return this->class_name; }
        class_space(ClassFile*);
        ~class_space();

        method_info get_method(const cp_info &method_ref);

        method_info get_method(const size_t &method_idx) { return this->methods_info->at(method_idx); }
        field_info  get_field_info(const size_t field_idx) { return this->fields_info->at(field_idx); }

        
        Field_t *get_class_field(const u2 &name_idx);
        Field_t *get_class_field(const cp_info &field_ref); // <- Talvez arrumar !!!!!!!!!!!!!!!!!!!!!
        std::vector<cp_info> &get_const_pool() { return *(this->runtime_cp); }; // When call this function, do not alter the result!!! 


};

class method_area { // <- Arrumar

    std::map<std::string, class_space> classes;

    void prepare_class(std::string &class_name);

    public:
        method_area() = default;
        method_area(const std::string &_class_path) {
            this->load_class(_class_path);
        }

        ~method_area();
        
        void insert_new_class(ClassFile*);
        // method_info get_method();
        void remove_class(const std::string& class_name);
        class_space &get_class(const std::string &class_name);

        template<class T>
        T &get_item(const cp_info &ref_item); // <-- provisorio (ainda nao implementado)

        void load_class(const std::string &_class_path);

        bool is_loaded(const std::string &_class_path) {

            for(const auto &it : this->classes) {
                if(_class_path.find(it.first) != std::string::npos) {
                    return true;
                }
            }

            return false;
        };
        
        size_t size() { return classes.size(); };

};

class frame {

    private:
        class frame *next_frame = nullptr;
        class class_space* cs_ref;
        std::vector<cp_info> *cp_ref;

        size_t max_locals;
        size_t max_stack;

        size_t stack_real_size = 0;
        std::stack<Any> operand_stack;
        std::vector<Any> local_vars; // <- Arrumar para considerar operacoes utilizando longs e doubles

    public:

        template<class T>
        T &get_local_var(size_t idx) {
            return this->local_vars.at(idx).as<T>();
        }
        
        template<class T>
        void push_stack(const T &);

        void pop_stack();

        template<class T>
        T &top_stack() { return this->operand_stack.top().as<T>(); };

        template<class T>
        T get_top_and_pop_stack();

        size_t size_stack() { return this->stack_real_size; }
        size_t max_size_stack() { return this->max_stack; }
        size_t size_locals() { return this->local_vars.size(); }
        
        frame(size_t max_stack_s, size_t max_locals_s, class_space* class_ref, frame* next_frame = nullptr);        
        frame(const attribute_info& code, class_space* class_ref, frame* next_frame = nullptr);

        ~frame() = default; // <- Nao eh pra deletar nenhuma memoria apontada
        // pelos ponteiros do frame

        void set_next_frame(class frame *next_frame) { this->next_frame = next_frame; };
        frame* get_next_frame_ref() { return this->next_frame; }
        // std::vector<Any> & get_local_vars() { return this->local_vars; };
        // std::stack<Any> & get_operands() { return this->operand_stack; };

};



#endif