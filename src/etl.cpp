#include "etl.hpp"
#include <cctype>

using namespace std;

DArray<string> ETL::tokenize(string data)
{
    DArray<string> tokens;
    string current_token;
    string processed_data = deaccent(data);

    for (char raw : processed_data)
    {
        unsigned char c = static_cast<unsigned char>(raw);
        if (isalnum(c))
        {
            current_token += static_cast<char>(tolower(c));
            continue;
        }

        if (!current_token.empty())
        {
            tokens.append(current_token);
            current_token.clear();
        }
    }

    if (!current_token.empty())
    {
        tokens.append(current_token);
    }

    removeAdjacentDuplicates(tokens);
    return tokens;
}

std::string ETL::deaccent(std::string data)
{
    std::string search[] = {"á", "à", "â", "ã", "é", "è", "ê", "í", "ì", "î", "ó", "ò", "ô", "õ", "ú", "ù", "û", "ç", "Á", "À", "Â", "Ã", "É", "È", "Ê", "Í", "Ì", "Î", "Ó", "Ò", "Ô", "Õ", "Ú", "Ù", "Û", "Ç"};
    std::string replace[] = {"a", "a", "a", "a", "e", "e", "e", "i", "i", "i", "o", "o", "o", "o", "u", "u", "u", "c", "A", "A", "A", "A", "E", "E", "E", "I", "I", "I", "O", "O", "O", "O", "U", "U", "U", "C"};

    for (size_t i = 0; i < sizeof(search) / sizeof(search[0]); i++)
    {
        size_t pos = data.find(search[i]);
        while (pos != std::string::npos)
        {
            data.replace(pos, search[i].length(), replace[i]);
            pos = data.find(search[i], pos + replace[i].length());
        }
    }
    return data;
}

void ETL::removeAdjacentDuplicates(DArray<std::string> &tokens)
{
    if (tokens.getSize() <= 1)
        return;

    size_t writePos = 0;
    for (size_t readPos = 1; readPos < tokens.getSize(); readPos++)
    {
        if (tokens[readPos] != tokens[writePos])
        {
            writePos++;
            tokens[writePos] = tokens[readPos];
        }
    }

    while (tokens.getSize() > writePos + 1)
        tokens.removeAt(tokens.getSize() - 1);
}
