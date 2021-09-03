#include "classes.h"

std::string getUtf8Const(const cp_info &const_info) {

    // char* hello = new char[(const_info.Const.Utf8.length + 1)];
    // hello = ((char*) const_info.Const.Utf8.bytes) + '\0';
    // std::string  utf8_const(hello);

    std::string utf8_const;

    for(int i = 0; i < const_info.Const.Utf8.length; i++) {
        utf8_const.push_back(const_info.Const.Utf8.bytes[i]);
    }

    utf8_const.push_back('\0');

    return utf8_const;


    // char* getString = new char[const_info.Const.Utf8.length + 1];
    // for(int i = 0; i < const_info.Const.Utf8.length; i++) {
    //     u1 b = const_info.Const.Utf8.bytes[i];

    //     if(~(b) & (1 << 7)) {

    //         cout << ((~b) & (1 << 7)) << endl;
    //         utf8_const.push_back(b);
    //     }
    //     else if(0xE0 & b) { // 3 bytes
    //         u1 b1 = const_info.Const.Utf8.bytes[i + 1];
    //         u1 b2 = const_info.Const.Utf8.bytes[i + 2];

    //         hello = ((b & 0xf) << 12) + ((b1 & 0x3f) << 6) + (b2 & 0x3f);
    //         char n_char = ((b & 0xf) << 12) + ((b1 & 0x3f) << 6) + (b2 & 0x3f);
    //         utf8_const.push_back(n_char);
    //         i += 2;

    //     }
    //     else { // 2 bytes
    //         u1 b1 = const_info.Const.Utf8.bytes[i + 1];
    //         hello = ((b & 0x1f) << 6) + (b1 & 0x3f);
    //         char n_char = ((b & 0x1f) << 6) + (b1 & 0x3f);
    //         utf8_const.push_back(n_char);
    //         i += 1;
    //     }


    // }

        // if(utf8_const.find("Sum") != utf8_const.npos) {

        //     cout << const_info.Const.Utf8.length << endl;
        //     for(int i = 0; i < const_info.Const.Utf8.length; i++) {
        //         cout << const_info.Const.Utf8.bytes[i];
        //         cout << (int) const_info.Const.Utf8.bytes[i];
        //     }
        //     cout << endl;

        //     // cout << (int) utf8_const.back() << endl;
        //     exit(EXIT_FAILURE);
        // }
    // char* utf8_const = (char *) const_info.Const.Utf8.bytes;
    // cout << "Tag = " << (u2) const_info.tag << endl;
    // for(int i = 0; i < const_info.Const.Utf8.length; i++) {
    //     cout << (int) utf8_const[i] << " ";
    // }
    // cout << endl;

}


bool validConstPoolAccess(const u2 &idx, const std::vector<cp_info> &cp) {
    return idx >= 1 and idx < cp.size() + 1;
}
