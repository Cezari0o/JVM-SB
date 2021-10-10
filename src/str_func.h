#ifndef STR_FUNC_H_
#define STR_FUNC_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include "leitor.h"
#include "classes.h"
#include "someTools.h"

#define CLASS_FILE_TYPE 0
#define FIELD_TYPE 1
#define METHOD_TYPE 2

std::vector<std::string> getAccessFlagString(u2 flags, int type);
std::string getStringOpcode(const u1 &opcode, const std::vector<cp_info> &cp);
// std::string constantToString(const cp_info &cinfo, const std::vector<cp_info> &cp, bool is_recursive);
std::vector<std::string> constantToString(const cp_info &cinfo, const vector<cp_info> &cp, bool summarize = true);
std::string getArrayType(u1 n_type);
template<typename T>
std::string getEmbracers(const T &item);
std::string getMajorVersionString(u2 major_version);
std::pair<int, std::string> getInstructToPrint(const u1 &opcode, size_t idx, u1* bytecode, const ClassFile &cf, size_t tabs_count);
std::string getTabs(int count);
std::string getClassName(const ClassFile& cf);

#endif