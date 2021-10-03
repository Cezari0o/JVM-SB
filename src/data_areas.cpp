#include "data_areas.h"


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


    if(DEBUG_MODE) {
        std::cout << "aqui\n\n";
    }

    if(cf_ref == nullptr)
        throw ClassNotFoundException("A classe contem um ponteiro nulo!");

    this->my_classfile = cf_ref;

    this->runtime_cp = &(cf_ref->constant_pool);

    this->methods_info = &(cf_ref->methods);
    this->fields_info = &(cf_ref->fields);
    this->class_name = getClassName(*cf_ref);
    // Inicializar os fields da classe?
}

class_space::class_space(ClassFile cf) {

    if(DEBUG_MODE) {
        std::cout << "aqui2\n\n";
    }

    this->my_classfile = new ClassFile;
    *(this->my_classfile) = cf;

    this->runtime_cp = &(this->my_classfile->constant_pool);

    this->methods_info = &(this->my_classfile->methods);
    this->fields_info = &(this->my_classfile->fields);
    this->class_name = getClassName(*(this->my_classfile));

    if(DEBUG_MODE){
        std::cout << "saindo de aqui2\n\n";
    }
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

class_space &class_space::operator=(const class_space& cp) {

    this->class_name = cp.get_class_name();

    this->my_classfile = new ClassFile;
    ClassFile toCopy = cp.get_class_file();
    *(this->my_classfile) = toCopy;

    this->runtime_cp = &(this->my_classfile->constant_pool);

    for(const auto &it : cp.fields_data) {
        this->fields_data[it.first] = new Field_t();
        *(this->fields_data[it.first]) = *(it.second);
    }

    return *this;
}


// --------------------------------------------------------------------------------------------------------------------------------

void method_area::insert_new_class(ClassFile *cf_ref) {

    if(cf_ref == nullptr)
        throw ItemNotFoundError("Area de Metodos (Insercao de nova classe):  a classe recebida nao pode ser nula!");

    class_space new_class(*cf_ref);

    if(DEBUG_MODE) {
        std::cout << "olha so o nome\n";
        std::cout << new_class.get_class_name() << "\n\n";
    }
    classes[new_class.get_class_name()] = new_class;

    if(DEBUG_MODE) {
        std::cout << "saiu?\n\n";
    }
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

void method_area::load_class(const std::string &cl_name) {
    // bool carregado = false;
    char separator = '/';

    std::string class_path;
    std::string class_name;

    size_t temp_num = cl_name.find_last_of(separator);

    temp_num = (temp_num == std::string::npos? 0 : temp_num + 1);
    class_name = cl_name.substr(temp_num);
    class_name = class_name.substr(0, class_name.find_last_of('.'));

    size_t dot_idx = cl_name.find_last_of('.');
    if(dot_idx == std::string::npos) {
        class_path = cl_name + ".class";
        // class_name = cl_name;
    } else {
        class_path = cl_name;
        // class_name = cl_name.substr(0, dot_idx);
    }

    if(DEBUG_MODE) {
        std::cout << "Class_path: " << class_path << "\n";
        std::cout << "Class name: " << class_name << "\n\n";
    }

    if(this->is_loaded(class_path))
        return;

    if(DEBUG_MODE)
        std::cout << "Passei por is_loaded\n\n" << std::endl;

    ClassFile* new_class = new ClassFile;

    try {
        *new_class = readClassFile(class_path);
    } catch (const Exception &e) {
        std::string msg = "Classe em (" + class_path + ") nao encontrada!";
        delete new_class;
        throw ClassNotFoundException(msg);
    }

    if(DEBUG_MODE)
        std::cout << "Passei pela leitura\n\n";

    if(not (new_class->minor_version >= 0 and new_class->major_version >= 44)) {
        delete new_class;
        throw UnsupportedClassVersionError("Versao do arquivo nao suportada");
    }

    std::string cf_name = 
    constantToString(new_class->constant_pool.at(new_class->this_class - 1), new_class->constant_pool).front();

    // bool eh_o_caminho_da_classe = true; // <- Flag que indica se eh pra carregar so o nome da classe ou o caminho do arquivo todo 
    // como o nome da classe 

    // std::string class_name;

    // if(eh_o_caminho_da_classe) {
    //     class_name = class_path;
    // }
    // else {
    //     // Obtendo o nome da classe recebida
    //     size_t temp_num = class_path.find_last_of(separator);

    //     temp_num = (temp_num == std::string::npos? 0 : temp_num + 1);
    //     class_name = class_path.substr(temp_num);

    // }

    // size_t dot_idx = class_name.find_last_of('.');

    // dot_idx = (dot_idx == std::string::npos? dot_idx - 1 : dot_idx + 1);

    // class_name = class_name.substr(0, dot_idx);

    if(class_name != cf_name) {
        std::string msg = "Classe requerida: " + class_name + "\n" +
        "Classe encontrada: " + cf_name;
        
        delete new_class;
        throw NoClassDefFoundError(msg);
    }

    // passo final: carregar a classe encontrada;
    // TODO: tratar o carregamento de Arrays

    if(DEBUG_MODE) 
        std::cout << "passe aqui tambem\n\n";

    if(new_class->super_class != 0) {

        std::vector<std::string> super_class_name = constantToString(new_class->constant_pool[new_class->super_class - 1], 
        new_class->constant_pool);

        if(DEBUG_MODE) {
            std::cout << "estou carregando super classes\n\n";
        }

        this->load_class(super_class_name.front());
    }

    else {
        if(DEBUG_MODE) {
            std::cout << "Comparando strings\n\n";
            std::cout << strlen(class_name.c_str()) << " " << strlen("java/lang/Object") << "\n\n";
        }
        if(class_name != "java/lang/Object")
            throw Exception("A classe carregada deveria ser Object, porem a classe eh " + class_name);
    }

    this->insert_new_class(new_class);
    this->prepare_class(class_name);

    if(DEBUG_MODE)
        std::cout << "Saiu do load_class()\n\n";
}

Array_t *get_array(std::string descriptor);

void method_area::prepare_class(std::string &class_name) {

    if(DEBUG_MODE) {
        std::cout << "Here!!\n\n";
    }
    class_space &class_to_prepare = this->get_class(class_name);    
    
    if(DEBUG_MODE)
        std::cout << "Is working?\n\n";

    for(const auto &f : class_to_prepare.get_class_file().fields) {
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
                    break;

                case 'D':
                    (*field) = 0.0;
                    break;

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

class_space &method_area::get_class(class_space *calling_class, const std::string &class_name) {

    this->load_class(class_name);

    class_space *required_class;

    try{
        required_class = &(this->classes.at(class_name));
    }
    catch(const std::exception& e) {
        stringstream buffer;
        buffer << "(Area de metodos) Erro no carregamento de classe\n";
        buffer << "Nome da classe requerida: " << class_name << "\n";
        buffer << "Erro encontrado: " << e.what() << "\n";

        throw Exception(buffer.str());
    }
    
    u2 flags_calling_class  = calling_class->get_class_file().access_flags;
    u2 flags_required_class = required_class->get_class_file().access_flags;

    if(!(flags_required_class & ACCESS_FLAGS_CLASS_FILE::ACC_PUBLIC)) {
        stringstream buffer;
        buffer << "(Area de metodos) ";
        buffer << "A classe requerida possui acesso restrito!\n";
        buffer << "Classe chamadora: " << calling_class->get_class_name() << "\n";
        buffer << "Classe requerida: " << required_class->get_class_name() << "\n";

        std::cout << buffer.str();
        // throw IllegalAccessError(buffer.str());
    }

    return *required_class;
}

bool method_area::is_sub_class(class_space &some_class, class_space &super_class) {
    const ClassFile &some_class_cf = (some_class.get_class_file());
    std::string super_from_some_class_name = constantToString(
        some_class_cf.constant_pool.at(some_class_cf.super_class - 1), 
        some_class_cf.constant_pool).front();

    if(super_from_some_class_name != super_class.get_class_name()) {

        if(super_from_some_class_name == "java/lang/Object") {
            return false;
        }

        this->load_class(super_from_some_class_name);
        class_space &super_class_from_some_class = this->get_class(super_from_some_class_name);

        return this->is_sub_class(super_class_from_some_class, super_class);
    }

    else {
        return true;
    }
}

Field_t &method_area::get_class_field(class_space *calling_class, const std::string &class_name, const std::pair<std::string, std::string>& name_and_type) {
    stringstream buffer; // Buffer para armazenar mensagem de erro, caso aconteca
    buffer << "(Area de metodos) Erro em adquirir o field da classe!\n";
    buffer << "Classe chamadora: " << calling_class->get_class_name() << "\n";
    buffer << "Classe do field: " << class_name << "\n";
    buffer << "Field name : " << name_and_type.first << "\n";
    buffer << "Field descriptor: " << name_and_type.second << "\n"; 

    class_space *required_class;

    try {
        required_class = &(this->get_class(calling_class, class_name));

    } catch(const Exception &e) {
        buffer << "Erro: " << e.get_exception_name() << "\n";
        buffer << "Erro ao carregar classe: " << e.what() << "\n";
        throw Linkage_Error_Exception(buffer.str());
    }

    auto &cf_required = required_class->get_class_file();
    bool found_field = false;
    Field_t *class_field = nullptr;

    for(auto &f : cf_required.fields) {
        std::string f_name, f_descriptor;
        f_name       = getUtf8Const(cf_required.constant_pool.at(f.name_index - 1));
        f_descriptor = getUtf8Const(cf_required.constant_pool.at(f.descriptor_index - 1));

        if(f_name == name_and_type.first and f_descriptor == name_and_type.second) {
            
            if(not (f.access_flags & ACCESS_FLAGS_FIELDS::ACC_STATIC)) { //<- Tirar caso use este metodo para carregar fields de objetos 
                buffer << "O field requerido nao e' estatico!\n";
                throw ItemNotFoundError(buffer.str());

            }

            if(f.access_flags & ACCESS_FLAGS_FIELDS::ACC_PUBLIC) {
                found_field = true;
                class_field = required_class->get_class_field(f_name);
            }

            else if(f.access_flags & ACCESS_FLAGS_FIELDS::ACC_PROTECTED) {

                if(calling_class->get_class_name() != class_name) {
                    if(not this->is_sub_class(*calling_class, *required_class)) {
                        buffer << "Field nao acessivel a class chamadora!\n";

                        throw IllegalAccessError(buffer.str());
                    }
                }
                found_field = true;
                class_field = required_class->get_class_field(f_name);
            }

            else if((not (ACCESS_FLAGS_FIELDS::ACC_PUBLIC & f.access_flags)) or (not (ACCESS_FLAGS_FIELDS::ACC_PRIVATE & f.access_flags))
            or (not (ACCESS_FLAGS_FIELDS::ACC_PROTECTED & f.access_flags))) {
                // Num sei
                found_field = true;
                class_field = required_class->get_class_field(f_name);
            }

            else if(f.access_flags & ACCESS_FLAGS_FIELDS::ACC_PRIVATE) {

                if(calling_class->get_class_name() != class_name) {
                    buffer << "Acesso ilegal a field de classe, o field e' privado!\n";

                    throw IllegalAccessError(buffer.str());
                }

                else {
                    found_field = true;
                    class_field = required_class->get_class_field(f_name);
                }
            }

            else {
                buffer << "O field encontrado nao possui flags de acesso validas!\n";

                throw Linkage_Error_Exception(buffer.str());
            }

            break;
        }
    }


    // fazer a procura do field nas superinterfaces diretas da classe
    if(!found_field) {
        if(cf_required.super_class != 0) {

            std::string super_class_name = constantToString(
                cf_required.constant_pool.at(cf_required.super_class - 1), cf_required.constant_pool).front();

            return this->get_class_field(calling_class, super_class_name, name_and_type);
        }

        else {
            buffer << "Field nao encontrado!\n";

            throw NoSuchFieldError(buffer.str()); 
        }
    }

    return *class_field;
    
}

method_info method_area::get_class_method(class_space *calling_class, const std::string &class_name, const std::pair<std::string, std::string> &name_and_type) {
    std::stringstream buffer;
    buffer << "(Area de Metodos) Erro ao carregar o metodo de classe!\n";
    buffer << "Classe chamadora: " << calling_class->get_class_name() << "\n";
    buffer << "Classe requerida: " << class_name << "\n";
    buffer << "Nome do metodo: "   << name_and_type.first << "\n";
    buffer << "Descriptor: "       << name_and_type.second << "\n";

    class_space *required_class;

    try {
        required_class = &(this->get_class(calling_class, class_name));
    } catch(const Exception &e) {
        buffer << "Erro ao carregar classe\n";
        buffer << e.what() << "\n";

        throw Linkage_Error_Exception(buffer.str());
    }

    auto &required_cf = required_class->get_class_file();
    method_info required_method;
    bool found_method = false;
    // Se temos uma classe C indicada por class_name:

    // Verificar se classe C eh uma interface
    if(required_cf.access_flags & ACCESS_FLAGS_CLASS_FILE::ACC_INTERFACE) {
        buffer << "A classe declarada e' uma interface\n";
        buffer << "Nao e' possivel carregar metodos de classe em interfaces.\n";

        throw IncompatibleClassChangeError(buffer.str());
    }

    // Se a classe C tiver o metodo com o mesmo nome e descriptor, retornar este metodo
    try {
        required_method =  required_class->get_method(name_and_type.first, name_and_type.second);
        found_method = true;
    } catch(const Exception &e) {}

    // Caso contrario, verificar nas superclasses de C se o metodo procurado existe,
    // caso a classe C tenha superclasses
    if(not found_method) {
        if(required_cf.super_class != 0) {
            std::string super_class_name = constantToString(
                required_cf.constant_pool.at(required_cf.super_class - 1), required_cf.constant_pool).front();

            try {
                required_method = this->get_class_method(calling_class, super_class_name, name_and_type);
                found_method = true;
            } catch(const Exception &e){}
        }
    }

    // Se nao der certo, procurar na superinterfaces diretas de C
    if(not found_method) {
        for(auto &interface_idx : required_cf.interfaces) {
            
            if(not found_method) {

                std::string super_interface_name = constantToString(
                    required_cf.constant_pool.at(interface_idx - 1), required_cf.constant_pool).front();

                try {
                    required_method = this->get_interface_method(calling_class, super_interface_name, name_and_type);

                    if(( not (required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PRIVATE) ) 
                            and ( not (required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_STATIC) ) ) {
                                found_method = true;
                        }
                } catch(const Exception &e) {}
            }
        }

    }

    if(not found_method) {
        buffer << "Metodo nao encontrado!\n";
        throw NoSuchMethodError(buffer.str());
    }

    else { // Verificando acessibilidade do metodo
        
        if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PUBLIC) {}

        else if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PROTECTED) {

            if(calling_class->get_class_name() != class_name) {
                if(not this->is_sub_class(*calling_class, *required_class)) {
                    buffer << "Metodo nao acessivel a classe chamadora!\n";

                    throw IllegalAccessError(buffer.str());
                }
            }
        }

        else if((not (ACCESS_FLAGS_METHODS::ACC_PUBLIC & required_method.access_flags)) or (not (ACCESS_FLAGS_METHODS::ACC_PRIVATE & required_method.access_flags))
        or (not (ACCESS_FLAGS_METHODS::ACC_PROTECTED & required_method.access_flags))) {
            // Num sei
        }

        else if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PRIVATE) {

            if(calling_class->get_class_name() != class_name) {
                buffer << "Acesso ilegal ao metodo. O metodo e' privado!\n";

                throw IllegalAccessError(buffer.str());
            }
        }

        else {
            buffer << "O metodo encontrado nao possui flags de acesso validas!\n";

            throw Linkage_Error_Exception(buffer.str());
        }
        
    }

    return required_method;
}

method_info method_area::get_interface_method(class_space *calling_class, const std::string &interface_name, const std::pair<std::string, std::string> &name_and_type) {
    std::stringstream buffer;
    buffer << "(Area de Metodos) Erro ao carregar o metodo de interface!\n";
    buffer << "Classe chamadora: " << calling_class->get_class_name() << "\n";
    buffer << "Interface requerida: " << interface_name << "\n";
    buffer << "Nome do metodo: "   << name_and_type.first << "\n";
    buffer << "Descriptor: "       << name_and_type.second << "\n";
    
    class_space *required_interface; 

    try {
        required_interface = &(this->get_class(calling_class, interface_name));
    } catch(const Exception &e) {
        buffer << "Erro ao carregar interface\n";
        buffer << e.what() << "\n";

        throw Linkage_Error_Exception(buffer.str());
    }

    bool found_method = false;
    method_info required_method;
    auto &interface_cf = required_interface->get_class_file();

    if(not (interface_cf.access_flags & ACCESS_FLAGS_CLASS_FILE::ACC_INTERFACE)) {
        buffer << "A classe requerida nao e' uma interface\n";
        buffer << "E' possivel carregar apenas metodos de interface com esta funcao!\n";

        throw IncompatibleClassChangeError(buffer.str());
    }

    try {
        required_method = required_interface->get_method(name_and_type.first, name_and_type.second);
        found_method = true;
    } catch(const Exception &e) {}


    if(not found_method) {

        class_space *Object_class = &(this->get_class("java/lang/Object"));

        for(auto &m : Object_class->get_class_file().methods) {
            std::string m_name      = getUtf8Const(Object_class->get_const_pool().at(m.name_index - 1));
            std::string m_descript  = getUtf8Const(Object_class->get_const_pool().at(m.descriptor_index - 1));


            if(m_name == name_and_type.first and m_descript == name_and_type.second and 
                ACCESS_FLAGS_METHODS::ACC_PUBLIC & m.access_flags and 
                not (ACCESS_FLAGS_METHODS::ACC_STATIC & m.access_flags)) {
                required_method = m;
                found_method = true;
                break;
            }

        }
    }

    if(not found_method) {

        for(auto &interface_idx : interface_cf.interfaces) {
            std::string super_interface_name = constantToString(
                interface_cf.constant_pool.at(interface_idx - 1), interface_cf.constant_pool).front(); 

            if (not found_method) {
                try {
                    required_method = this->get_interface_method(calling_class, super_interface_name, name_and_type);
                    
                    if((not (required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PRIVATE) ) 
                        and ( not (required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_STATIC) )) {
                            found_method = true;
                    }
                } catch(const Exception &e) {}
            }

        }
    }

    if(not found_method) {
        buffer << "Metodo de interface nao encontrado!\n";

        throw NoSuchMethodError(buffer.str());
    }

    else { // Verificando acessibilidade do metodo
        if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PUBLIC) {}

        else if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PROTECTED) {

            if(calling_class->get_class_name() != interface_name) {
                if(not this->is_sub_class(*calling_class, *required_interface)) {
                    buffer << "Metodo nao acessivel a classe chamadora!\n";

                    throw IllegalAccessError(buffer.str());
                }
            }
        }

        else if((not (ACCESS_FLAGS_METHODS::ACC_PUBLIC & required_method.access_flags)) or (not (ACCESS_FLAGS_METHODS::ACC_PRIVATE & required_method.access_flags))
        or (not (ACCESS_FLAGS_METHODS::ACC_PROTECTED & required_method.access_flags))) {
            // Num sei
        }

        else if(required_method.access_flags & ACCESS_FLAGS_METHODS::ACC_PRIVATE) {

            if(calling_class->get_class_name() != interface_name) {
                buffer << "Acesso ilegal a metodo de interface, o metodo e' privado!\n";

                throw IllegalAccessError(buffer.str());
            }
        }

        else {
            buffer << "O metodo encontrado nao possui flags de acesso validas!\n";

            throw Linkage_Error_Exception(buffer.str());
        }
    }

    return required_method;
}

Array_t *get_array(std::string descriptor) { // Num sei o q fazer ainda
    Array_t* a;

    return a;
}