#ifndef ATTR_FUNCTIONS_H_
#define ATTR_FUNCTIONS_H_

#include <map>
#include <fstream>
#include <string>
#include "classes.h"
#include "someTools.h"
// #include <ostream>

// "interface" padrao para as funcoes que trabalham em atributos
typedef int attr_func(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);

int readConstant(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp);
int readCode(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp);
int readExceptions(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
// int readStackMapTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readLineNumberTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readLocalVariableTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
int readSourceFile(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);

// Mapa com a definicao das funcoes para tratar atributos.
// Adicione novos atributos aqui
static std::map<std::string, attr_func*> func_map = {
                                                // {},
                                                {"ConstantValue", readConstant},
                                                {"Code", readCode},                                                
                                                {"Exceptions", readExceptions},
                                                {"SourceFile", readSourceFile},
                                                {"LineNumberTable", readLineNumberTable},
                                                {"LocalVariableTable", readLocalVariableTable}
                                            };

/**
 * readAttr. 
 *
 * Essa funcao le o proximo atributo presente no arquivo apontado por file.
 * Retorna uma attribute_info. Pode parar o programa. 
 * @author	@Cezari0o
 * @since	v0.0.1
 * @version	v1.0.0	Thursday, September 2nd, 2021.
 * @global
 * @param	fstream	&file	
 * @param	mixed  	&cp  	
 * @return	attribute_info
 */
attribute_info* readAttr(std::fstream &file, const std::vector<cp_info> &cp);

#endif
