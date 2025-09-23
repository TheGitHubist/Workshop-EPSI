#include <string>
#include <cstdlib>
#include <ctime>
#include "keygenerator.h"

std::string generateID() {
  std::string id = "";
  srand((unsigned)time(NULL));
  for (int i = 0; i < 2; i++) {
    LogicDoor door = LogicDoor(rand()%4);
    switch (door) {
      case KXOR : id += "00"; break;
      case KNXOR : id += "01"; break;
      case NKXOR : id += "10"; break;
      case NKNXOR : id += "11"; break;
      default : id += "00"; break;
    }
  }
  return id.substr(0, 2) != id.substr(2, 4) ? id : generateID();
}

std::string generateBlur() {
  srand((unsigned)time(NULL));
  int random;
  std::string key = "";
  for (int i = 0; i < 8; i++) {
    random = rand() % 2;
    key += std::to_string(random);
  }
  return key;
}

std::string generateKey() {
  srand((unsigned)time(NULL));
  int random;
  std::string key = "";
  for (int i = 0; i < 25; i++) {
    random = rand() % 2;
    key += std::to_string(random);
  }
  return key;
}

std::string generateKeyWithIDAndBlur() {
    std::string key = generateKey();
    std::string blur = generateBlur();
    std::string id = generateID();
    return id + blur + key;
}