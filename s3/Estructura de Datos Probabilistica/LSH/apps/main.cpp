#include "lsh.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    LSH lsh(3, 5);

    std::vector<std::string> values = {
        "apple", "banana", "grape", "orange", "melon"
    };

    std::cout << "Se insertan 5 elementos para crear firmas LSH." << '\n';
    for (const auto& value : values) {
        lsh.add(value);
        std::cout << "Agregado: " << value << '\n';
    }

    std::cout << "Se consulta la firma de un elemento." << '\n';
    std::cout << "Firma de apple: " << lsh.signature("apple") << '\n';
    return 0;
}
