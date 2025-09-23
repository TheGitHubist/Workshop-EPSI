#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <string>

enum LogicDoor {
    KXOR,    // regular XOR
    KNXOR,   // regular NXOR
    NKXOR,   // XOR but with NOT key
    NKNXOR   // NXOR but with NOT key
};

std::string generateID();
std::string generateBlur();
std::string generateKey();
std::string generateKeyWithIDAndBlur();

#endif // KEYGENERATOR_H
