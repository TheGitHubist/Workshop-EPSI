#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <string>
#include "keygenerator.h"

std::string kxortext(const std::string &plaintext, const std::string &key);      // regular XOR
std::string knxortext(const std::string &plaintext, const std::string &key);     // regular NXOR
std::string nkxortext(const std::string &plaintext, const std::string &key);     // XOR but with NOT key
std::string nknxortext(const std::string &plaintext, const std::string &key);    // NXOR but with NOT key
std::string encryptMessage(const std::string &message, const std::string &key);
std::string decryptMessage(const std::string &ciphertext, const std::string &key);

#endif // CIPHERTEXT_H
