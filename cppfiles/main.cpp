#include "rsa.h"
#include "encryption.h"

bool isPrime(int number) {
    if (number <= 1) return false;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return false;
    }
    return true;
}

int generateRandomPrime(int lower, int upper) {
    int num;
    do {
        num = rand() % (upper - lower + 1) + lower;
    } while (!isPrime(num));
    return num;
}

int main() {
    return 0;
}