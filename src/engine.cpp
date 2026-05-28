#include "engine.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

Engine::Engine()
    : dataPath("data/"), totalDocs(0), dictionary(32), reverseDictionary(), fileQueue(), history(), documents() {
}

size_t Engine::getTermId(const std::string& token) {
    size_t* existing = dictionary.find(token);
    if (existing) {
        return *existing;
    }

    size_t newId = reverseDictionary.getSize() + 1;
    dictionary.insert(token, newId);
    reverseDictionary.append(token);
    return newId;
}

void Engine::indexDocument(const std::string& path, const DArray<std::string>& tokens) {
    Document doc(path);
    for (size_t i = 0; i < tokens.getSize(); i++) {
        size_t termId = getTermId(tokens[i]);
        doc.addTerm(termId);
    }
    documents.append(doc);
}

void Engine::loadData() {
    namespace fs = std::filesystem;

    documents.clear();
    totalDocs = 0;
    dictionary = HTable<std::string, size_t>(32);
    reverseDictionary.clear();
    history.clear();
    fileQueue.clear();

    if (!fs::exists(dataPath) || !fs::is_directory(dataPath)) {
        std::cerr << "[!] Diretório de dados não encontrado: " << dataPath << "\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(dataPath)) {
        if (!entry.is_regular_file()) continue;
        fileQueue.enqueue(entry.path().string());
    }

    while (!fileQueue.empty()) {
        std::string path = fileQueue.dequeue();
        std::ifstream input(path);
        if (!input.is_open()) {
            std::cerr << "[!] Não foi possível abrir " << path << "\n";
            continue;
        }

        std::string content;
        std::string line;
        while (std::getline(input, line)) {
            content += line;
            content += '\n';
        }

        history.push(content);
        DArray<std::string> tokens = ETL::tokenize(content);
        std::string tokenList;
        for (size_t i = 0; i < tokens.getSize(); i++) {
            if (i > 0) tokenList += ' ';
            tokenList += tokens[i];
        }
        history.push(tokenList);

        indexDocument(path, tokens);
        totalDocs++;
    }

    std::cout << "[!] Indexação concluída: " << totalDocs << " documentos carregados." << std::endl;
}

void Engine::search(const std::string& query) {
    DArray<std::string> queryTokens = ETL::tokenize(query);
    if (queryTokens.empty()) {
        std::cout << "[!] Nenhum token encontrado na busca." << std::endl;
        return;
    }

    SparseList queryVector;
    for (size_t i = 0; i < queryTokens.getSize(); i++) {
        const std::string& token = queryTokens[i];
        size_t* id = dictionary.find(token);
        if (id) {
            queryVector.add(*id);
        }
    }

    if (queryVector.empty()) {
        std::cout << "[!] Nenhum termo conhecido encontrado na busca." << std::endl;
        return;
    }

    BST results;
    for (size_t i = 0; i < documents.getSize(); i++) {
        const Document& doc = documents[i];
        int score = doc.scoreWith(queryVector);
        if (score > 0) {
            results.insert(i, score);
        }
    }

    DArray<SearchResult> ordered;
    results.collectResults(ordered);

    std::cout << "[!] Resultados de similaridade para: " << query << std::endl;
    if (ordered.empty()) {
        std::cout << "  Nenhum documento similar encontrado." << std::endl;
        return;
    }

    for (size_t i = 0; i < std::min<size_t>(ordered.getSize(), 10); i++) {
        const SearchResult& result = ordered[i];
        std::cout << "  " << (i + 1) << ". " << documents[result.documentIndex].path << " (score=" << result.score << ")" << std::endl;
    }
}
