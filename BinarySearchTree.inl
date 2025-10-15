// BinarySearchTree.inl
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr)
{
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    clear();
}

template <typename T>
void BinarySearchTree<T>::destroy(Node *n)
{
    if (n)
    {
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

template <typename T>
void BinarySearchTree<T>::clear()
{
    destroy(root);
    root = nullptr;
}

template <typename T>
void BinarySearchTree<T>::insert(const T &v, bool announce)
{
    if (announce)
    {
        std::cout << "Inserted " << v << "\n";
    }

    if (!root)
    {
        root = new Node(v);
    }
    else
    {
        Node *p = root;
        bool placed = false;
        while (!placed)
        {
            if (v < p->value)
            {
                if (!p->left)
                {
                    p->left = new Node(v);
                    placed = true;
                }
                else
                {
                    p = p->left;
                }
            }
            else
            {
                if (!p->right)
                {
                    p->right = new Node(v);
                    placed = true;
                }
                else
                {
                    p = p->right;
                }
            }
        }
    }

    print_ascii(std::cout);
    std::cout << "\n";
}

template <typename T>
bool BinarySearchTree<T>::search(const T &v, bool trace) const
{
    bool found = false;
    Node *p = root;
    while (p && !found)
    {
        if (trace) { std::cout << "visit " << p->value << "\n"; }
        if (v == p->value) { found = true; }
        else if (v < p->value) { p = p->left; }
        else { p = p->right; }
    }
    return found;
}

template <typename T>
void BinarySearchTree<T>::print_rec(std::ostream &os, Node *n, std::string indent, bool isRight)
{
    if (n)
    {
        if (n->right) { print_rec(os, n->right, indent + "    ", true); }
        os << indent << (isRight ? "/-- " : "\\-- ") << n->value << "\n";
        if (n->left) { print_rec(os, n->left, indent + "    ", false); }
    }
}

template <typename T>
void BinarySearchTree<T>::print_ascii(std::ostream &os) const
{
    if (!root)
    {
        os << "(empty)\n";
    }
    else
    {
        print_rec(os, root, "", true);
    }
}
