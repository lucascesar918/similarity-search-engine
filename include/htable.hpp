#pragma once

#include <functional>
#include <stdexcept>
#include <cstddef>

template <typename T>
class HTable {
    private:
        size_t capacity;
        DArray<T>* table;

        size_t bucketIndex(const T& item) const {
            return std::hash<T>{}(item) % this->capacity;
        }

    public:
        explicit HTable(size_t capacity)
            : capacity(capacity), table(new DArray<T>[capacity]) {
        }

        HTable(const HTable& other)
            : capacity(other.capacity), table(new DArray<T>[other.capacity]) {
            for (size_t i = 0; i < this->capacity; i++) {
                this->table[i] = other.table[i];
            }
        }

        HTable& operator=(const HTable& other) {
            if (this != &other) {
                delete[] this->table;
                this->capacity = other.capacity;
                this->table = new DArray<T>[other.capacity];
                for (size_t i = 0; i < this->capacity; i++) {
                    this->table[i] = other.table[i];
                }
            }
            return *this;
        }

        void insert(const T& item) {
            size_t index = bucketIndex(item);
            if (!find(item)) {
                this->table[index].append(item);
            }
        }

        DArray<T>& operator[](size_t index) {
            if (index >= this->capacity) throw std::out_of_range("Index out of range");
            return this->table[index];
        }

        const DArray<T>& operator[](size_t index) const {
            if (index >= this->capacity) throw std::out_of_range("Index out of range");
            return this->table[index];
        }

        ~HTable() { delete[] this->table; }

        size_t getCapacity() const { return this->capacity; }

        bool find(const T& item) const {
            size_t index = bucketIndex(item);
            for (size_t i = 0; i < this->table[index].getSize(); i++) {
                if (this->table[index][i] == item) return true;
            }

            return false;
        }
};