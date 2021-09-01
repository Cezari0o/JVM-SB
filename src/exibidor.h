#ifndef EXIBIDOR_H_
#define EXIBIDOR_H_

#include <ostream>
#include <string>
#include "leitor.h"

#define endl "\n"

void showClassFile(const ClassFile &myClass, std::ostream &outstream);
void showExcept(const string &msg);

#endif