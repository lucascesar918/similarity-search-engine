#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class DQueue {
    struct Node {
        T value;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DQueue()
        : head(nullptr), tail(nullptr), size(0) {
    }

    DQueue(const DQueue&) = delete;
    DQueue& operator=(const DQueue&) = delete;

    ~DQueue() {
        clear();
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(const T& item) {
        Node* node = new Node{item, nullptr};
        if (tail) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
        size++;
    }

    T dequeue() {
        if (empty()) throw std::out_of_range("Fila vazia");
        Node* node = head;
        T value = node->value;
        head = node->next;
        if (!head) tail = nullptr;
        delete node;
        size--;
        return value;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("Fila vazia");
        return head->value;
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};
