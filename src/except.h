/*!
* \file \src\except.h
* \version 0.1
* \date 12/10/2021
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef EXCEPT_H_
#define EXCEPT_H_

/*! Importation of librairies*/
#include <exception>
#include <string>
#include <typeinfo>

enum errors_type {LINK_ERROR = 1,
                  CLASS_EXCEPT,
                 };

class Exception: public std::exception {

    protected:
        std::string error_msg;
        int my_error_type;

        void set_error_type(int error_num) {
            this->my_error_type = error_num;
        }

    public:

        virtual ~Exception() = default;

        virtual std::string get_exception_name() const { return "Exception"; };

        int get_error_type() const { return this->my_error_type; }
        Exception(const std::string& msg, const int num_error = 0): error_msg(msg), my_error_type(num_error) {}

        const char* what() const noexcept override {
            return this->error_msg.c_str();
        }

};

class Linkage_Error_Exception : public Exception {
    public:
        std::string get_exception_name() const override { return "Linkage_Error_Exception"; }

        Linkage_Error_Exception(const std::string &msg): Exception(msg, LINK_ERROR) {}
};

class ClassNotFoundException : public Exception {

    public:
        std::string get_exception_name() const override { return "ClassNotFoundException"; }
        ClassNotFoundException(const std::string &msg): Exception(msg, CLASS_EXCEPT) {}
};

class UnsupportedClassVersionError: public Exception {

    public:

        std::string get_exception_name() const override { return "UnsupportedClassVersionError"; }
        UnsupportedClassVersionError(const std::string &msg) : Exception(msg) {}
};

class NoClassDefFoundError: public Exception {

    public:
        std::string get_exception_name() const override { return "NoClassDefFoundError"; }
        NoClassDefFoundError(const std::string &msg) : Exception(msg) {}
};

class OutOfMemoryError: public Exception {

    public:
        std::string get_exception_name() const override { return "OutOfMemoryError"; }
        OutOfMemoryError(const std::string &msg) : Exception(msg) {}
};

class ItemNotFoundError: public Exception {

    public:
        std::string get_exception_name() const override { return "ItemNotFoundError"; }
        ItemNotFoundError(const std::string &msg) : Exception(msg) {}
};

class IllegalAccessError: public Exception {
    public:
        std::string get_exception_name() const override { return "IllegalAccessError"; }
        IllegalAccessError(const std::string &msg) : Exception(msg) {}
};

class NoSuchFieldError: public Exception {
    public:
        std::string get_exception_name() const override { return "NoSuchFieldError"; }
        NoSuchFieldError(const std::string &msg) : Exception(msg) {}
};

class NoSuchMethodError: public Exception {
    public:
        std::string get_exception_name() const override { return "NoSuchMethodError"; }
        NoSuchMethodError(const std::string &msg) : Exception(msg) {}
};

class IncompatibleClassChangeError: public Exception {
    public:
        std::string get_exception_name() const override { return "IncompatibleClassChangeError"; }
        IncompatibleClassChangeError(const std::string &msg) : Exception(msg) {}
};

class NullPointerException: public Exception {
    public:
        std::string get_exception_name() const override { return "NullPointerException"; }
        NullPointerException(const std::string &msg) : Exception(msg) {} 
};

class ArrayIndexOutOfBoundsException: public Exception {
    public:
        std::string get_exception_name() const override { return "ArrayIndexOutOfBoundsException"; }
        ArrayIndexOutOfBoundsException(const std::string &msg) : Exception(msg) {} 
};

class NegativeArraySizeException: public Exception {
    public:
        std::string get_exception_name() const override { return "NegativeArraySizeException"; }
        NegativeArraySizeException(const std::string &msg) : Exception(msg) {}
};

#endif