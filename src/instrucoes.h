#ifndef INSTRUCOES_H_
#define INSTRUCOES_H_

#include <vector>
#include <utility>
#include <algorithm>
#include "data_areas.h"
#include "data_objects.h"
#include "str_func.h"
#include "descript_types.h"
#include "special_java_classes.h"

// Instrucoes devem retornar a quantidade total de bytes que elas usaram do vetor de instrucoes
typedef int instruct(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

std::map<u1, instruct*> get_instructions();

typedef struct interpreter {

    void show_error(const Exception &e) {

            std::cerr << "Erro na execucao!\n";
            std::cerr << "Excecao encontrada: " << e.get_exception_name() << "\n";
            std::cerr << "Erro: " << e.what() << "\n";
            std::cerr << "Terminando a execucao do programa!\n";

            this->~interpreter();
    };

    protected:
    static struct interpreter* the_interpreter;
    interpreter(const std::string &initial_class_name);
    interpreter() = default;

    public:
    // fazer metodo para iniciar objetos!!
    void init_obj(const std::string &class_name, Object* new_obj);
    void init_class(const std::string &class_name);
    std::map<std::string, bool> initialized_classes;

    static struct interpreter* get_instance(const std::string &initial_class_name) {
        if(the_interpreter == nullptr) {
            the_interpreter = new interpreter(initial_class_name);
        }

        return the_interpreter;
    };

    static struct interpreter* get_instance() {
        return the_interpreter;
    };
    
    ~interpreter();
    class class_space* initial_class_ref; 
    std::map<u1, instruct*> instructions;

    class method_area* my_method_area;
    class heap*        my_heap;
    class jvm_stack*   my_java_stack;
//     class pc_register* my_pc;

    void execute_method(const std::string &class_name, const method_info &m, std::vector<Any> &args);

} interpreter;


// ------------------------------------------------------------------------------------------------------------------------
// Templates
template<class T>
int type_store_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

template<class T>
int type_const_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, T VALOR_CONST);

template<class T>
int type_store_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, T VALOR_CONST);

template<class T>
int a_store_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, int VALOR_CONST);

template<class T, typename Comp>
int type_math_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, Comp oper);

template<class T, class U>
int typeT_2_typeU_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

template<class T>
int type_comp_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, int aux);

template<class T>
int type_astore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

template<class U>
int i2_typeU_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

template<typename Comp>
int type_if_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, Comp oper);

// -----------------------------------------------------------------------------------------------------------------
// Instrucoes

int iadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int ladd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int dadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int isub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int imul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int idiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ldiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fdiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);
        
int ddiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int irem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lrem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int frem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int drem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ineg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ishl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lshl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ishr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lshr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iand_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int land_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ior_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ixor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lxor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iinc_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int aaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int bipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int sipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Constantes

int aconst_null_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int iconst_m1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_4_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iconst_5_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Loads

int aload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int aload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int aload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int aload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int aload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int dload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int faload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int laload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int daload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int baload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int caload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int saload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Stack 

int swap_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int nop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int pop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int pop2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup2_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dup2_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int wide_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// References

int anewarray_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int areturn_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int arraylength_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int athrow_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Stores referecens -----------------------------------------------------------------------------------

int astore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int astore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int astore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int astore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int astore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int astore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// int athrow_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
//         const u1* code_vector, int pc, bool is_wide);

// Stores tipos basicos ---------------------------------------------------------------------

int istore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Store ints ---------------------------------------------------------------------------------


int istore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int istore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int istore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int istore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);


// Store longs ---------------------------------------------------------------------------------

int lstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Store floats ---------------------------------------------------------------------------------
int fstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Store doubles ---------------------------------------------------------------------------------
int dstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Conversions -----------------------------------------------------------------------------------
int i2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int i2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int i2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int i2b_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int i2c_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int i2s_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int l2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int l2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int l2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int f2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int f2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int f2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int d2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int d2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int d2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

// Stores values to arraysrefs --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int iastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int lastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int castore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int sastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int aastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

//Comparison

int lcmp_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int fcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int dcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int iflt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifle_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmplt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmpge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmpgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_icmple_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_acmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int if_acmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int goto_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int goto_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifnull_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

int ifnonnull_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, bool &end_execution);

#endif