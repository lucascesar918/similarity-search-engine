#pragma once

#include <string>
#include "darray.hpp"

class ETL {
public:
    static DArray<std::string> tokenize(std::string text);
    static std::string deaccent(std::string data);
    static void removeAdjacentDuplicates(DArray<std::string>& tokens);
};
