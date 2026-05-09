#pragma once

#include "darray.hpp"
#include <list>
#include <utility>

template<typename K, typename V>
class HashTable {
    private:
        DArray<std::list<std::pair<K, V>>> buckets;
        size_t bucketCount;
        size_t hash(const K& key);

    public:
        HashTable();
        void insert(const K& key, const V& value);
        V get(const K& key);
        bool contains(const K& key);
};