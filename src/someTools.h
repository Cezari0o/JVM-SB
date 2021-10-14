/**
 * @file someTools.h
 * 
 * @brief Contem as definicoes sobre de funcoes uteis que podem ser importadas e usadas.
 */
#ifndef SOMETOOLS_H_
#define SOMETOOLS_H_

#define DEBUG_MODE 0

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <stdint.h>

// Definicoes para uso nos demais arquivos
typedef uint8_t     u1; // <- 1 Byte
typedef uint16_t    u2; // <- 2 Bytes
typedef uint32_t    u4; // <- 4 Bytes
typedef uint64_t    u8; // <- 8 Bytes

/**
 * @brief Le byte(s) do arquivo lido, e retorna esse(s) byte(s).
 *
 * @warning Eh assumido que o ponteiro para o arquivo esta aberto corretamente.
 * @warning Caso nao seja possivel ler do arquivo, a execucao de todo o programa eh parada!
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	fp      o ponteiro para o arquivo lido.
 * @return	O byte lido do arquivo
 */
u1 read1Byte(std::fstream &fp);
/**
 * @brief Le byte(s) do arquivo lido, e retorna esse(s) byte(s).
 *
 * @warning Eh assumido que o ponteiro para o arquivo esta aberto corretamente.
 * @warning Caso nao seja possivel ler do arquivo, a execucao de todo o programa eh parada!
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	fp      o ponteiro para o arquivo lido.
 * @return	O byte lido do arquivo
 */
u2 read2Byte(std::fstream &fp);
/**
 * @brief Le byte(s) do arquivo lido, e retorna esse(s) byte(s).
 *
 * @warning Eh assumido que o ponteiro para o arquivo esta aberto corretamente.
 * @warning Caso nao seja possivel ler do arquivo, a execucao de todo o programa eh parada!
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	fp      o ponteiro para o arquivo lido.
 * @return	O byte lido do arquivo
 */
u4 read4Byte(std::fstream &fp);
/**
 * @brief Le uma quantidade de bytes especificada
 *
 * @warning Eh assumido que o ponteiro para o arquivo esta aberto corretamente.
 * @warning Caso nao seja possivel ler do arquivo, a execucao de todo o programa eh parada!
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	file        O ponteiro para o arquivo lido.
 * @param   total_bytes A quantidade de bytes a serem lidos do arquivo
 * @return	Os bytes lidos do arquivo.
 */
u1* readBytes(u4 total_bytes, std::fstream &file);
/**
 * @brief Retorna um vetor, com a lista de opcodes em strings.
 * @global
 * 
 * @return Um vetor de pares. O primeiro item indica o numero do opcode, ja o segundo indica a string correspondente do par.
 */
std::vector<std::pair<u2, std::string>> init_opcode_list();

/**
 * @brief   Exibe uma mensagem no terminal, e encerra a execucao do programa.
 * @since	v0.0.1
 * @version	v1.0.0	Sunday, September 5th, 2021.
 * @global
 * @param	msg     a mensagem a ser exibida no terminal.	
 * @return	void
 */
void showExcept(const std::string &msg);

void showHelp(std::ostream &output);


#endif