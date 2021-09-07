/**
 * @file exibidor.h
 * 
 * @brief Contem as definicoes usadas para exibir as classes e estruturas presentes no arquivo classes.h
 * @sa classes.h
 * 
*/
#ifndef EXIBIDOR_H_
#define EXIBIDOR_H_

#include <ostream>
#include <string>
#include <map>
#include "leitor.h"
#include "classes.h"
#include "someTools.h"
#include "str_func.h"

#define endl "\n"

/**
 * @typedef printAttr
 * @global
 * 
 * @brief Definicao usada como uma "interface" para uso na funcao showClassFile
 */
typedef void printAttr(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);

/**
 * @brief Usada para exibir a estrutura de um atributo code na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printCode(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);/**
 * @brief Usada para exibir a estrutura de um atributo ConstanteValue na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printConstValue(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);/**
 * @brief Usada para exibir a estrutura de um atributo Exception na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printExceptions(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);
/**
 * @brief Usada para exibir a estrutura de um atributo SourceFile na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printSourceFile(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);/**
 * @brief Usada para exibir a estrutura de um atributo LineNumberTable na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printLineNumberTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);/**
 * @brief Usada para exibir a estrutura de um atributo LocalVariableTable na saida.
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	att         O atributo a ser exibido.      	
 * @param	cp          O pool de constantes, para buscar e exibir constantes associadas ao atributo
 * @param	outstream   O fluxo de saida utilizado para exibir o atributo 
 * @return	void
 */
void printLocalVariableTable(const attribute_info &att, const std::vector<cp_info> &cp, std::ostream &outstream);


/**
 * Exibe a classe recebida na saida
 *
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	myClass     A classe do arquivo lido, a ser exibido na saida.
 * @param	outstream  	O fluxo de saida usado para exibir o classfile.
 * @return	void
 */
void showClassFile(const ClassFile &myClass, std::ostream &outstream);

/**
 * @var func_show_map 
 * 
 * @brief Contem o mapeamento de strings para funcoes, a serem usadas para exibir atributos
 * @warning Este mapa deve ser usado apenas pelas funcoes presentes neste arquivo
 */
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