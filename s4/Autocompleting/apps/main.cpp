#include "trie.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main() {
    Trie trie;
    int option = 0;

    while (option != 7) {
        std::cout << "\n===== SISTEMA DE AUTOCOMPLETADO =====" << '\n';
        std::cout << "1. Agregar palabra" << '\n';
        std::cout << "2. Autocompletar prefijo" << '\n';
        std::cout << "3. Buscar palabra exacta" << '\n';
        std::cout << "4. Eliminar palabra" << '\n';
        std::cout << "5. Mostrar cantidad de palabras" << '\n';
        std::cout << "6. Mostrar grafico del trie" << '\n';
        std::cout << "7. Salir" << '\n';
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion invalida." << '\n';
            continue;
        }

        std::string text;
        switch (option) {
        case 1:
            std::cout << "Palabra a agregar: ";
            std::cin >> text;
            std::cout << (trie.insert(text) ? "Palabra agregada."
                                             : "No se pudo agregar la palabra.")
                      << '\n';
            break;
        case 2: {
            std::cout << "Prefijo: ";
            std::cin >> text;
            std::vector<std::string> suggestions = trie.autocomplete(text);
            if (suggestions.empty()) {
                std::cout << "No hay sugerencias para ese prefijo." << '\n';
                break;
            }

            std::cout << "Sugerencias:" << '\n';
            for (const auto& suggestion : suggestions) {
                std::cout << "- " << suggestion << '\n';
            }
            break;
        }
        case 3:
            std::cout << "Palabra a buscar: ";
            std::cin >> text;
            std::cout << (trie.contains(text) ? "La palabra existe."
                                              : "La palabra no existe.")
                      << '\n';
            break;
        case 4:
            std::cout << "Palabra a eliminar: ";
            std::cin >> text;
            std::cout << (trie.erase(text) ? "Palabra eliminada."
                                            : "La palabra no existe.")
                      << '\n';
            break;
        case 5:
            std::cout << "Cantidad de palabras: " << trie.size() << '\n';
            break;
        case 6:
            std::cout << "\nGrafico del trie (* indica fin de palabra):" << '\n';
            trie.print();
            break;
        case 7:
            std::cout << "Programa terminado." << '\n';
            break;
        default:
            std::cout << "Opcion invalida." << '\n';
            break;
        }
    }

    return 0;
}
