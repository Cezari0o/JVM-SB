#include "data_areas.h"

pc_register::pc_register() {
    this->pc = 0;
}

int pc_register::get_pc() const {
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

// --------------------------------------------------------------------------------------------------------------------------------


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

// --------------------------------------------------------------------------------------------------------------------------------


frame::frame(size_t max_stack_s, size_t max_locals_s, class_space* class_ref, frame* next_frame) {
    
    this->max_locals      = max_locals_s;
    this->max_stack       = max_stack_s;
    this->cs_ref          = class_ref;
    this->next_frame      = next_frame;
    this->stack_real_size = 0;

    this->local_vars.resize(max_locals_s);

    std::vector<cp_info> *runtime_cp = &(class_ref->get_const_pool());
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

// --------------------------------------------------------------------------------------------------------------------------------


class_space::class_space(ClassFile* cf_ref) {

    if(cf_ref == nullptr)
        throw ClassNotFoundException("A classe contem um ponteiro nulo!");

    this->my_classfile = cf_ref;

    this->runtime_cp = &(cf_ref->constant_pool);

    this->methods_info = &(cf_ref->methods);
    this->fields_info = &(cf_ref->fields);
    this->class_name = getClassName(*cf_ref);
    // Inicializar os fields da classe?
}

class_space::~class_space() {

    delete this->my_classfile;

    for(auto &it : this->fields_data) {
        delete it.second;
    }
}

method_info class_space::get_method(const std::string &name, const std::string &descriptor) {
    std::vector<method_info> *class_methods;

    method_info to_return_m;
    class_methods = &(this->my_classfile->methods);

    for(const method_info &m : *class_methods) {
        std::string m_name = getUtf8Const(this->runtime_cp->at(m.name_index - 1));
        std::string m_descript = getUtf8Const(this->runtime_cp->at(m.descriptor_index - 1));
        
        if((m_name == name) and (m_descript == descriptor)) {
            return to_return_m = m;
        }
    }

    throw ItemNotFoundError("Metodo nao encontrado!\nClasse: " + this->class_name +
    "Metodo: " + name + "\nDescritor: " + descriptor);

    return to_return_m;
}

method_info class_space::get_method(const u2 &name_idx, const u2 &descriptor_idx) {
    std::string method_name, method_descriptor;

    method_name = getUtf8Const(this->runtime_cp->at(name_idx - 1));
    method_descriptor = getUtf8Const(this->runtime_cp->at(descriptor_idx - 1));

    return this->get_method(method_name, method_descriptor);
}

// method_info class_space::get_method(const u2 &method_idx) {
//     std::string method_name, method_descript;

//     cp_info method_ref = this->runtime_cp->at(method_idx - 1);
//     std::vector<string> method_infos = constantToString(
//         this->runtime_cp->at(method_ref.Const.Methodref_info.name_and_type_index - 1), *(this->runtime_cp));


//     method_name     = method_infos.at(0);
//     method_descript = method_infos.at(1);

//     return this->get_method(method_name, method_descript);
// }

method_info class_space::get_method(const cp_info &method_ref) {
    cp_info name_and_type = this->runtime_cp->at(method_ref.Const.Methodref_info.name_and_type_index - 1);
    u2 name_idx, descript_idx;

    name_idx = name_and_type.Const.NameAndType_info.name_index;
    descript_idx = name_and_type.Const.NameAndType_info.descriptor_index;

    return this->get_method(name_idx, descript_idx);
}

Field_t *class_space::get_class_field(const std::string &field_name) {

    if(this->fields_data.count(field_name) > 0) {
        return (this->fields_data[field_name]);
    }

    this->fields_data[field_name] = new Field_t();

    return this->fields_data[field_name];
}


Field_t *class_space::get_class_field(const cp_info &field_ref) {
    cp_info name_and_type = this->runtime_cp->at(field_ref.Const.Fieldref_info.name_and_type_index);
    u2 name_idx, descript_idx;

    name_idx = name_and_type.Const.NameAndType_info.name_index;
    
    std::string field_name = getUtf8Const(this->runtime_cp->at(name_idx - 1));

    return this->get_class_field(field_name);
}

Field_t *class_space::get_class_field(const u2 &name_idx) {
    std::string field_name = getUtf8Const(this->runtime_cp->at(name_idx - 1));

    return this->get_class_field(field_name);
}

// --------------------------------------------------------------------------------------------------------------------------------

void method_area::insert_new_class(ClassFile *cf_ref) {

    if(cf_ref == nullptr)
        throw ItemNotFoundError("Area de Metodos (Insercao de nova classe):  a classe recebida nao pode ser nula!");

    class_space new_class(cf_ref);

    classes[new_class.get_class_name()] = new_class;
}

void method_area::remove_class(const std::string &class_name) {

    if(this->classes.count(class_name) == 0) {
        throw ClassNotFoundException(
            "Area de Metodos (Remocao de classe): a classe nao existe na area de metodos!\nClasse: "
            + class_name);
    }

    classes.erase(class_name);
}

class_space &method_area::get_class(const std::string &class_name) {

    if(this->classes.count(class_name) == 0) {
        throw ClassNotFoundException(
            "Area de Metodos (Acesso a classe): a classe nao existe na area de metodos!\nClasse: "
            + class_name);
    }

    return classes[class_name];
}

void method_area::load_class(const std::string &class_path) {
    bool carregado = false;
    char separator = '/';

    if(this->is_loaded(class_path))
        return;

    ClassFile* new_class = new ClassFile;

    try {
        *new_class = readClassFile(class_path);
    } catch (const Exception &e) {
        std::string msg = "Classe em (" + class_path + ") nao encontrada!";
        delete new_class;
        throw ClassNotFoundException(msg);
    }

    if(not (new_class->minor_version >= 0 and new_class->major_version >= 44)) {
        delete new_class;
        throw UnsupportedClassVersionError("Versao do arquivo nao suportada");
    }

    std::string cf_name = 
    constantToString(new_class->constant_pool.at(new_class->this_class - 1), new_class->constant_pool).front();

    bool eh_o_caminho_da_classe = true; // <- Flag que indica se eh pra carregar so o nome da classe ou o caminho do arquivo todo 
    // como o nome da classe 

    std::string class_name;

    if(eh_o_caminho_da_classe) {
        class_name = class_path;
    }
    else {
        // Obtendo o nome da classe recebida
        size_t temp_num = class_path.find_last_of(separator);

        temp_num = (temp_num == std::string::npos? 0 : temp_num + 1);
        class_name = class_path.substr(temp_num);

    }

    size_t dot_idx = class_name.find_last_of('.');

    dot_idx = (dot_idx == std::string::npos? dot_idx - 1 : dot_idx + 1);

    class_name = class_name.substr(0, dot_idx);

    if(class_name != cf_name) {
        std::string msg = "Classe requerida: " + class_name + "\n" +
        "Classe encontrada: " + cf_name;
        
        delete new_class;
        throw NoClassDefFoundError(msg);
    }

    // passo final: carregar a classe encontrada;
    // TODO: tratar o carregamento de Arrays

    if(new_class->super_class != 0) {

        std::vector<std::string> super_class_name = constantToString(new_class->constant_pool[new_class->super_class - 1], 
        new_class->constant_pool);

        this->load_class(super_class_name.front());
    }

    else {
        if(class_name != "java/lang/Object")
            throw Exception("A classe carregada deveria ser Object, porem a classe eh " + class_name);
    }

    this->insert_new_class(new_class);
    this->prepare_class(class_name);
}

Array_t *get_array(std::string descriptor);

void method_area::prepare_class(std::string &class_name) {
    class_space &class_to_prepare = this->get_class(class_name);    

    for(const auto &f : *(class_to_prepare.fields_info)) {
        if(f.access_flags & ACCESS_FLAGS_FIELDS::ACC_STATIC) {
            
            std::string field_name = getUtf8Const(class_to_prepare.get_const_pool().at(f.name_index - 1));
            std::string descriptor = getUtf8Const(class_to_prepare.get_const_pool().at(f.descriptor_index - 1));

            Field_t* field = class_to_prepare.get_class_field(field_name);

            switch(descriptor.front()) {
                case 'B':
                case 'C':
                case 'I':
                case 'S':
                case 'Z':
                    (*field) = 0;
                    break;

                case 'F':
                    (*field) = 0.0F;

                case 'D':
                    (*field) = 0.0;

                case 'J':
                    (*field) = 0L;
                    break;

                case 'L':
                    descriptor = descriptor.substr(1);
                    descriptor.pop_back();

                    (*field) = Object(descriptor);
                    break;

                case '[':
                    (*field) = get_array(descriptor);
                    break;
            }

        }
    }

}

Array_t *get_array(std::string descriptor) { // Num sei o q fazer ainda
    Array_t* a;

}