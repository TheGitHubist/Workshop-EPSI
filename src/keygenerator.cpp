#include <Arduino.h>
#include <string>

enum LogicDoor {
  XOR,
  NOR,
  NAND,
  AND
};

std::string generateID() {
  std::string id = "";
  srand((unsigned)time(NULL));
  for (int i = 0; i < 2; i++) {
    LogicDoor door = LogicDoor(rand()%4);
    switch (door) {
      case XOR : id += "00"; break;
      case NOR : id += "01"; break;
      case NAND : id += "10"; break;
      case AND : id += "11"; break;
      default : id += "00"; break;
    }
  }
  return id;
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