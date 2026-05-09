#include <iostream>
#include <string>
#include "engine.hpp"
#include "etl.hpp"
#include "darray.hpp"

using namespace std;

int main() {
    cout << "[!] Inicializando motor de busca...\n";

    Engine engine;
    engine.loadData();

    string busca;

    while (true) {
        cout << "\n=============================\n";
        cout << "Buscar por: ";
        getline(cin, busca);

        if (busca.empty()) continue;

        engine.search(busca);
    }

    return 0;
}