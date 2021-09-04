#ifndef EXIBIDOR_H_
#define EXIBIDOR_H_

#include <ostream>
#include <string>
#include <map>
#include "leitor.h"
#include "classes.h"

#define endl "\n"

typedef void printAttr(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);

void printCode(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
void printConstValue(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
void printExceptions(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
void printSourceFile(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
void printLineNumberTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
void printLocalVariableTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);


void showClassFile(const ClassFile &myClass, std::ostream &outstream);

static std::map<std::string, printAttr*> func_show_map = {
                                                // {},
                                                {"Code", printCode},
                                                {"ConstValue", printConstValue},                                                
                                                {"Exceptions", printExceptions},
                                                {"SourceFile", printSourceFile},
                                                {"LineNumberTable", printLineNumberTable},
                                                {"LocalVariableTable", printLocalVariableTable}
                                            };
                


#endif