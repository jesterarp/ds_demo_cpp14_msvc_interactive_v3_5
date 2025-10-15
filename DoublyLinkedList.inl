// DoublyLinkedList.inl

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr)
{
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &v)
{
    Node *n = new Node(v);
    if (!tail)
    {
        head = tail = n;
    }
    else
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

template <typename T>
bool DoublyLinkedList<T>::insert_before(const T &x, const T &y)
{
    bool result = false;
    Node *p = head;
    while (p && !result)
    {
        if (p->value == x)
        {
            Node *n = new Node(y);
            n->next = p;
            n->prev = p->prev;
            if (p->prev) { p->prev->next = n; } else { head = n; }
            p->prev = n;
            if (!n->next) { tail = n; }
            result = true;
        }
        else
        {
            p = p->next;
        }
    }
    return result;
}

template <typename T>
bool DoublyLinkedList<T>::erase(const T &x)
{
    bool result = false;
    Node *p = head;
    while (p && !result)
    {
        if (p->value == x)
        {
            if (p->prev) { p->prev->next = p->next; } else { head = p->next; }
            if (p->next) { p->next->prev = p->prev; } else { tail = p->prev; }
            delete p;
            result = true;
        }
        else
        {
            p = p->next;
        }
    }
    return result;
}

template <typename T>
void DoublyLinkedList<T>::print_forward(std::ostream &os) const
{
    const Node *p = head;
    bool first = true;
    os << "[";
    while (p)
    {
        if (!first) { os << " <-> "; }
        os << p->value;
        first = false;
        p = p->next;
    }
    os << "]\n";
}

template <typename T>
void DoublyLinkedList<T>::print_backward(std::ostream &os) const
{
    const Node *p = tail;
    bool first = true;
    os << "[";
    while (p)
    {
        if (!first) { os << " <-> "; }
        os << p->value;
        first = false;
        p = p->prev;
    }
    os << "]\n";
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    Node *p = head;
    while (p)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename T>
typename DoublyLinkedList<T>::Node* dll_merge_nodes(typename DoublyLinkedList<T>::Node *a,
                                                    typename DoublyLinkedList<T>::Node *b)
{
    typedef typename DoublyLinkedList<T>::Node Node;
    Node *newHead = nullptr;
    Node *tailMerge = nullptr;
    if (a || b)
    {
        if (!b || (a && a->value <= b->value))
        {
            newHead = a; a = a ? a->next : nullptr;
        }
        else
        {
            newHead = b; b = b ? b->next : nullptr;
        }
        tailMerge = newHead;
        while (a || b)
        {
            Node *pick = nullptr;
            if (!b || (a && a->value <= b->value))
            {
                pick = a; a = a ? a->next : nullptr;
            }
            else
            {
                pick = b; b = b ? b->next : nullptr;
            }
            tailMerge->next = pick;
            if (pick) { pick->prev = tailMerge; }
            tailMerge = pick;
        }
    }
    if (newHead) { newHead->prev = nullptr; }
    return newHead;
}

template <typename T>
void dll_split_nodes(typename DoublyLinkedList<T>::Node *source,
                     typename DoublyLinkedList<T>::Node* &front,
                     typename DoublyLinkedList<T>::Node* &back)
{
    front = source;
    back = nullptr;
    if (source && source->next)
    {
        typedef typename DoublyLinkedList<T>::Node Node;
        Node *slow = source;
        Node *fast = source->next;
        while (fast)
        {
            fast = fast->next;
            if (fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }
        front = source;
        back = slow->next;
        if (back) { back->prev = nullptr; }
        slow->next = nullptr;
    }
}

template <typename T>
void DoublyLinkedList<T>::sort()
{
    typedef typename DoublyLinkedList<T>::Node Node;
    std::function<Node*(Node*)> sort_rec = [&](Node *h) -> Node*
    {
        Node *ret = h;
        if (h && h->next)
        {
            Node *a = nullptr;
            Node *b = nullptr;
            dll_split_nodes<T>(h, a, b);
            a = sort_rec(a);
            b = sort_rec(b);
            ret = dll_merge_nodes<T>(a, b);
        }
        return ret;
    };
    head = sort_rec(head);
    Node *t = head;
    while (t && t->next) { t = t->next; }
    tail = t;
}
