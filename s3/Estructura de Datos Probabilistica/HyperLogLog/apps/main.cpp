#include "hyperloglog.h"
#include <iostream>
#include <string>

int main() {
    HyperLogLog hll(10);
    std::string values[] = {
        "alpha", "beta", "gamma", "delta", "epsilon",
        "zeta", "eta", "theta", "iota", "kappa"
    };

    std::cout << "Se insertan 10 elementos distintos en el registro del algoritmo." << '\n';
    for (int i = 0; i < 10; i++) {
        hll.add(values[i]);
        std::cout << "Agregado: " << values[i] << '\n';
    }

    std::cout << "Se estima la cardinalidad usando HyperLogLog." << '\n';
    std::cout << "estimacion: " << hll.estimate() << '\n';
    return 0;
}
