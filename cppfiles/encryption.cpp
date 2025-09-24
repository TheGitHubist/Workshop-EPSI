#include "encryption.h"
#include <fstream>
#include <stdexcept>
#include <cctype>

int alphaIndex(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a';
    return -1;
}

char toLowerAscii(char c) { 
    return ('A' <= c && c <= 'Z') ? char(c - 'A' + 'a') : c; 
}

bool isKeyValid(const std::string& key) {
    if (key.size() != 4) return false;
    for (char c : key) {
        if (alphaIndex(c) < 0) return false;
    }
    return true;
}

std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::vector<std::string> loadKeysFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Impossible d'ouvrir le fichier de cles: " + path);

    std::vector<std::string> keys;
    std::string line;
    while (std::getline(in, line)) {
        std::string k = trim(line);
        if (k.empty()) continue;
        if (!isKeyValid(k)) {
            throw std::runtime_error("Cle invalide dans le fichier (besoin de 4 lettres): '" + k + "'");
        }
        keys.push_back(k);
    }
    if (keys.empty()) throw std::runtime_error("Aucune cle valide trouvee dans le fichier.");
    return keys;
}
