#include "rsa.h"

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int &e, int &n) {
    e = e % n;
    for (int d = n; d >= 1; d--) {
        if ((d * e) % n == 1) {
            return d;
        }
    }
    return -1; // Inverse doesn't exist
}

int EulerTotient(int &p, int &q) {
    return (p - 1) * (q - 1);
}

std::vector<std::vector<int>> generateKeys(int &p, int &q) {
    int n = p * q;
    int phi = EulerTotient(p, q);

    int e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            break;
        }
    }

    int d = modInverse(e, phi);
    return {{e, n}, {d, n}}; // Public key {e, n}, Private key {d, n}
}