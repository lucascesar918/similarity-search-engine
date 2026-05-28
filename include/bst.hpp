#pragma once

#include "darray.hpp"
#include <cstddef>

struct SearchResult {
    size_t documentIndex;
    int score;
};

class BST {
    struct Node {
        size_t documentIndex;
        int score;
        Node* left;
        Node* right;
    };

    Node* root;

    void insertNode(Node*& current, size_t docIndex, int score) {
        if (!current) {
            current = new Node{docIndex, score, nullptr, nullptr};
            return;
        }

        if (score > current->score || (score == current->score && docIndex < current->documentIndex)) {
            insertNode(current->left, docIndex, score);
        } else {
            insertNode(current->right, docIndex, score);
        }
    }

    void collectReverse(Node* current, DArray<SearchResult>& results) const {
        if (!current) return;
        collectReverse(current->right, results);
        results.append(SearchResult{current->documentIndex, current->score});
        collectReverse(current->left, results);
    }

    void clear(Node* current) {
        if (!current) return;
        clear(current->left);
        clear(current->right);
        delete current;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(size_t documentIndex, int score) {
        insertNode(root, documentIndex, score);
    }

    void collectResults(DArray<SearchResult>& results) const {
        collectReverse(root, results);
    }
};
