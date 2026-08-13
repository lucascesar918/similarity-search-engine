#pragma once

#include <string>
#include "etl.hpp"
#include "darray.hpp"
#include "htable.hpp"
#include "queue.hpp"
#include "sparse_list.hpp"
#include "bst.hpp"

class Engine {
    private:
        struct Document {
            std::string path;
            SparseList terms;

            Document() : path() {}
            explicit Document(const std::string& path) : path(path) {}

            void addTerm(size_t termId) {
                terms.add(termId);
            }

            int scoreWith(const SparseList& query) const {
                return terms.dotProduct(query);
            }
        };

        const std::string dataPath;
        int totalDocs;
        HTable<std::string, size_t> dictionary;
        DArray<std::string> reverseDictionary;
        DQueue<std::string> fileQueue;
        DArray<Document> documents;

        size_t getTermId(const std::string& token);
        void indexDocument(const std::string& path, const DArray<std::string>& tokens);

    public:
        Engine();
        void loadData();
        void search(const std::string& query);
};
