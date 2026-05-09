#include <iostream>
#include <string>
#include "engine.hpp"
#include "etl.hpp"
#include "darray.hpp"

using namespace std;

int main() {
    cout << "[!] Inicializando motor de busca...\n";

    //Engine engine = Engine();
    
    // Indexa dados
    int totalDocs = 0;

    cout << "[!] Indexação concluída! " << totalDocs << " arquivos indexados na memória.\n";

    string busca;

    while (true) {
        cout << "\n=============================\n";
        cout << "Buscar por: ";
        getline(cin, busca);

        if (busca.empty()) continue;

        for (const auto& token : ETL::tokenize(busca)) cout << token << " ";

        /* Pesquisa e resposta, onde ocorre o ETL da busca e é calculado o produto escalar
        motor.

        engine.search(busca);
        */
    }

    return 0;
}