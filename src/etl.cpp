#include "etl.hpp"
#include "darray.hpp"
#include <locale>
#include <codecvt>

using namespace std;

DArray<string> ETL::tokenize(string data) {
    DArray<string> tokens;
    string current_token;

    // Primeiro remove acentos da string inteira usando deaccent
    string processed_data = ETL::deaccent(data);

    for (char c : processed_data) {
        if (isalnum(c)) {
            current_token += tolower(c);
            continue;
        }

        if (!current_token.empty()) {
            if (tokens.empty() || tokens.back() != current_token)
                tokens.append(current_token);
            
            current_token.clear();
        }
    }

    if (!current_token.empty() && (tokens.empty() || tokens.back() != current_token))
        tokens.append(current_token);

    return tokens;
}

// Só serão tirados os acentos que estão em caracteres em minúsculo, pois a função tokenize já converte tudo para minúsculo
std::string ETL::deaccent(std::string data) {
    std::string search[]  = {"á","à","â","ã","é","è","ê","í","ì","î","ó","ò","ô","õ","ú","ù","û","ç"};
    std::string replace[] = {"a","a","a","a","e","e","e","i","i","i","o","o","o","o","u","u","u","c"};

    for (size_t i = 0; i < sizeof(search) / sizeof(search[0]); i++) {
        size_t pos = data.find(search[i]);
        while (pos != std::string::npos) {
            data.replace(pos, search[i].length(), replace[i]);
            pos = data.find(search[i], pos + replace[i].length());
        }
    }
    return data;
}

