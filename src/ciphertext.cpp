#include <string>
#include <iostream>
#include "keygenerator.h"

std::string kxortext(const std::string &plaintext, const std::string &key) {
    std::string ciphertext = plaintext;
    size_t key_len = key.length();

    if (key_len == 0) {
        throw std::invalid_argument("Key cannot be empty");
    }

    // KXOR (regular XOR) encryption working with bytes to support UTF-8
    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
    return ciphertext;
}

std::string knxortext(const std::string &plaintext, const std::string &key) {
    std::string ciphertext = plaintext;
    size_t key_len = key.length();

    if (key_len == 0) {
        throw std::invalid_argument("Key cannot be empty");
    }

    // KNXOR (regular NXOR) encryption working with bytes to support UTF-8
    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext[i] = ~(plaintext[i] ^ key[i]);
    }
    return ciphertext;
}

std::string nkxortext(const std::string &plaintext, const std::string &key) {
    std::string ciphertext = plaintext;
    size_t key_len = key.length();

    if (key_len == 0) {
        throw std::invalid_argument("Key cannot be empty");
    }

    // NKXOR (XOR but with NOT key) encryption working with bytes to support UTF-8
    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext[i] = plaintext[i] ^ (~key[i]);
    }
    return ciphertext;
}

std::string nknxortext(const std::string &plaintext, const std::string &key) {
    std::string ciphertext = plaintext;
    size_t key_len = key.length();

    if (key_len == 0) {
        throw std::invalid_argument("Key cannot be empty");
    }

    // NKNXOR (NXOR but with NOT key) encryption working with bytes to support UTF-8
    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext[i] = ~(plaintext[i] ^ (~key[i]));
    }
    return ciphertext;
}

LogicDoor getLogicDoor(const std::string &id) {
    if (id == "00") return KXOR;
    if (id == "01") return KNXOR;
    if (id == "10") return NKXOR;
    if (id == "11") return NKNXOR;
    throw std::invalid_argument("Invalid ID");
}

std::string encryptMessage(const std::string &message, const std::string &key) {
    std::string keyCopy = key; // Work with a copy to avoid modifying original

    LogicDoor doorOne = getLogicDoor(keyCopy.substr(0, 2));
    keyCopy = keyCopy.substr(2); // Remove ID
    LogicDoor doorTwo = getLogicDoor(keyCopy.substr(0, 2));
    keyCopy = keyCopy.substr(2); // Remove ID
    std::string blur = keyCopy.substr(0, 8);
    keyCopy = keyCopy.substr(8); // Remove Blur
    std::string ciphertext;
    switch (doorOne) {
        case KXOR:
            ciphertext = kxortext(message, keyCopy);
            break;
        case KNXOR:
            ciphertext = knxortext(message, keyCopy);
            break;
        case NKXOR:
            ciphertext = nkxortext(message, keyCopy);
            break;
        case NKNXOR:
            ciphertext = nknxortext(message, keyCopy);
            break;
        default:
            throw std::invalid_argument("Invalid Logic Door");
    }
    switch (doorTwo) {
        case KXOR:
            ciphertext = kxortext(ciphertext, keyCopy);
            break;
        case KNXOR:
            ciphertext = knxortext(ciphertext, keyCopy);
            break;
        case NKXOR:
            ciphertext = nkxortext(ciphertext, keyCopy);
            break;
        case NKNXOR:
            ciphertext = nknxortext(ciphertext, keyCopy);
            break;
        default:
            throw std::invalid_argument("Invalid Logic Door");
    }

    return ciphertext;
}

std::string decryptMessage(const std::string &ciphertext, const std::string &key) {
    std::string keyCopy = key; // Work with a copy to avoid modifying original

    LogicDoor doorOne = getLogicDoor(keyCopy.substr(0, 2));
    keyCopy = keyCopy.substr(2); // Remove ID
    LogicDoor doorTwo = getLogicDoor(keyCopy.substr(0, 2));
    keyCopy = keyCopy.substr(2); // Remove ID
    std::string blur = keyCopy.substr(0, 8);
    keyCopy = keyCopy.substr(8); // Remove Blur

    std::string plaintext;
    switch (doorTwo) {
        case KXOR:
            plaintext = kxortext(ciphertext, keyCopy);
            break;
        case KNXOR:
            plaintext = knxortext(ciphertext, keyCopy);
            break;
        case NKXOR:
            plaintext = nkxortext(ciphertext, keyCopy);
            break;
        case NKNXOR:
            plaintext = nknxortext(ciphertext, keyCopy);
            break;
        default:
            throw std::invalid_argument("Invalid Logic Door");
    }
    switch (doorOne) {
        case KXOR:
            plaintext = kxortext(plaintext, keyCopy);
            break;
        case KNXOR:
            plaintext = knxortext(plaintext, keyCopy);
            break;
        case NKXOR:
            plaintext = nkxortext(plaintext, keyCopy);
            break;
        case NKNXOR:
            plaintext = nknxortext(plaintext, keyCopy);
            break;
        default:
            throw std::invalid_argument("Invalid Logic Door");
    }
    return plaintext;
}
