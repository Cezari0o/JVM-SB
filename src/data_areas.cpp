#include "data_areas.h"

pc_register::pc_register() {
    this->pc = 0;
}

int pc_register::get_pc() {
    return this->pc;
}

void pc_register::increment_pc(const int &value) {

    if(not (value + this->pc > 0)) {
        throw Exception("Valor de incremento de pc invalido!\nValor encontrado: " + std::to_string(value));
    }

    this->pc += value;
}

void pc_register::increment_pc() {
    this->increment_pc(1);
}

int pc_register::get_next_pc(const int &value) {

    this->increment_pc(value);
    int next_pc = this->get_pc();

    return next_pc;
}

void jvm_stack::push(frame *new_frame) {


    if(this->stack_size + 1 == max_stack_size)
        throw Exception("Max jvm stack size reached!");
    
    new_frame->set_next_frame(this->top_frame);
    this->top_frame = new_frame;
    this->stack_size++;

}

void jvm_stack::pop() {

    if(this->top_frame == nullptr)
        throw Exception("Trying to pop from empty jvm stack!");

    frame* frame_to_del = this->top_frame;

    this->top_frame = frame_to_del->get_next_frame_ref();
    this->stack_size--;

    delete frame_to_del;
}

jvm_stack::~jvm_stack() {

    while(this->size() > 0)
        this->pop();
}

frame::frame(size_t max_stack_s, size_t max_locals_s, class_space* class_ref, frame* next_frame) {
    
    this->max_locals      = max_locals_s;
    this->max_stack       = max_stack_s;
    this->cs_ref          = class_ref;
    this->next_frame      = next_frame;
    this->stack_real_size = 0;

    this->local_vars.resize(max_locals_s);

    std::vector<cp_info> *runtime_cp = class_ref->get_const_pool();
    this->cp_ref = runtime_cp;
}

frame::frame(const attribute_info& code, class_space* class_ref, frame* next_frame)
: frame(code.attr.Code.max_stack, code.attr.Code.max_locals, class_ref, next_frame) {}


template<class T>
void frame::push_stack(const T &v) {

    Any value(v);

    if(this->stack_real_size + 1 == this->max_stack)
        throw Exception("Max operand stack size reached!");


    if(value.is<long long>() or value.is<double>()) {
        this->stack_real_size += 2;
    }

    else {
        this->stack_real_size++;
    }

    this->operand_stack.push(value);
}

void frame::pop_stack() {
    int temp;

    if(operand_stack.top().is<double>() or operand_stack.top().is<long long>()) {
        temp = 2;
    }

    else {
        temp = 1;
    }

    if(this->stack_real_size - temp < 0)
        throw Exception("Bad pop in operand stack frame!");

    this->stack_real_size -= temp;
    this->operand_stack.pop();
}

template<class T>
T frame::get_top_and_pop_stack() {
    T toReturn = this->top_stack<T>();

    this->pop_stack();

    return toReturn;
}