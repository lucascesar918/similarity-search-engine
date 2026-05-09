#pragma once

#include <string>
#include "etl.hpp"
#include "darray.hpp"
#include "htable.hpp"

class Engine {
    private:
        struct Document {
            std::string path;
            HTable<std::string> tokenTable;
            size_t tokenCount;

            Document()
                : path(), tokenTable(16), tokenCount(0) {}

            Document(const std::string& path, size_t hashCapacity)
                : path(path), tokenTable(hashCapacity), tokenCount(0) {}

            void addToken(const std::string& token) {
                if (!tokenTable.find(token)) {
                    tokenTable.insert(token);
                    tokenCount++;
                }
            }

            bool contains(const std::string& token) const {
                return tokenTable.find(token);
            }
        };

        const std::string dataPath;
        int totalDocs;
        ETL dataPipeline;
        DArray<Document> documents;

    public:
        Engine();
        void loadData();
        void search(const std::string& query);
};