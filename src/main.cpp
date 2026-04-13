#include <iostream>
#include <string>
#include "engine.hpp"

using namespace std;

int main() {
    cout << "[!] Inicializando motor de busca...\n";

    // Instancia motor
    // Indexa dados
    int totalDocs = 0;

    cout << "[!] Indexação concluída! " << totalDocs << " arquivos indexados na memória.\n";

    string busca;

    while (true) {
        cout << "\n=============================\n";
        cout << "Buscar por: ";
        getline(cin, busca);

        if (busca.empty()) continue;

        /* Pesquisa e resposta, onde ocorre o ETL da busca e é calculado o produto escalar
        motor.

        engine.search(busca);
        */
    }

    return 0;
}