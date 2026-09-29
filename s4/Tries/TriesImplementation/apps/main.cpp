#include "trie.h"

#include <limits>
#include <iostream>
#include <string>

int main() {
    Trie trie;

    int option = 0;
    while (option != 7) {
        std::cout << "\n===== MENU DEL TRIE =====" << '\n';
        std::cout << "1. Insertar palabra" << '\n';
        std::cout << "2. Buscar palabra" << '\n';
        std::cout << "3. Buscar prefijo" << '\n';
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
            std::cout << "Palabra a insertar: ";
            std::cin >> text;
            std::cout << (trie.insert(text) ? "Palabra insertada."
                                             : "No se pudo insertar la palabra.")
                      << '\n';
            break;
        case 2:
            std::cout << "Palabra a buscar: ";
            std::cin >> text;
            std::cout << (trie.contains(text) ? "La palabra existe."
                                              : "La palabra no existe.")
                      << '\n';
            break;
        case 3:
            std::cout << "Prefijo a buscar: ";
            std::cin >> text;
            std::cout << (trie.starts_with(text) ? "El prefijo existe."
                                                 : "El prefijo no existe.")
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
