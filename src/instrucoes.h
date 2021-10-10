#ifndef INSTRUCOES_H_
#define INSTRUCOES_H_

#include "data_areas.h"
#include "data_objects.h"
#include <vector>
#include <utility>
#include "str_func.h"
#include "descript_types.h"

// Instrucoes devem retornar a quantidade total de bytes que elas usaram do vetor de instrucoes
typedef int instruct(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

std::map<u1, instruct*> get_instructions();

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
        const u1* code_vector, int pc, bool is_wide);

int fadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int dadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int isub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int imul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int idiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ldiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fdiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);
        
int ddiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int irem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lrem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int frem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int drem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ineg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ishl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lshl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ishr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lshr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iand_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int land_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ior_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ixor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lxor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iinc_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);


// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int aaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int bipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int sipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Constantes

int aconst_null_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int iconst_m1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_4_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iconst_5_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);


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
        const u1* code_vector, int pc, bool is_wide);

int dload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int faload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int laload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int daload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int baload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int caload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int saload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Stack 

int swap_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int nop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

int pop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int pop2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup2_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dup2_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int wide_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide = false);

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// References

int anewarray_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int areturn_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int arraylength_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Stores referecens -----------------------------------------------------------------------------------

int astore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int astore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int astore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int astore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int astore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int astore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// int athrow_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
//         const u1* code_vector, int pc, bool is_wide);

// Stores tipos basicos ---------------------------------------------------------------------

int istore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Store ints ---------------------------------------------------------------------------------


int istore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int istore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int istore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int istore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);


// Store longs ---------------------------------------------------------------------------------

int lstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Store floats ---------------------------------------------------------------------------------
int fstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Store doubles ---------------------------------------------------------------------------------
int dstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Conversions -----------------------------------------------------------------------------------
int i2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int i2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int i2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int i2b_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int i2c_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int i2s_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int l2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int l2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int l2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int f2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int f2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int f2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int d2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int d2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int d2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

// Stores values to arraysrefs --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int iastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int lastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int castore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int sastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int aastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

//Comparison

int lcmp_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int fcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int dcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ifeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ifne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int iflt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ifle_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ifgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int ifge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmplt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmpge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmpgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_icmple_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_acmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int if_acmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int goto_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

int goto_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide);

#endif