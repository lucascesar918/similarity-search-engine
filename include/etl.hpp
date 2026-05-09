#pragma once

#include <string>
#include "darray.hpp"

class ETL {
public:
    static DArray<std::string> tokenize(std::string text);

};