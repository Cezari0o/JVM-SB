/**
 * @file attr_functions.h
 * 
 * @brief Contem as funcoes para a leitura de atributos da JVM de um arquivo .class
 */
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

/**
 * Le um atributo do tipo constante do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readConstant(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp);
/**
 * Le um atributo do tipo Code do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readCode(std::fstream &file, attribute_info &att, const std::vector<cp_info> &cp);
/**
 * Le um atributo do tipo Exception do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readExceptions(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
// int readStackMapTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
/**
 * Le um atributo do tipo LineNumberTable do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readLineNumberTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
/**
 * Le um atributo do tipo LocalVariableTable do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readLocalVariableTable(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);
/**
 * Le um atributo do tipo SourceFile do  arquivo recebido, e armazena na variavel att .
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido.
 * @param	att     Referencia para o atributo, onde serao armazenados os dados lidos.
 * @param	cp      vetor representando o pool de constantes
 * @return	True se completou a operacao com sucesso, false caso contrario
 */
int readSourceFile(std::fstream &file, attribute_info &att,const std::vector<cp_info> &cp);

/**
 * @var		func_map
 * 
 * @brief Mapa com a definicao das funcoes para tratar atributos.
 * Adicione novas funcoes de atributo aqui
 *
 * @warning O uso desta estrutura eh intencionada apenas para as funcoes deste arquivo.
 */
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
 *  @brief Le o proximo atributo presente no arquivo apontado por file.
 * Retorna uma attribute_info. Pode parar o programa.
 * @warning o ponteiro para o arquivo lido deve estar aberto, caso contrario o comportamento desta funcao
 * eh indefinido.
 * @since	v0.0.1
 * @version	v1.0.0	Thursday, September 2nd, 2021.
 * @global
 * @param	file    O ponteiro para o arquivo lido
 * @param	cp      O vetor do pool de constantes
 * @return	Uma struct attribute_info, com os dados lidos de um atributo.
 * @sa      attribute_info
 */
attribute_info* readAttr(std::fstream &file, const std::vector<cp_info> &cp);

#endif
