// BinarySearchTree.h
// DO-178B/C: strict single-return-per-function
#pragma once
#include <iostream>
#include <string>

template <typename T>
class BinarySearchTree
{
public:
    struct Node
    {
        T value;
        Node *left;
        Node *right;
        explicit Node(const T &v) : value(v), left(nullptr), right(nullptr) {}
    };

    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    void insert(const T &v, bool announce = false);
    bool search(const T &v, bool trace = false) const;
    void clear();
    void print_ascii(std::ostream &os) const; // rotated: right up, left down

private:
    Node *root;
    static void destroy(Node *n);
    static void print_rec(std::ostream &os, Node *n, std::string indent, bool isRight);
};

#include "BinarySearchTree.inl"
