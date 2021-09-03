#include "someTools.h"

u1 read1Byte(std::fstream &file) {
    u1 byte;
    char my_byte[1];

    file.read(&my_byte[0], sizeof(u1));

    // Se leu fim de arquivo, ou se falhou em ler do arquivo
    if(!file)
        showExcept("Falha em ler do arquivo class");

    byte = (u1) my_byte[0];

    return byte;
}

u2 read2Byte(std::fstream &file){
    u2 byte2;
    
    byte2 = read1Byte(file);
    byte2 = (byte2 << 8) | read1Byte(file);
}

u4 read4Byte(std::fstream &file){
    u4 byte4;
    byte4 = read2Byte(file);
    byte4 = (byte4 << 16) | read2Byte(file);
    // 1111 0010 0000 0000
    return byte4;
}

// Le a quantidade de bytes presentes em total_bytes do arquivo apontado por 
// file, e armazena no array byteArray
u1* readBytes(u4 total_bytes, std::fstream &file) {
    u1 *byteArray = new u1[total_bytes];

    for(int it = 0; it < total_bytes; it++) {
        byteArray[it] = read1Byte(file);
        // cout << byteArray[it] << endl;
        // if(byteArray[it] == 0 or byteArray[it] >= ((u1)240) and byteArray[it] <= ((u1)255))
        //     showExcept("Byte lido de constante em UTF-8 invalido!");
    }

    return byteArray;
}

// Mostra o erro no terminal e encerra o programa
void showExcept(const std::string &msg) {

    std::cerr << "Erro: " << msg << "\n";
    std::cerr << "Terminando o programa\n";
    exit(EXIT_FAILURE);
}

/*
Formato big-endian
static u2 u2Read(FILE *fd) {
 u2 toReturn = getc(fd);
 toReturn = (toReturn << 8) | (getc(fd));
 return toReturn;
} 

*/