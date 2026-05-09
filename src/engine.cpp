#include "engine.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

Engine::Engine()
    : dataPath("data/"), totalDocs(0) {
}

void Engine::loadData() {
    namespace fs = std::filesystem;

    documents.clear();
    totalDocs = 0;

    if (!fs::exists(dataPath) || !fs::is_directory(dataPath)) {
        std::cerr << "[!] Diretório de dados não encontrado: " << dataPath << '\n';
        return;
    }

    for (const auto& entry : fs::directory_iterator(dataPath)) {
        if (!entry.is_regular_file()) continue;

        std::ifstream input(entry.path());
        if (!input.is_open()) continue;

        std::string content;
        std::string line;
        while (std::getline(input, line)) {
            content += line;
            content += '\n';
        }

        DArray<std::string> tokens = ETL::tokenize(content);
        Engine::Document doc(entry.path().string(), std::max<size_t>(tokens.getSize() * 2 + 1, 16));

        for (size_t i = 0; i < tokens.getSize(); i++) {
            doc.addToken(tokens[i]);
        }

        documents.append(doc);
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

    HTable<std::string> queryTable(std::max<size_t>(queryTokens.getSize() * 2 + 1, 16));
    for (size_t i = 0; i < queryTokens.getSize(); i++) {
        queryTable.insert(queryTokens[i]);
    }

    std::vector<std::pair<double, std::string>> results;
    results.reserve(totalDocs);

    for (size_t i = 0; i < documents.getSize(); i++) {
        const Document& doc = documents[i];
        size_t intersection = 0;

        for (size_t j = 0; j < queryTokens.getSize(); j++) {
            if (doc.contains(queryTokens[j])) {
                intersection++;
            }
        }

        if (intersection == 0) continue;

        double score = static_cast<double>(intersection) / static_cast<double>(queryTokens.getSize());
        results.emplace_back(score, doc.path);
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    std::cout << "[!] Resultados de similaridade para: " << query << std::endl;
    if (results.empty()) {
        std::cout << "  Nenhum documento similar encontrado." << std::endl;
        return;
    }

    for (size_t i = 0; i < std::min<size_t>(results.size(), 10); i++) {
        std::cout << "  " << (i + 1) << ". " << results[i].second << " (score=" << results[i].first << ")" << std::endl;
    }
}
