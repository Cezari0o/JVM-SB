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
    
    return byte2;

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

std::vector<std::pair<u2, std::string>> init_opcode_list() {

    return {
        // Constants
        {(0x00), "nop"},
        {(0x01), "aconst_null"},
        {(0x02), "iconst_m1"},
        {(0x03), "iconst_0"},
        {(0x04), "iconst_1"},
        {(0x05), "iconst_2"},
        {(0x06), "iconst_3"},
        {(0x07), "iconst_4"},
        {(0x08), "iconst_5"},
        {(0x09), "lconst_0"},
        {(0x0a), "lconst_1"},
        {(0x0b), "fconst_0"},
        {(0x0c), "fconst_1"},
        {(0x0d), "fconst_2"},
        {(0x0e), "dconst_0"},
        {(0x0f), "dconst_1"},
        {(0x10), "bipush"},
        {(0x11), "sipush"},
        {(0x12), "ldc"},
        {(0x13), "ldc_w"},
        {(0x14), "ldc2_w"},

        // Loads
        {(0x15), "iload"},
        {(0x16), "lload"},
        {(0x17), "fload"},
        {(0x18), "dload"},
        {(0x19), "aload"},
        {(0x1a), "iload_0"},
        {(0x1b), "iload_1"},
        {(0x1c), "iload_2"},
        {(0x1d), "iload_3"},
        {(0x1e), "lload_0"},
        {(0x1f), "lload_1"},
        {(0x20), "lload_2"},
        {(0x21), "lload_3"},
        {(0x22), "fload_0"},
        {(0x23), "fload_1"},
        {(0x24), "fload_2"},
        {(0x25), "fload_3"},
        {(0x26), "dload_0"},
        {(0x27), "dload_1"},
        {(0x28), "dload_2"},
        {(0x29), "dload_3"},
        {(0x2a), "aload_0"},
        {(0x2b), "aload_1"},
        {(0x2c), "aload_2"},
        {(0x2d), "aload_3"},
        {(0x2e), "iaload"},
        {(0x2f), "laload"},
        {(0x30), "faload"},
        {(0x31), "daload"},
        {(0x32), "aaload"},
        {(0x33), "baload"},
        {(0x34), "caload"},
        {(0x35), "saload"},

        // Stores
        {(0x36), "istore"},
        {(0x37), "lstore"},
        {(0x38), "fstore"},
        {(0x39), "dstore"},
        {(0x3a), "astore"},
        {(0x3b), "istore_0"},
        {(0x3c), "istore_1"},
        {(0x3d), "istore_2"},
        {(0x3e), "istore_3"},
        {(0x3f), "lstore_0"},
        {(0x40), "lstore_1"},
        {(0x41), "lstore_2"},
        {(0x42), "lstore_3"},
        {(0x43), "fstore_0"},
        {(0x44), "fstore_1"},
        {(0x45), "fstore_2"},
        {(0x46), "fstore_3"},
        {(0x47), "dstore_0"},
        {(0x48), "dstore_1"},
        {(0x49), "dstore_2"},
        {(0x4a), "dstore_3"},
        {(0x4b), "astore_0"},
        {(0x4c), "astore_1"},
        {(0x4d), "astore_2"},
        {(0x4e), "astore_3"},
        {(0x4f), "iastore"},
        {(0x50), "lastore"},
        {(0x51), "fastore"},
        {(0x52), "dastore"},
        {(0x53), "aastore"},
        {(0x54), "bastore"},
        {(0x55), "castore"},
        {(0x56), "sastore"},

        // Stack
        {(0x57), "pop"},
        {(0x58), "pop2"},
        {(0x59), "dup"},
        {(0x5a), "dup_x1"},
        {(0x5b), "dup_x2"},
        {(0x5c), "dup2"},
        {(0x5d), "dup2_x1"},
        {(0x5e), "dup2_x2"},
        {(0x5f), "swap"},

        // Math
        {(0x60), "iadd"},
        {(0x61), "ladd"},
        {(0x62), "fadd"},
        {(0x63), "dadd"},
        {(0x64), "isub"},
        {(0x65), "lsub"},
        {(0x66), "fsub"},
        {(0x67), "dsub"},
        {(0x68), "imul"},
        {(0x69), "lmul"},
        {(0x6a), "fmul"},
        {(0x6b), "dmul"},
        {(0x6c), "idiv"},
        {(0x6d), "ldiv"},
        {(0x6e), "fdiv"},
        {(0x6f), "ddiv"},
        {(0x70), "irem"},
        {(0x71), "lrem"},
        {(0x72), "frem"},
        {(0x73), "drem"},
        {(0x74), "ineg"},
        {(0x75), "lneg"},
        {(0x76), "fneg"},
        {(0x77), "dneg"},
        {(0x78), "ishl"},
        {(0x79), "lshl"},
        {(0x7a), "ishr"},
        {(0x7b), "lshr"},
        {(0x7c), "iushr"},
        {(0x7d), "lushr"},
        {(0x7e), "iand"},
        {(0x7f), "land"},
        {(0x80), "ior"},
        {(0x81), "lor"},
        {(0x82), "ixor"},
        {(0x83), "lxor"},
        {(0x84), "iinc"},

        // Conversions
        {(0x85), "i2l"},
        {(0x86), "i2f"},
        {(0x87), "i2d"},
        {(0x88), "l2i"},
        {(0x89), "l2f"},
        {(0x8a), "l2d"},
        {(0x8b), "f2i"},
        {(0x8c), "f2l"},
        {(0x8d), "f2d"},
        {(0x8e), "d2i"},
        {(0x8f), "d2l"},
        {(0x90), "d2f"},
        {(0x91), "i2b"},
        {(0x92), "i2c"},
        {(0x93), "i2s"},

        // Comparisons
        {(0x94), "lcmp"},
        {(0x95), "fcmpl"},
        {(0x96), "fcmpg"},
        {(0x97), "dcmpl"},
        {(0x98), "dcmpg"},
        {(0x99), "ifeq"},
        {(0x9a), "ifne"},
        {(0x9b), "iflt"},
        {(0x9c), "ifge"},
        {(0x9d), "ifgt"},
        {(0x9e), "ifle"},
        {(0x9f), "if_icmpeq"},
        {(0xa0), "if_icmpne"},
        {(0xa1), "if_icmplt"},
        {(0xa2), "if_icmpge"},
        {(0xa3), "if_icmpgt"},
        {(0xa4), "if_icmple"},
        {(0xa5), "if_acmpeq"},
        {(0xa6), "if_acmpne"},

        // Control
        {(0xa7), "goto"},
        {(0xa8), "jsr"},
        {(0xa9), "ret"},
        {(0xaa), "tableswitch"},
        {(0xab), "lookupswitch"},
        {(0xac), "ireturn"},
        {(0xad), "lreturn"},
        {(0xae), "freturn"},
        {(0xaf), "dreturn"},
        {(0xb0), "areturn"},
        {(0xb1), "return"},

        // References
        {(0xb2), "getstatic"},
        {(0xb3), "putstatic"},
        {(0xb4), "getfield"},
        {(0xb5), "putfield"},
        {(0xb6), "invokevirtual"},
        {(0xb7), "invokespecial"},
        {(0xb8), "invokestatic"},
        {(0xb9), "invokeinterface"},
        {(0xba), "invokedynamic"},
        {(0xbb), "new"},
        {(0xbc), "newarray"},
        {(0xbd), "anewarray"},
        {(0xbe), "arraylength"},
        {(0xbf), "athrow"},
        {(0xc0), "checkcast"},
        {(0xc1), "instanceof"},
        {(0xc2), "monitorenter"},
        {(0xc3), "monitorexit"},

        // Extended

        {(0xc4), "wide"},
        {(0xc5), "multianewarray"},
        {(0xc6), "ifnull"},
        {(0xc7), "ifnonnull"},
        {(0xc8), "goto_w"},
        {(0xc9), "jsr_w"},

        // Reserved
        {(0xca), "breakpoint"},
        {(0xfe), "impdep1"},
        {(0xff), "impdep2"}
    };
}

/*
Formato big-endian
static u2 u2Read(FILE *fd) {
 u2 toReturn = getc(fd);
 toReturn = (toReturn << 8) | (getc(fd));
 return toReturn;
} 

*/
