#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class DList {
    struct Node {
        T value;
        Node* next;
    };

    Node* sentinel;
    Node* tail;
    size_t listSize;

public:
    DList()
        : sentinel(new Node{T(), nullptr}), tail(nullptr), listSize(0) {
        sentinel->next = sentinel;
    }

    ~DList() {
        clear();
        delete sentinel;
    }

    void append(const T& item) {
        Node* node = new Node{item, sentinel};
        if (tail) {
            tail->next = node;
        } else {
            sentinel->next = node;
        }
        tail = node;
        listSize++;
    }

    bool contains(const T& item) const {
        Node* current = sentinel->next;
        while (current != sentinel) {
            if (current->value == item) return true;
            current = current->next;
        }
        return false;
    }

    size_t getSize() const {
        return listSize;
    }

    bool empty() const {
        return listSize == 0;
    }

    void clear() {
        Node* current = sentinel->next;
        while (current != sentinel) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        sentinel->next = sentinel;
        tail = nullptr;
        listSize = 0;
    }

    Node* getHead() const {
        return sentinel->next == sentinel ? nullptr : sentinel->next;
    }

    Node* getTail() const {
        return tail;
    }
};
