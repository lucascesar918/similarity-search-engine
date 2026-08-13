#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class DStack {
    struct StackNode {
        T value;
        StackNode* next;
    };

    StackNode* topNode;
    size_t stackSize;

public:
    DStack()
        : topNode(nullptr), stackSize(0) {}

    DStack(const DStack&) = delete;
    DStack& operator=(const DStack&) = delete;

    ~DStack() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& item) {
        StackNode* node = new StackNode{item, topNode};
        topNode = node;
        stackSize++;
    }

    T pop() {
        if (topNode == nullptr) {
            throw std::out_of_range("Pilha vazia");
        }
        StackNode* node = topNode;
        T value = node->value;
        topNode = node->next;
        delete node;
        stackSize--;
        return value;
    }

    const T& top() const {
        if (topNode == nullptr) {
            throw std::out_of_range("Pilha vazia");
        }
        return topNode->value;
    }

    bool empty() const {
        return stackSize == 0;
    }

    size_t getSize() const {
        return stackSize;
    }
};
