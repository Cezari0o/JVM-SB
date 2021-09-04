#ifndef SOMETOOLS_H_
#define SOMETOOLS_H_

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

typedef unsigned char  u1;
typedef unsigned short u2;
typedef unsigned int   u4;
typedef unsigned long  u8;

// Lembrar de tirar caso nao use em outros arquivos
u1 read1Byte(std::fstream &fp);
u2 read2Byte(std::fstream &fp);
u4 read4Byte(std::fstream &fp);
u1* readBytes(u4 total_bytes, std::fstream &file);
std::vector<std::pair<u2, std::string>> init_opcode_list();

void showExcept(const std::string &msg);


#endif