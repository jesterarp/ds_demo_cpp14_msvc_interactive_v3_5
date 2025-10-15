// SinglyLinkedList.h
// DO-178B/C: strict single-return-per-function
#pragma once
#include <iostream>
#include <sstream>
#include <functional>

template <typename T>
class SinglyLinkedList
{
public:
    struct Node
    {
        T value;
        Node *next;
        explicit Node(const T &v) : value(v), next(nullptr) {}
    };

    SinglyLinkedList();
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    void push_front(const T &v);
    void push_back(const T &v);
    bool insert_after(const T &x, const T &y);
    bool pop_front();
    void clear();
    void print(std::ostream &os) const;
    void sort(); // in-place merge sort

private:
    Node *head;
};

#include "SinglyLinkedList.inl"
