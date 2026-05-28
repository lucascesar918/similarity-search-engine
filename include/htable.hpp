#pragma once

#include <functional>
#include <stdexcept>
#include <cstddef>
#include "darray.hpp"

template <typename K, typename V>
class HTable {
    struct Entry {
        K key;
        V value;
    };

    size_t capacity;
    DArray<Entry>* table;

    size_t bucketIndex(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

public:
    explicit HTable(size_t capacity)
        : capacity(capacity), table(new DArray<Entry>[capacity]) {
    }

    HTable(const HTable& other)
        : capacity(other.capacity), table(new DArray<Entry>[other.capacity]) {
        for (size_t i = 0; i < capacity; i++) {
            table[i] = other.table[i];
        }
    }

    HTable& operator=(const HTable& other) {
        if (this != &other) {
            delete[] table;
            capacity = other.capacity;
            table = new DArray<Entry>[other.capacity];
            for (size_t i = 0; i < capacity; i++) {
                table[i] = other.table[i];
            }
        }
        return *this;
    }

    ~HTable() {
        delete[] table;
    }

    bool insert(const K& key, const V& value) {
        size_t index = bucketIndex(key);
        DArray<Entry>& bucket = table[index];
        for (size_t i = 0; i < bucket.getSize(); i++) {
            if (bucket[i].key == key) {
                return false;
            }
        }
        bucket.append(Entry{key, value});
        return true;
    }

    V* find(const K& key) {
        size_t index = bucketIndex(key);
        DArray<Entry>& bucket = table[index];
        for (size_t i = 0; i < bucket.getSize(); i++) {
            if (bucket[i].key == key) {
                return &bucket[i].value;
            }
        }
        return nullptr;
    }

    const V* find(const K& key) const {
        size_t index = bucketIndex(key);
        const DArray<Entry>& bucket = table[index];
        for (size_t i = 0; i < bucket.getSize(); i++) {
            if (bucket[i].key == key) {
                return &bucket[i].value;
            }
        }
        return nullptr;
    }

    bool contains(const K& key) const {
        return find(key) != nullptr;
    }
};
