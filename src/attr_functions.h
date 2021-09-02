#ifndef ATTR_FUNCTIONS_H_
#define ATTR_FUNCTIONS_H_

#include "leitor.h"
#include "exibidor.h"
#include <map>
#include <fstream>
#include <string>
// #include <ostream>

// "interface" padrao para as funcoes que trabalham em atributos
typedef int attr_func(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);

int readConstant(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp);
int readCode(attribute_info &att, const vector<cp_info> &cp);
int readExceptions(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
// int readStackMapTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readLineNumberTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readLocalVariableTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readSourceFile(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);

// Mapa com a definicao das funcoes para tratar atributos.
// Adicione novos atributos aqui
std::map<std::string, attr_func*> func_map = {
                                                // {},
                                                {"ConstantValue", readConstant},
                                                {"Code", readCode},                                                
                                                {"Exceptions", readExceptions},
                                                {"SourceFile", readSourceFile},
                                                {"LineNumberTable", readLineNumberTable},
                                                {"LocalVariableTable", readLocalVariableTable}
                                            };

attribute_info* readAttr(std::fstream &file, const std::vector<cp_info> &cp);

#endif
