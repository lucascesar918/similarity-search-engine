#pragma once

#include <stdexcept>

template <typename T>
class DArray {
    private:
        T* data;
        size_t capacity;
        size_t size;
    public:
        DArray() {
            this->capacity = 4;
            this->size = 0;
            this->data = new T[this->capacity];
        }

        void append(T item) {
            if (this->size == this->capacity) {
                this->capacity *= 2;
                T* newData = new T[this->capacity];
                for (size_t i = 0; i < this->size; i++) {
                    newData[i] = this->data[i];
                }
                delete[] this->data;
                this->data = newData;
            }
            this->data[this->size++] = item;
        }

        size_t getSize() { return this->size; }

        T& operator[](size_t index) {
            if (index >= this->size) throw std::out_of_range("Index out of range");
            return this->data[index];
        }

        DArray(const DArray& other) {
            this->capacity = other.capacity;
            this->size = other.size;
            this->data = new T[this->capacity];
            for (size_t i = 0; i < this->size; i++) {
                this->data[i] = other.data[i];
            }
        }

        DArray& operator=(const DArray& other) {
            if (this != &other) {
                delete[] this->data;
                this->capacity = other.capacity;
                this->size = other.size;
                this->data = new T[this->capacity];
                for (size_t i = 0; i < this->size; i++) {
                    this->data[i] = other.data[i];
                }
            }
            return *this;
        }

        ~DArray() {
            delete[] this->data;
        }

        bool empty() { return this->size == 0; }

        T& back() {
            if (this->size == 0) throw std::out_of_range("Array is empty");
            return this->data[this->size - 1];
        }

        T* begin() { return this->data; }
        T* end() { return this->data + this->size; }
        const T* begin() const { return this->data; }
        const T* end() const { return this->data + this->size; }
        void clear() { this->size = 0; }
    };