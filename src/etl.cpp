#include "etl.hpp"
#include "darray.hpp"

using namespace std;

DArray<string> ETL::tokenize(string data) {
    DArray<string> tokens;
    string current_token;

    for (char c : data) {
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