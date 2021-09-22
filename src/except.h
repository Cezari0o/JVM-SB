#ifndef EXCEPT_H_
#define EXCEPT_H_

#include <exception>
#include <string>

class Exception: public std::exception {

    private:
        std::string error_msg;

    public:

        Exception(const std::string& msg): error_msg(msg) {}

        const char* what() const noexcept override {
            return this->error_msg.c_str();
        }

};

#endif