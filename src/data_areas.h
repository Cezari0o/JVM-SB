/*!
* \file \src\data_areas.h
* \version 0.1
* \date 12/10/2021
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef DATA_AREAS_H_
#define DATA_AREAS_H_

/*! Importation of librairies*/
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <ostream>
#include <list>

#include "classes.h"
#include "any.h"
#include "except.h"
#include "str_func.h"
#include "data_objects.h"
#include "leitor.h"
#include "access_flags.h"
#include "descript_types.h"
#include "someTools.h"

/**
 * @brief Armazena o endereco de uma instrucao da JVM.
 *
 * @since	v0.0.1
 * @global
 */
class pc_register {

    private:
        int pc = 0;

    public:
        void set_pc(const int &v) { this->pc = v;}
        pc_register() { this->pc = 0; };
        ~pc_register() = default;
        int get_pc() const ;
        
        /**
         * @brief Incrementa o valor de pc por 1.
         *
         */
        void increment_pc();

        /**
         * @brief Incrementa o valor de pc pelo valor recebido.
         * 
         */
        void increment_pc(const int &);

        /**
         * @brief Incrementa o valor de pc pelo valor recebido. Retorna o resultado da 
         * operacao.
         * 
         * @return int 
         */
        int get_next_pc(const int &);

        // void operator+(const int &v) { this->increment_pc(v); }
        void operator+=(const int &v) { this->increment_pc(v); }
        void operator=(const int &v) { this->set_pc(v); }
        void operator=(const pc_register &pc_v) { this->set_pc(pc_v.get_pc()); }
};

/**
 * @class jvm_stack 
 * @brief Classe que armazena os frames da jvm.
 * 
 */
class jvm_stack {

    class frame* top_frame = nullptr;

    size_t stack_size = 0;
    static const size_t max_stack_size = 1e4;

    public:

        jvm_stack() = default;
        ~jvm_stack();

        /**
         * @brief Retorna o tamanho total da pilha de frames.
         * 
         * @return size_t 
         */
        size_t size() { return this->stack_size; };

        /**
         * @brief Armazena o ponteiro no topo da pilha de operandos na pilha atual.
         * 
         */
        void push(class frame*);

        /**
         * @brief Retira o frame do topo da pilha interna. Efetivamente destroi os dados 
         * do frame no topo da pilha. 
         * 
         */
        void pop();
        /**
         * @brief Retorna uma referencia para o frame no topo da pilha.
         * 
         * @return frame& 
         */
        class frame &top() { return *(this->top_frame); };

};


/**
 * @brief Classe utilizada para armazenar os dados de uma classe, representada por um classfile. 
 * Armazena os metodos, dados de fields e os fields estaticos.
 * 
 */
class class_space {

    private:
        std::string class_name;

        ClassFile *my_classfile;
        std::vector<cp_info> *runtime_cp;

        
    public:
        int count_objects = 0;


        int get_num_of_instance(bool to_increment = true) { 
            
            if(to_increment) {
                return this->count_objects++ % ((1 << 30));
            }
        
            else {
                return this->count_objects;
            }
        }

        /**
         * @brief Mapa que contem os dados de um fields estaticos. A chave indica o nome do 
         * field.
         * 
         */
        std::map<std::string, Field_t*> fields_data; // <- Contem os fields estaticos

        const std::vector<method_info> *methods_info;
        const std::vector<field_info>  *fields_info;

        Field_t *get_class_field(const std::string &name);
        method_info &get_method(const std::string &name, const std::string &descriptor) ;
        method_info get_method(const u2 &name_idx, const u2 &descriptor_idx) ;

        std::string get_class_name() const { return this->class_name; }
        class_space(ClassFile);
        class_space(ClassFile*);
        class_space() = default;
        ~class_space();

        /**
         * @brief Get the method object.
         * 
         * @param method_ref 
         * @return method_info 
         */
        method_info get_method(const cp_info &method_ref);

        /**
         * @brief Get the method object
         * 
         * @param method_idx 
         * @return method_info 
         */
        method_info get_method(const size_t &method_idx) { return this->methods_info->at(method_idx); }
        
        /**
         * @brief Get the field info object
         * 
         * @param field_idx 
         * @return field_info 
         */
        field_info  get_field_info(const size_t field_idx) { return this->fields_info->at(field_idx); }

        /**
         * @brief Get the class file object
         * 
         * @return const ClassFile& 
         */
        const ClassFile &get_class_file() const { return *(this->my_classfile); }

        /**
         * @brief Get the class field object
         * 
         * @param name_idx 
         * @return Field_t* 
         */
        Field_t *get_class_field(const u2 &name_idx);

        /**
         * @brief Get the class field object
         * 
         * @param field_ref 
         * @return Field_t* 
         */
        Field_t *get_class_field(const cp_info &field_ref); // <- Talvez arrumar !!!!!!!!!!!!!!!!!!!!!

        /**
         * @brief Get the const pool object
         * 
         * @return std::vector<cp_info>& 
         */
        std::vector<cp_info> &get_const_pool() { return this->my_classfile->constant_pool; }; // When call this function, do not alter the result!!! 

        /**
         * @brief Construct a new class space object
         * 
         * @param cp 
         */
        class_space(const class_space &cp) {
            *this = cp;
        }

        class class_space&operator=(const class_space& cp);
};

/**
 * @brief Area de metodos da JVM. Armazena as classes carregadas.
 * 
 * @sa class_space
 */
class method_area {

    std::map<std::string, class_space> classes;

    void prepare_class(std::string &class_name);
    bool is_sub_class(class_space &some_class, class_space &super_class);

    // friend class interpreter;

    public:
    
        /**
         * @brief Procura e retorna uma referencia para uma classe, recebendo o nome dela.
         * Pode lancar excecoes caso a classe nao esteja carregada.
         * 
         * @param class_name 
         * @return class_space& 
         */
        class_space &get_class(const std::string &class_name); // <- Apenas recupera a classe, sem verificar flags de acesso
        method_area() = default;
        method_area(const std::string &_class_path) {
            this->load_class(_class_path);
        }

        /**
         * @brief Retorna um metodo de uma classe. Pode lancar excecoes, caso a classe requerida nao 
         * esteja carregada.
         * 
         * @param class_name 
         * @param name_and_type 
         * @return const method_info& 
         */
        const method_info &get_method(const std::string &class_name, const std::pair<std::string, std::string> &name_and_type);

        ~method_area() = default;
        
        /**
         * @brief Constroi uma nova classe, a partir da referencia de class file recebida. 
         * 
         */
        void insert_new_class(ClassFile*);
        // method_info get_method();

        /**
         * @brief Retira uma classe. Indicada pelo nome recebido.
         * 
         * @param class_name 
         */
        void remove_class(const std::string& class_name);

        // template<class T>
        // T &get_item(const cp_info &ref_item); // <-- provisorio (ainda nao implementado)

        /**
         * @brief Retorna uma classe, indicada pelo seu nome. A classe sera carregada caso nao esteja.
         * Verifica as flags de acesso a partir da classe chamadora. 
         * 
         * @param calling_class 
         * @param class_name 
         * @return class_space& 
         */
        class_space &get_class(class_space* calling_class, const std::string &class_name); // <-- Carrega a classe se ela ainda nao ta na area de metodos
        //              ^
        //              |
        //              |
        // Talvez arrumar para considerar arrays!!!

        /**
         * @brief Retorna um field de classe, indicado pelo nome da classe. Carrega a classe, caso a mesma nao esteja na area 
         * de metodos. Verifica as flags de acesso da classe chamada. Pode lancar excecoes. 
         * 
         * @param calling_class 
         * @param class_name 
         * @param name_and_type 
         * @param from_object 
         * @return Field_t& 
         */
        Field_t &get_class_field(class_space *calling_class, const std::string &class_name, const std::pair<std::string, std::string>& name_and_type, bool from_object = false);

        /**
         * @brief Retorna todos os fields de um novo objeto. Carrega as classes, superclasses e interfaces da classe 
         * que o objeto representa, e retorna os fields encontrados nessas classes, caso nao sejam estaticos.
         * 
         * @param calling_class 
         * @param class_name 
         * @param to_return_fields 
         */
        void get_fields_from_obj(class_space *calling_class, const std::string &class_name, std::vector<std::pair<std::string, Field_t*>> &to_return_fields);

        /**
         * @brief Retorna um metodo de classe, verificando as flags de acesso a classe chamada. Carrega a classe chamada 
         * caso a mesma nao esteja carregada.
         * 
         * @param calling_class 
         * @param class_name 
         * @param name_and_type 
         * @return method_info 
         */
        method_info get_class_method(class_space *calling_class, const std::string &class_name, const std::pair<std::string, std::string> &name_and_type);


        /**
         * @brief Retorna um metodo de interface, de acordo com o processo especificado no manual 
         * da JVM 8. Encontre este no site da Oracle.
         * 
         * @param calling_class 
         * @param interface_name 
         * @param name_and_type 
         * @return method_info 
         */
        method_info get_interface_method(class_space *calling_class, const std::string &interface_name, const std::pair<std::string, std::string> &name_and_type);

        /**
         * @brief Carrega uma classe, a partir do caminho recebido.
         * 
         * @param _class_path 
         */
        void load_class(const std::string &_class_path);

        /**
         * @brief Verifica se uma dada classe esta carregada.
         * 
         * @param _class_path 
         * @return true 
         * @return false 
         */
        bool is_loaded(const std::string &_class_path) {

            // for(const auto &it : this->classes) {
            //     if(not _class_path.compare(it.first)) {
            //         return true;
            //     }
            // }

            return this->classes.count(_class_path) > 0;
        };
        
        /**
         * @brief Retorna a quantidade de classes carregadas.
         * 
         * @return size_t 
         */
        size_t size() { return classes.size(); };

};

/**
 * @brief Armazena os dados de uma frame. Contem um vetor de variaveis locais, a pilha de operandos, 
 * uma referencia para o pool de constantes, e uma referencia para o espaco da classe.
 * 
 * @sa class_space, ClassFile
 */
class frame {

    private:
        class frame *next_frame = nullptr;

        size_t max_locals;
        size_t max_stack;

        size_t stack_real_size = 0;

    public:
        std::stack<Any> operand_stack;
        std::vector<Any> local_vars; // <- Arrumar para considerar operacoes utilizando longs e doubles
        
        class class_space* cs_ref;
        std::vector<cp_info> *cp_ref;

        template<class T>
        T &get_local_var(size_t idx) {
            return this->local_vars.at(idx).as<T>();
        }
        
        template<class T>
        void push_stack(const T &v) {

            Any value(v);

            while(value.is<Any>()) {
                value = value.as<Any>();
            }

            // if(this->stack_real_size + 1 == this->max_stack)  // Tem q verificar, talvez
            //     throw Exception("Max operand stack size reached!");


            if(value.is<long long>() or value.is<double>()) {
                this->stack_real_size += 2;
            }

            else {
                this->stack_real_size++;
            }

            this->operand_stack.push(value);
        }

        void pop_stack();

        Any &top_stack() { return this->operand_stack.top(); };

        template<class T>
        T get_top_and_pop_stack() {
            T toReturn = this->top_stack().as<T>();
        
            this->pop_stack();
        
            return toReturn;
        }

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


/**
 * @brief Armazena os objetos alocados dinamicamente da JVM.
 * 
 */
class heap {

    private:
        std::list<Object*> objects_list;

    public:

        heap() = default;

        ~heap() { 
            
            for(auto it = this->objects_list.begin(); it != this->objects_list.end(); it++)
                delete (*it);

        }

        Object* pushRef(Object* obj_ref) {
            this->objects_list.push_back(obj_ref);
            return this->objects_list.back();
        }

        std::list<Object*> &get_objects() { return this->objects_list; }

};


#endif