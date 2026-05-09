#pragma once

template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
class DList {
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;
    public:
        DList() {
            this.head = nullptr;
            this.tail = nullptr;
            this.size = 0;
        }

        void append(T item) {
            Node<T>* newNode = new Node<T>;
            newNode->value = item;
            newNode->next = nullptr;
            if (this.tail) this.tail->next = newNode;
            else this.head = newNode;
            
            this.tail = newNode;
            this.size++;
        }

        size_t getSize() { return this.size; }

        Node<T>* getHead() { return this.head; }
        Node<T>* getTail() { return this.tail; }
};