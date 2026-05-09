#pragma once

template <typename T>
struct Node {
    T value;
    Node<T>* next;
};

template <typename T>
class DStack {
    private:
        Node<T>* top;
        size_t size;

    public:
        DStack() {
            this.top = nullptr;
            this.size = 0;
        }

        void push(T item) {
            Node<T>* newNode = new Node<T>;
            newNode->value = item;
            newNode->next = this.top;
            this.top = newNode;
            this.size++;
        }

        T pop() {
            if (this.top == nullptr)
                throw std::runtime
        }
};