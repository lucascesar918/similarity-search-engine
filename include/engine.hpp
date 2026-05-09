#pragma once

#include "etl.hpp"

class Engine {
    private:
        const std::string dataPath;
        int totalDocs;
        ETL dataPipeline;

    public:
        Engine();
        // void loadData();
        // void processDocuments();
        // void search(const std::string& query);
};