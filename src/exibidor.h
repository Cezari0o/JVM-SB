#ifndef EXIBIDOR_H_
#define EXIBIDOR_H_

#include <ostream>
#include <string>
#include "leitor.h"

#define endl "\n"

void showClassFile(const ClassFile &myClass, std::ostream &outstream);
void showExcept(const std::string &msg);
std::string getUtf8Const(const cp_info &const_info);

#endif