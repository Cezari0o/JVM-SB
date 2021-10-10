#include "instrucoes.h"

typedef int returnAddress;

bool is_cat2(const Any &v) {

    return v.is<long>() or v.is<double>();
}

bool is_cat1(const Any &v) {

    return not is_cat2(v);
}

int nop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return 1;
}

int pop_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

    my_frame->pop_stack();

    return 1;            
}

int pop2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

    my_frame->pop_stack();
    my_frame->pop_stack();

    return 1;            
}

int dup_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value = my_frame->top_stack();
    my_frame->push_stack(value);
    
    return 1;
    
}

int dup_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value1 = my_frame->top_stack();
    my_frame->pop_stack();

    Any value2 =  my_frame->top_stack();
    my_frame->pop_stack();

    my_frame->push_stack(value1);      
    my_frame->push_stack(value2);
    my_frame->push_stack(value1);

    return 1;
        
}

int dup_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value1 = my_frame->top_stack();
    my_frame->pop_stack();

    Any value2 =  my_frame->top_stack();
    my_frame->pop_stack();


    if(is_cat2(value2)) {
        my_frame->push_stack(value1);      
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
    }

    else {
        
        Any value3 =  my_frame->top_stack();
        my_frame->pop_stack();
        
        my_frame->push_stack(value1);
        my_frame->push_stack(value3);
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
        
    }
    

    return 1;
        
}

int dup2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value1 = my_frame->top_stack();
    my_frame->pop_stack();

    if(is_cat2(value1)){
        my_frame->push_stack(value1);
        my_frame->push_stack(value1);
    }
    else{
        Any value2 =  my_frame->top_stack();

        my_frame->push_stack(value1);
        
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
    }

          
    return 1;
    
}


int dup2_x1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value1 = my_frame->top_stack();
    my_frame->pop_stack();

    Any value2 =  my_frame->top_stack();
    my_frame->pop_stack();


    if(is_cat2(value1)) {
        my_frame->push_stack(value1);      
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
    }

    else {
        
        Any value3 =  my_frame->top_stack();
        my_frame->pop_stack();
        
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
        my_frame->push_stack(value3);
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
        
    }
    
    return 1;
}

int dup2_x2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    Any value1 = my_frame->top_stack();
    my_frame->pop_stack();

    Any value2 =  my_frame->top_stack();
    my_frame->pop_stack();

    Any value3 =  my_frame->top_stack();

    if(is_cat2(value1) and is_cat2(value2)){
        my_frame->push_stack(value1);      
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
               
    }
    else if(is_cat2(value3) and is_cat2(value2)){

        my_frame->pop_stack();
        
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
        my_frame->push_stack(value3);
        my_frame->push_stack(value2);
        my_frame->push_stack(value1); 
    }
    else if(is_cat2(value1)){

        my_frame->pop_stack();
        
        my_frame->push_stack(value1);
        my_frame->push_stack(value3);
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);        
    }
    else{
        my_frame->pop_stack();

        Any value4 =  my_frame->top_stack();
        my_frame->pop_stack();       
        
        my_frame->push_stack(value2);
        my_frame->push_stack(value1);
        my_frame->push_stack(value4);
        my_frame->push_stack(value3);
        my_frame->push_stack(value2);
        my_frame->push_stack(value1); 
    }


    return 1;
}

int swap_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
        
        Any value_1 = my_frame->top_stack();
        my_frame->pop_stack();

        Any value_2 = my_frame->top_stack();
        my_frame->pop_stack();

        // value_1 = my_frame->get_top_and_pop_stack<Any>();
        // value_2 = my_frame->get_top_and_pop_stack<Any>();

        my_frame->push_stack(value_1);
        my_frame->push_stack(value_2);
        
        return 1;   
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Math

int iadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x + y;});
}

int ladd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x + y;});
}

int fadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<float>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](float  x, float y) { return x + y;});
}

int dadd_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<double>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](double x, double y) { return x + y;});
}

int isub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x - y;});
}

int lsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x - y;});
}

int fsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<float>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](float  x, float y) { return x - y;});
}

int dsub_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<double>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](double x, double y) { return x - y;}); 
}

int imul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x * y;});
}

int lmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x * y;});
}

int fmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<float>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](float  x, float y) { return x * y;});
}

int dmul_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<double>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](double x, double y) { return x * y;});
}

int idiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x / y;});
}

int ldiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x / y;});
}

int fdiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<float>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](float  x, float y) { return x / y;});
}

int ddiv_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<double>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](double x, double y) { return x / y;});
}

int irem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x % y;});
}

int lrem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x % y;});
}

int frem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<float>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](float  x, float y) { return (float) ((int )x % (int)y);});
}

int drem_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<double>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](double x, double y) { return  (double) ((long )x % (long) y);});
}

int ineg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    
    int value_1;

    value_1 = my_frame->get_top_and_pop_stack<int>();

    int result = ~value_1+1;

    my_frame->push_stack(result);

    return 1;
}

int lneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    
    long value_1;

    value_1 = my_frame->get_top_and_pop_stack<long>();

    long result = ~value_1+1;

    my_frame->push_stack(result);

    return 1;
}

int fneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    
    float value_1;

    value_1 = my_frame->get_top_and_pop_stack<float>();

    float result = value_1*(-1.0);

    my_frame->push_stack(result);

    return 1;
}

int dneg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    
    double value_1;

    value_1 = my_frame->get_top_and_pop_stack<double>();

    double result = value_1*(-1.0);

    my_frame->push_stack(result);

    return 1;
}

int ishl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x << y;});
}

int lshl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x << y;});
}

int ishr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x >> y;});
}

int lshr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x >> y;});
}

int iushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    // return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
    //     code_vector, pc, is_wide, [](int x, int y) { return x << y;});

    int value2 = my_frame->get_top_and_pop_stack<int>();    
    int value1 = my_frame->get_top_and_pop_stack<int>();    

    int s = value2 & 0x1f;

    if(value1 >= 0)
        my_frame->push_stack(value1 >> s);
    
    else 
        my_frame->push_stack((value1 >> s) + (2 << ~s));

    return 1;

}

int lushr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    // return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
    //     code_vector, pc, is_wide, [](long x, long y) { return x << y;});

    long value2 = my_frame->get_top_and_pop_stack<long>();    
    long value1 = my_frame->get_top_and_pop_stack<long>();    

    long s = value2 & 0x3f;

    if(value1 >= 0)
        my_frame->push_stack(value1 >> s);
    
    else 
        my_frame->push_stack((value1 >> s) + (2l << ~s));

    return 1;
}

int iand_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x & y;});
}

int land_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x & y;});
}

int ior_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x | y;});
}

int lor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x | y;});
}

int ixor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<int>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](int x, int y) { return x ^ y;});
}

int lxor_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    return type_math_num_i<long>(m_area, heap_area, java_stack, my_frame,
        code_vector, pc, is_wide, [](long x, long y) { return x ^ y;});
}


int iinc_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes;

    if(is_wide) {
        advance_bytes = 5;
        int index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        int constant = (short) ((code_vector[pc + 3] << 8) | code_vector[pc + 4]);

        my_frame->local_vars.at(index).as<int>() += constant;


    } else {
        advance_bytes = 3;

        int index = code_vector[pc + 1];
        int constant = (char) code_vector[pc + 2];

        my_frame->local_vars.at(index).as<int>() += constant;
    }

    return advance_bytes;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int aaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int index = my_frame->get_top_and_pop_stack<int>();
    Object* arrayref = my_frame->get_top_and_pop_stack<Object*>();

    if(index >= arrayref->single_value.as<Array_t*>()->size()) {
        throw ArrayIndexOutOfBoundsException("Index: " + std::to_string(index));
    }

    if(arrayref->single_value.is_null())
        throw NullPointerException("Nao eh possivel acessar ponteiros nulos!");

    my_frame->push_stack(arrayref->single_value.as<Array_t*>()->my_data.at(index));

    return 1;
}

// -------------------------------------------------------------------------------------------
// bipush
int bipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int byte = (char) code_vector[pc + 1];

    my_frame->push_stack(byte);

    return 2;
}

int sipush_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

    int val_short = (short) ((code_vector[pc + 1] << 8) | code_vector[pc + 2]);

    my_frame->push_stack(val_short);
    
    return 3;
}

int ldc_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int index = code_vector[pc + 1];

    cp_info value_from_cp = my_frame->cs_ref->get_const_pool().at(index);
    std::string str_val, class_name;

    switch (value_from_cp.tag) {
    case Float_info_value:

        float value = getFloatVal(value_from_cp);
        my_frame->push_stack(value);
        break;

    case Int_info_value:

        my_frame->push_stack((int) value_from_cp.Const.Integer_info.bytes);
        break;
    
    case String_info_value:

        str_val = constantToString(value_from_cp, my_frame->cs_ref->get_const_pool()).front();

        Object* new_str = new Object();
        new_str->set_type(FIELD_TYPES::STRING_TYPE);
        new_str->single_value = str_val;

        heap_area->pushRef(new_str);

        my_frame->push_stack(new_str);
        break;

    case Class_info_value:

        class_name = constantToString(value_from_cp, my_frame->cs_ref->get_const_pool()).front();

        m_area->load_class(class_name);

        Object* new_class_ref = new Object();

        new_class_ref->set_type(FIELD_TYPES::CLASS_REF_TYPE);
        class_space &the_class = m_area->get_class(class_name);

        new_class_ref->single_value = the_class.get_class_name();

        my_frame->push_stack(new_class_ref);
        break; 
    default:
        break;
    }
    
    return 2;
}

int ldc_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int index = ((code_vector[pc + 1] << 8) | code_vector[pc + 2]);

    cp_info value_from_cp = my_frame->cs_ref->get_const_pool().at(index);
    std::string str_val, class_name;

    switch (value_from_cp.tag) {
    case Float_info_value:

        float value = getFloatVal(value_from_cp);
        my_frame->push_stack(value);
        break;

    case Int_info_value:

        my_frame->push_stack((int) value_from_cp.Const.Integer_info.bytes);
        break;
    
    case String_info_value:

        str_val = constantToString(value_from_cp, my_frame->cs_ref->get_const_pool()).front();

        Object* new_str = new Object();
        new_str->set_type(FIELD_TYPES::STRING_TYPE);
        new_str->single_value = str_val;

        heap_area->pushRef(new_str);

        my_frame->push_stack(new_str);
        break;

    case Class_info_value:

        class_name = constantToString(value_from_cp, my_frame->cs_ref->get_const_pool()).front();

        m_area->load_class(class_name);

        Object* new_class_ref = new Object();

        new_class_ref->set_type(FIELD_TYPES::CLASS_REF_TYPE);
        class_space &the_class = m_area->get_class(class_name);

        new_class_ref->single_value = the_class.get_class_name();

        my_frame->push_stack(new_class_ref);
        break; 
    default:
        break;
    }
    
    return 3;
}


int ldc2_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
            
    int index = ((code_vector[pc + 1] << 8) | code_vector[pc + 2]);

    cp_info value_from_cp = my_frame->cs_ref->get_const_pool().at(index);

    switch (value_from_cp.tag) {
    case Long_info_value:

        long value = getLongVal(value_from_cp);
        
        my_frame->push_stack(value);
        break;

    case Double_info_value:

        double value = getDoubleVal(value_compare);
        my_frame->push_stack(value);
    default:
        break;
    }

    return 3;
}


// --------------------------------------------------------------------------------------------
// Constants
int aconst_null_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(nullptr);

    return 1;
}

int iconst_m1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, -1);
}

int iconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int iconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int iconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int iconst_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

int iconst_4_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 4);
}

int iconst_5_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 5);
}

int lconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int lconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int fconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0.0);
}

int fconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1.0);
}

int fconst_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2.0);
}

int dconst_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0.0);
}

int dconst_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_const_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1.0);
}


// aload -------------------------------------------------------------------------------

int aload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    my_frame->push_stack(my_frame->local_vars.at(index).as<Object*>());
    
    return advance_bytes;
}

int aload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<Object*>(0));
    
    return 1;
}


int aload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<Object*>(1));
    
    return 1;
}


int aload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<Object*>(2));
    
    return 1;
}

int aload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<Object*>(3));
    
    return 1;
}

// dload -------------------------------------------------------------------------------

int dload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    my_frame->push_stack(my_frame->get_local_var<double>(index));
    
    return advance_bytes;
}

int dload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<double>(0));

    return 1;
}

int dload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<double>(1));

    return 1;
}

int dload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<double>(2));

    return 1;
}

int dload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<double>(3));

    return 1;
}

// iload -------------------------------------------------------------------------------
int iload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    my_frame->push_stack(my_frame->get_local_var<int>(index));
    
    return advance_bytes;
}

int iload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<int>(0));

    return 1;
}

int iload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<int>(1));

    return 1;
}

int iload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<int>(2));

    return 1;
}

int iload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<int>(3));

    return 1;
}

// lload -------------------------------------------------------------------------------
int lload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    my_frame->push_stack(my_frame->get_local_var<long>(index));
    
    return advance_bytes;
}

int lload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<long>(0));

    return 1;
}

int lload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<long>(1));

    return 1;
}

int lload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<long>(2));

    return 1;
}

int lload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<long>(3));

    return 1;
}
// fload ----------------------------------------------------------------------------------
int fload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    my_frame->push_stack(my_frame->get_local_var<float>(index));
    
    return advance_bytes;
}

int fload_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<float>(0));

    return 1;
}

int fload_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<float>(1));

    return 1;
}

int fload_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<float>(2));

    return 1;
}

int fload_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    my_frame->push_stack(my_frame->get_local_var<float>(3));

    return 1;
}

// -----------------------------------------------------------------------------------------
int iaload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<int>());

            return 1;
}

int faload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            

            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

        
            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<float>());
            return 1;
}

int laload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            

            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

        
            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<long>());
            return 1;
}

int daload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

        
            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<double>());
            return 1;
}

int baload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();
    
            my_frame->push_stack((int) (char) array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<u1>());
            return 1;
}

int caload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

        
            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<char>());
            return 1;
}

int saload_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            int index_array = my_frame->get_top_and_pop_stack<int>();
            Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

        
            my_frame->push_stack(array_ref->single_value.as<Array_t*>()->my_data.at(index_array).as<short>());
            return 1;
}

int wide_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    std::vector<int> op_codes_1st_form = {
        21, 
        22, 
        23, 
        24, 
        25,
        54, 
        55, 
        56, 
        57, 
        58, 
        169
        };

    int bytes_to_incr_pc = 4; 

    u1 next_op_code = code_vector[pc + 1];

    auto it_result = find(op_codes_1st_form.begin(), op_codes_1st_form.end(), next_op_code);

    if(it_result != op_codes_1st_form.end()) { // O opcode foi encontrado no primeiro vetor
        auto instructions = get_instructions();

        instruct* next_instruct = instructions[*it_result];

        next_instruct(m_area, heap_area, java_stack, my_frame, code_vector, pc + 1, true);

        bytes_to_incr_pc = 4;
    }

    else { // O opcode encontrado esta no segundo vetor

        iinc_i(m_area, heap_area, java_stack, my_frame, code_vector, pc + 1, true);        

        bytes_to_incr_pc = 6;
    }

    return bytes_to_incr_pc;
}

int anewarray_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 3;

    int array_size = my_frame->get_top_and_pop_stack<int>();

    u2 const_pool_idx = (code_vector[pc + 1] << 8) | code_vector[pc + 2];

    std::string component_descriptor = constantToString(my_frame->cp_ref->at(const_pool_idx - 1), 
    *(my_frame->cp_ref)).front(); 

    class_space &array_component = m_area->get_class(my_frame->cs_ref, component_descriptor);

    Object* the_new_array = new Object();

    the_new_array->set_type(FIELD_TYPES::ARRAY_REF_TYPE);
    the_new_array->single_value = new Array_t(array_size);

    for(int i = 0; i < the_new_array->single_value.as<Array_t*>()->size(); i++) {
        Object* new_object = new Object(array_component.get_class_name());
        new_object->set_type(FIELD_TYPES::OBJECT_TYPE);
        // Talvez inicializar os objetos novos...

        the_new_array->single_value.as<Array_t*>()->my_data.at(i) = new_object;
    }

    heap_area->pushRef(the_new_array);

    return advance_bytes;
}


int areturn_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1;

    Object* obj_ref = my_frame->get_top_and_pop_stack<Object*>();

    java_stack->pop();

    java_stack->top().push_stack(obj_ref);

    return advance_bytes;
}

int arraylength_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
    
    int advance_bytes = 1;

    Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

    if(array_ref == nullptr) {
        stringstream buffer;

        buffer << "Erro ao executar instrucao arraylength_i\n";
        buffer << "pc: " << pc << "\n";
        buffer << "Acesso invalido a ponteiro nulo!\n";

        throw NullPointerException(buffer.str());
    }

    int array_lengh = array_ref->single_value.as<Array_t*>()->size();

    my_frame->push_stack(array_lengh);

    return advance_bytes;
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Stores


// Stores types --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int astore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int istore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int lstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int fstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int dstore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

// Stores ints --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int istore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int istore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int istore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int istore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

// Stores longs --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int lstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int lstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int lstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int lstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

// Stores floats --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int fstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int fstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int fstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int fstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

// Stores doubles --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int dstore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int dstore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int dstore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int dstore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_store_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

// Stores references --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int astore_0_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return a_store_num_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int astore_1_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return a_store_num_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int astore_2_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return a_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int astore_3_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return a_store_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 3);
}

// Stores values to arraysrefs --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int iastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int lastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int fastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int dastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int bastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<u1>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int castore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<char>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int sastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {
 
    return type_astore_i<short>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int aastore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    return type_astore_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}




// int athrow_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
//         const u1* code_vector, int pc, bool is_wide) {

    
// }



// Conversions--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int i2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<int, long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int i2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<int, float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int i2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<int, double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int i2b_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<int, char>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int i2c_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<int, char>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int i2s_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){ 

    return i2_typeU_i<short>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int l2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<long, int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int l2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<long, float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int l2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<long, double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int f2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<float, int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int f2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<float, long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int f2d_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<float, double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int d2i_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<double, int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int d2l_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<double, long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

int d2f_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    return typeT_2_typeU_i<double, float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide);
}

// ------------------------------------------------------------------------------------------------------------------------

// Comparison------------------------------------------------------------------------------------------------------------------------

int lcmp_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_comp_num_i<long>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 0);
}

int fcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_comp_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int fcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_comp_num_i<float>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int dcmpl_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_comp_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 2);
}

int dcmpg_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_comp_num_i<double>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, 1);
}

int ifeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x == 0;});
}

int ifne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x != 0;});
}

int iflt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x < 0;});
}

int ifle_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x <= 0;});
}

int ifgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x > 0;});
}

int ifge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x >= 0;});
}

int if_icmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x == y;});
}

int if_icmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x != y;});
}

int if_icmplt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x < y;});
}

int if_icmpge_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x >= y;});
}

int if_icmpgt_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x > y;});
}

int if_icmple_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<int>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](int x, int y) { return x <= y;});
}

int if_acmpeq_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](Object* x, Object* y) { return x == y;});
}

int if_acmpne_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return type_if_num_i<Object*>(m_area, heap_area, java_stack, my_frame, code_vector, pc, is_wide, [](Object* x, Object* y) { return x != y;});
}
// ------------------------------------------------------------------------------------------------------------------------
// Control------------------------------------------------------------------------------------------------------------------------
int goto_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

            int branchoffset = ((short) ((code_vector[pc + 1] << 8) | code_vector[pc + 2]));
            return branchoffset;
}

int jsr_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            
            returnAddress jump_adress = ((short) ((code_vector[pc + 1] << 8) | code_vector[pc + 2]));
            
            my_frame->push_stack(pc + 3);

            return jump_adress;
}

int jsr_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){

    returnAddress jump_adress =  (int) ((code_vector[pc + 1] << 24) | (code_vector[pc + 2] << 16) | (code_vector[pc + 3] << 8) | code_vector[pc + 4]);
    
    my_frame->push_stack(pc + 5);

    return jump_adress;
}

// ------------------------------------------------------------------------------------------------------------------------
// Extended------------------------------------------------------------------------------------------------------------------------
int goto_w_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
            return ((int) ((code_vector[pc + 1] << 24) | (code_vector[pc + 2] << 16) | (code_vector[pc + 3] << 8) 
            | (code_vector[pc + 4])));
}
// ------------------------------------------------------------------------------------------------------------------------
// Templates

template<class T>
int type_store_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    int advance_bytes = 1; 
    u2 index;

    if(is_wide) {
        index = (code_vector[pc + 1] << 8) | code_vector[pc + 2];
        advance_bytes += 2;
    }

    else {
        index = code_vector[pc + 1];
        advance_bytes += 1;
    }

    T value = my_frame->get_top_and_pop_stack<T>();

    my_frame->get_local_var<T>(index) = value;

    return advance_bytes;

}

template<class T>
int type_const_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, T VALOR_CONST) {

    my_frame->push_stack<T>(VALOR_CONST);

    return 1;
}

template<class T>
int type_store_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, T VALOR_CONST) {

    T value = my_frame->get_top_and_pop_stack<T>();

    my_frame->local_vars.at(VALOR_CONST) = value;

    return 1;
}

template<class T>
int a_store_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, int VALOR_CONST) {

    T value = my_frame->get_top_and_pop_stack<T>();

    my_frame->local_vars.at(VALOR_CONST) = value;

    return 1;
}

template<class T, typename Comp>
int type_math_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, Comp oper) {
    
    T value_1, value_2;

    value_2 = my_frame->get_top_and_pop_stack<T>();
    value_1 = my_frame->get_top_and_pop_stack<T>();

    // Any daldsl;
    // binary_search(my_frame->local_vars.begin(), my_frame->local_vars.end(), daldsl, [](Any x, Any y) { return true; });

    T result = oper(value_1, value_2);

    my_frame->push_stack(result);

    return 1;
}

template<class T, class U>
int typeT_2_typeU_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide){
    
    U value = my_frame->top_stack().as<T>();
    my_frame->pop_stack();

    // value = value.as<char>();
    
    my_frame->push_stack(<U>value);

    return 1;
}

template<class U>
int i2_typeU_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {

    U value = my_frame->top_stack().as<int>();
    my_frame->pop_stack();

    int valueConverted = value;
    
    my_frame->push_stack(valueConverted);

    return 1;
}

template<class T>
int type_comp_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, int aux){
    
    T value_1, value_2;
    
    value_2 = my_frame->get_top_and_pop_stack<T>();
    value_1 = my_frame->get_top_and_pop_stack<T>();
    
    if(value_1 > value_2){
        my_frame->push_stack<int>(1);
    }else if(value_1==value_2){
        my_frame->push_stack<int>(0);
    }else if(value_1 < value_2){
        my_frame->push_stack<int>(-1);
    }else if((value_1==INFINITY && aux==1) || (value_2==INFINITY && aux==1)){
        my_frame->push_stack<int>(1);
    }else if((value_1==INFINITY && aux==2) || (value_2==INFINITY && aux==2)){
        my_frame->push_stack<int>(-1);
    }
    return 1;
}

template<class T, typename Comp>
int type_if_num_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide, Comp oper){
            
            int advance_bytes;
            
            T value_2 = my_frame->get_top_and_pop_stack<T>();
            T value_1 = my_frame->get_top_and_pop_stack<T>();

            if(oper(value_1, value_2)){
                advance_bytes = (short) ((code_vector[pc + 1] << 8) | code_vector[pc + 2]);
            }
            else {
                advance_bytes = 3;
            }

            return advance_bytes;//nada nao  :3
            
}


template<class T>
int type_astore_i(method_area* m_area, heap* heap_area, jvm_stack* java_stack, frame* my_frame,
        const u1* code_vector, int pc, bool is_wide) {


    T value = my_frame->get_top_and_pop_stack<T>();
    int index = my_frame->get_top_and_pop_stack<int>();
    Object* array_ref = my_frame->get_top_and_pop_stack<Object*>();

    if(array_ref->single_value.is_null()) {
        stringstream buffer;
        buffer << "Erro ao executar isatore!\n A referencia ao array eh nula!";

        throw NullPointerException(buffer.str());
    }

    // if(array_ref->get_type() != FIELD_TYPES::ARRAY_BASE_TYPE) {
    //     throw Exception("Erro ao executar iastore: o array recebido nao eh de inteiros!");
    // }

    array_ref->single_value.as<Array_t*>()->at<T>(index) = value;
   
    return 1;
}


// -----------------------------------------------------------------------------------------------------------------------------
std::map<u1, instruct*> get_instructions() {

    return {
        // Constants
        {(0x00), nop_i},
        {(0x01), aconst_null_i},
        {(0x02), iconst_m1_i},
        {(0x03), iconst_0_i},
        {(0x04), iconst_1_i},
        {(0x05), iconst_2_i},
        {(0x06), iconst_3_i},
        {(0x07), iconst_4_i},
        {(0x08), iconst_5_i},
        {(0x09), lconst_0_i},
        {(0x0a), lconst_1_i},
        {(0x0b), fconst_0_i},
        {(0x0c), fconst_1_i},
        {(0x0d), fconst_2_i},
        {(0x0e), dconst_0_i},
        {(0x0f), dconst_1_i},
        {(0x10), bipush_i},
        {(0x11), sipush_i},
        {(0x12), ldc_i},
        {(0x13), ldc_w_i},
        {(0x14), ldc2_w_i},

        // Loads
        {(0x15), iload_i},
        {(0x16), lload_i},
        {(0x17), fload_i},
        {(0x18), dload_i},
        {(0x19), aload_i},
        {(0x1a), iload_0_i},
        {(0x1b), iload_1_i},
        {(0x1c), iload_2_i},
        {(0x1d), iload_3_i},
        {(0x1e), lload_0_i},
        {(0x1f), lload_1_i},
        {(0x20), lload_2_i},
        {(0x21), lload_3_i},
        {(0x22), fload_0_i},
        {(0x23), fload_1_i},
        {(0x24), fload_2_i},
        {(0x25), fload_3_i},
        {(0x26), dload_0_i},
        {(0x27), dload_1_i},
        {(0x28), dload_2_i},
        {(0x29), dload_3_i},
        {(0x2a), aload_0_i},
        {(0x2b), aload_1_i},
        {(0x2c), aload_2_i},
        {(0x2d), aload_3_i},
        {(0x2e), iaload_i},
        {(0x2f), laload_i},
        {(0x30), faload_i},
        {(0x31), daload_i},
        {(0x32), aaload_i},
        {(0x33), baload_i},
        {(0x34), caload_i},
        {(0x35), saload_i},

        // Stores
        {(0x36), istore_i},
        {(0x37), lstore_i},
        {(0x38), fstore_i},
        {(0x39), dstore_i},
        {(0x3a), astore_i},
        {(0x3b), istore_0_i},
        {(0x3c), istore_1_i},
        {(0x3d), istore_2_i},
        {(0x3e), istore_3_i},
        {(0x3f), lstore_0_i},
        {(0x40), lstore_1_i},
        {(0x41), lstore_2_i},
        {(0x42), lstore_3_i},
        {(0x43), fstore_0_i},
        {(0x44), fstore_1_i},
        {(0x45), fstore_2_i},
        {(0x46), fstore_3_i},
        {(0x47), dstore_0_i},
        {(0x48), dstore_1_i},
        {(0x49), dstore_2_i},
        {(0x4a), dstore_3_i},
        {(0x4b), astore_0_i},
        {(0x4c), astore_1_i},
        {(0x4d), astore_2_i},
        {(0x4e), astore_3_i},
        {(0x4f), iastore_i},
        {(0x50), lastore_i},
        {(0x51), fastore_i},
        {(0x52), dastore_i},
        {(0x53), aastore_i},
        {(0x54), bastore_i},
        {(0x55), castore_i},
        {(0x56), sastore_i},

        // Stack
        {(0x57), pop_i},
        {(0x58), pop2_i},
        {(0x59), dup_i},
        {(0x5a), dup_x1_i},
        {(0x5b), dup_x2_i},
        {(0x5c), dup2_i},
        {(0x5d), dup2_x1_i},
        {(0x5e), dup2_x2_i},
        {(0x5f), swap_i},

        // Math
        {(0x60), iadd_i},
        {(0x61), ladd_i},
        {(0x62), fadd_i},
        {(0x63), dadd_i},
        {(0x64), isub_i},
        {(0x65), lsub_i},
        {(0x66), fsub_i},
        {(0x67), dsub_i},
        {(0x68), imul_i},
        {(0x69), lmul_i},
        {(0x6a), fmul_i},
        {(0x6b), dmul_i},
        {(0x6c), idiv_i},
        {(0x6d), ldiv_i},
        {(0x6e), fdiv_i},
        {(0x6f), ddiv_i},
        {(0x70), irem_i},
        {(0x71), lrem_i},
        {(0x72), frem_i},
        {(0x73), drem_i},
        {(0x74), ineg_i},
        {(0x75), lneg_i},
        {(0x76), fneg_i},
        {(0x77), dneg_i},
        {(0x78), ishl_i},
        {(0x79), lshl_i},
        {(0x7a), ishr_i},
        {(0x7b), lshr_i},
        {(0x7c), iushr_i},
        {(0x7d), lushr_i},
        {(0x7e), iand_i},
        {(0x7f), land_i},
        {(0x80), ior_i},
        {(0x81), lor_i},
        {(0x82), ixor_i},
        {(0x83), lxor_i},
        {(0x84), iinc_i},

        // Conversions
        {(0x85), i2l_i},
        {(0x86), i2f_i},
        {(0x87), i2d_i},
        {(0x88), l2i_i},
        {(0x89), l2f_i},
        {(0x8a), l2d_i},
        {(0x8b), f2i_i},
        {(0x8c), f2l_i},
        {(0x8d), f2d_i},
        {(0x8e), d2i_i},
        {(0x8f), d2l_i},
        {(0x90), d2f_i},
        {(0x91), i2b_i},
        {(0x92), i2c_i},
        {(0x93), i2s_i},

        // Comparisons
        {(0x94), lcmp_i},
        {(0x95), fcmpl_i},
        {(0x96), fcmpg_i},
        {(0x97), dcmpl_i},
        {(0x98), dcmpg_i},
        {(0x99), ifeq_i},
        {(0x9a), ifne_i},
        {(0x9b), iflt_i},
        {(0x9c), ifge_i},
        {(0x9d), ifgt_i},
        {(0x9e), ifle_i},
        {(0x9f), if_icmpeq_i},
        {(0xa0), if_icmpne_i},
        {(0xa1), if_icmplt_i},
        {(0xa2), if_icmpge_i},
        {(0xa3), if_icmpgt_i},
        {(0xa4), if_icmple_i},
        {(0xa5), if_acmpeq_i},
        {(0xa6), if_acmpne_i},

        // Control
        {(0xa7), goto_i},
        {(0xa8), jsr_i},
        {(0xa9), ret_i},
        {(0xaa), tableswitch_i},
        {(0xab), lookupswitch_i},
        {(0xac), ireturn_i},
        {(0xad), lreturn_i},
        {(0xae), freturn_i},
        {(0xaf), dreturn_i},
        {(0xb0), areturn_i},
        {(0xb1), return_i},

        // References
        {(0xb2), getstatic_i},
        {(0xb3), putstatic_i},
        {(0xb4), getfield_i},
        {(0xb5), putfield_i},
        {(0xb6), invokevirtual_i},
        {(0xb7), invokespecial_i},
        {(0xb8), invokestatic_i},
        {(0xb9), invokeinterface_i},
        {(0xba), invokedynamic_i},
        {(0xbb), new_i},
        {(0xbc), newarray_i},
        {(0xbd), anewarray_i},
        {(0xbe), arraylength_i},
        {(0xbf), athrow_i},
        {(0xc0), checkcast_i},
        {(0xc1), instanceof_i},
        {(0xc2), monitorenter_i},
        {(0xc3), monitorexit_i},

        // Extended

        {(0xc4), wide_i},
        {(0xc5), multianewarray_i},
        {(0xc6), ifnull_i},
        {(0xc7), ifnonnull_i},
        {(0xc8), goto_w_i},
        {(0xc9), jsr_w_i},

        // Reserved
        {(0xca), breakpoint_i},
        {(0xfe), impdep1_i},
        {(0xff), impdep2_i}
    };
}