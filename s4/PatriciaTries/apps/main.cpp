#include "patricia_trie.h"

#include <iostream>
#include <limits>
#include <string>

int main() {
    PatriciaTrie trie;
    int option = 0;

    while (option != 5) {
        std::cout << "\n===== PATRICIA TRIE =====" << '\n';
        std::cout << "1. Insertar palabra" << '\n';
        std::cout << "2. Buscar palabra" << '\n';
        std::cout << "3. Mostrar Patricia trie" << '\n';
        std::cout << "4. Mostrar cantidad de palabras" << '\n';
        std::cout << "5. Salir" << '\n';
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion invalida." << '\n';
            continue;
        }

        std::string word;
        switch (option) {
        case 1:
            std::cout << "Palabra a insertar: ";
            std::cin >> word;
            std::cout << (trie.insert(word) ? "Palabra insertada."
                                             : "No se pudo insertar la palabra.")
                      << '\n';
            break;
        case 2:
            std::cout << "Palabra a buscar: ";
            std::cin >> word;
            std::cout << (trie.contains(word) ? "La palabra existe."
                                              : "La palabra no existe.")
                      << '\n';
            break;
        case 3:
            std::cout << "\nPatricia trie (* indica fin de palabra):" << '\n';
            trie.print();
            break;
        case 4:
            std::cout << "Cantidad de palabras: " << trie.size() << '\n';
            break;
        case 5:
            std::cout << "Programa terminado." << '\n';
            break;
        default:
            std::cout << "Opcion invalida." << '\n';
            break;
        }
    }

    return 0;
}
