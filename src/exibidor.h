#ifndef EXIBIDOR_H_
#define EXIBIDOR_H_

#include <ostream>
#include <string>
#include "leitor.h"
#include "classes.h"

#define endl "\n"

void showClassFile(const ClassFile &myClass, std::ostream &outstream);

#endif