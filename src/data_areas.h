#ifndef DATA_AREAS_H_
#define DATA_AREAS_H_

#include "classes.h"
#include "jvm_types.h"
#include <vector>
#include <stack>
#include "any.h"
#include "except.h"

class pc_register {

    private:
        int pc = 0;

        void set_pc(const int &v) { this->pc = v;}

    public:

        pc_register();
        int get_pc();
        
        void increment_pc();
        void increment_pc(const int &);

        int get_next_pc(const int &);

        void operator+(const int &v) { this->increment_pc(v); }
};

class jvm_stack {

    class frame* top_frame = nullptr;

    size_t stack_size = 0;
    static const size_t max_stack_size = 1e5;

    public:

        jvm_stack();
        ~jvm_stack();
        size_t size() { return this->stack_size; };

        void push(class frame*);
        void pop();
        class frame &top() { return *(this->top_frame); };

};

class class_space { // (<- Arrumar) Ainda nao sei o que eu faco

    private:

        ClassFile *my_classfile;
        std::vector<cp_info> *runtime_cp;
        std::vector<method_info*> methods_data;
        std::vector<field_info*> fields_data;

        std::string class_name = "";

    public:

        class_space();
        ~class_space();

        method_info get_method(const u2 & cp_index);
        field_info &get_class_field(const u2 &cp_index);
        std::vector<cp_info> *get_const_pool() { return this->runtime_cp; };

};

class method_area { // <- Talvez arrumar

    std::vector<class_space> classes;
    // void push_back(class_info) { this->classes.push_back(class_info); }
    // void push_back(method_info *mi) { this->methods.push_back(mi); }
    // void pop_back() { this->classes.pop_back(); };

    public:
        method_area();
        ~method_area();
        
        void insert_new_class(const ClassFile*);
        // method_info get_method();
        void remove_class(const std::string& class_name);
        void load_class(const std::string &class_name);

        size_t size() { return classes.size(); };

};

class frame {

    private:
        class frame *next_frame = nullptr;
        class_space* cs_ref;
        std::vector<cp_info> *cp_ref;

        size_t max_locals;
        size_t max_stack;

        size_t stack_real_size = 0;
        std::stack<Any> operand_stack;

    public:

        std::vector<Any> local_vars; // <- Arrumar para considerar operacoes utilizando longs e doubles
        
        template<class T>
        void push_stack(const T &);

        void pop_stack();

        template<class T>
        T &top_stack() { return this->operand_stack.top().as<T>(); };

        template<class T>
        T get_top_and_pop_stack();

        size_t size_stack() { return this->stack_real_size; }
        size_t size_locals() { return this->local_vars.size(); }
        
        frame(size_t max_stack_s, size_t max_locals_s, class_space* class_ref, frame* next_frame = nullptr);        
        frame(const attribute_info& code, class_space* class_ref, frame* next_frame = nullptr);

        void set_next_frame(class frame *next_frame) { this->next_frame = next_frame; };
        frame* get_next_frame_ref() { return this->next_frame; }
        // std::vector<Any> & get_local_vars() { return this->local_vars; };
        // std::stack<Any> & get_operands() { return this->operand_stack; };

};



#endif