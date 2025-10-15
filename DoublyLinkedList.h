// DoublyLinkedList.h
// DO-178B/C: strict single-return-per-function
#pragma once
#include <iostream>
#include <functional>

template <typename T>
class DoublyLinkedList
{
public:
    struct Node
    {
        T value;
        Node *prev;
        Node *next;
        explicit Node(const T &v) : value(v), prev(nullptr), next(nullptr) {}
    };

    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void push_back(const T &v);
    bool insert_before(const T &x, const T &y);
    bool erase(const T &x);
    void print_forward(std::ostream &os) const;
    void print_backward(std::ostream &os) const;
    void clear();
    void sort(); // in-place merge sort

private:
    Node *head;
    Node *tail;
};

#include "DoublyLinkedList.inl"
