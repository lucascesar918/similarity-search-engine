#pragma once

#include <cstddef>

struct SparseNode {
    size_t termId;
    size_t frequency;
    SparseNode* next;
};

class SparseList {
    SparseNode* sentinel;
    size_t size;

public:
    SparseList()
        : sentinel(new SparseNode{0, 0, nullptr}), size(0) {
        sentinel->next = sentinel;
    }

    SparseList(const SparseList& other)
        : sentinel(new SparseNode{0, 0, nullptr}), size(0) {
        sentinel->next = sentinel;
        SparseNode* current = other.sentinel->next;
        while (current != other.sentinel) {
            add(current->termId);
            SparseNode* inserted = sentinel->next;
            while (inserted != sentinel && inserted->termId != current->termId) {
                inserted = inserted->next;
            }
            if (inserted != sentinel) {
                inserted->frequency = current->frequency;
            }
            current = current->next;
        }
    }

    SparseList& operator=(const SparseList& other) {
        if (this != &other) {
            clear();
            SparseNode* current = other.sentinel->next;
            while (current != other.sentinel) {
                add(current->termId);
                SparseNode* inserted = sentinel->next;
                while (inserted != sentinel && inserted->termId != current->termId) {
                    inserted = inserted->next;
                }
                if (inserted != sentinel) {
                    inserted->frequency = current->frequency;
                }
                current = current->next;
            }
        }
        return *this;
    }

    ~SparseList() {
        clear();
        delete sentinel;
    }

    void clear() {
        SparseNode* current = sentinel->next;
        while (current != sentinel) {
            SparseNode* next = current->next;
            delete current;
            current = next;
        }
        sentinel->next = sentinel;
        size = 0;
    }

    bool empty() const {
        return sentinel->next == sentinel;
    }

    size_t getSize() const {
        return size;
    }

    void add(size_t termId) {
        SparseNode* previous = sentinel;
        SparseNode* current = sentinel->next;

        while (current != sentinel && current->termId < termId) {
            previous = current;
            current = current->next;
        }

        if (current != sentinel && current->termId == termId) {
            current->frequency++;
            return;
        }

        SparseNode* node = new SparseNode{termId, 1, current};
        previous->next = node;
        size++;
    }

    int dotProduct(const SparseList& other) const {
        SparseNode* a = sentinel->next;
        SparseNode* b = other.sentinel->next;
        int score = 0;

        while (a != sentinel && b != other.sentinel) {
            if (a->termId == b->termId) {
                score += static_cast<int>(a->frequency * b->frequency);
                a = a->next;
                b = b->next;
            } else if (a->termId < b->termId) {
                a = a->next;
            } else {
                b = b->next;
            }
        }

        return score;
    }
};
