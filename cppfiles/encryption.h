#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <vector>

// ---- utils clé ----
int alphaIndex(char c);
char toLowerAscii(char c);
bool isKeyValid(const std::string& key);
std::string trim(const std::string& s);
std::vector<std::string> loadKeysFile(const std::string& path);

#endif // ENCRYPTION_H
