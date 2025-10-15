// SinglyLinkedList.inl
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr)
{
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    clear();
}

template <typename T>
void SinglyLinkedList<T>::push_front(const T &v)
{
    Node *n = new Node(v);
    n->next = head;
    head = n;
}

template <typename T>
void SinglyLinkedList<T>::push_back(const T &v)
{
    Node *n = new Node(v);
    if (!head)
    {
        head = n;
    }
    else
    {
        Node *p = head;
        while (p->next) { p = p->next; }
        p->next = n;
    }
}

template <typename T>
bool SinglyLinkedList<T>::insert_after(const T &x, const T &y)
{
    bool result = false;
    Node *p = head;
    while (p && !result)
    {
        if (p->value == x)
        {
            Node *n = new Node(y);
            n->next = p->next;
            p->next = n;
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
bool SinglyLinkedList<T>::pop_front()
{
    bool result = false;
    if (head)
    {
        Node *n = head;
        head = head->next;
        delete n;
        result = true;
    }
    return result;
}

template <typename T>
void SinglyLinkedList<T>::clear()
{
    Node *p = head;
    while (p)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
    head = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::print(std::ostream &os) const
{
    const Node *p = head;
    bool first = true;
    os << "[";
    while (p)
    {
        if (!first) { os << " -> "; }
        os << p->value;
        first = false;
        p = p->next;
    }
    os << "]\n";
}

template <typename T>
typename SinglyLinkedList<T>::Node* sll_merge_nodes(typename SinglyLinkedList<T>::Node *a, typename SinglyLinkedList<T>::Node *b)
{
    typedef typename SinglyLinkedList<T>::Node Node;
    Node *resultHead = nullptr;
    Node *tail = nullptr;
    if (a || b)
    {
        if (!b || (a && a->value <= b->value))
        {
            resultHead = a; a = a ? a->next : nullptr;
        }
        else
        {
            resultHead = b; b = b ? b->next : nullptr;
        }
        tail = resultHead;
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
            tail->next = pick;
            tail = pick;
        }
    }
    return resultHead;
}

template <typename T>
void sll_split_nodes(typename SinglyLinkedList<T>::Node *source,
                     typename SinglyLinkedList<T>::Node* &front,
                     typename SinglyLinkedList<T>::Node* &back)
{
    front = source;
    back = nullptr;
    if (source && source->next)
    {
        typedef typename SinglyLinkedList<T>::Node Node;
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
        slow->next = nullptr;
    }
}

template <typename T>
void SinglyLinkedList<T>::sort()
{
    typedef typename SinglyLinkedList<T>::Node Node;
    std::function<Node*(Node*)> sort_rec = [&](Node *h) -> Node*
    {
        Node *ret = h;
        if (h && h->next)
        {
            Node *a = nullptr;
            Node *b = nullptr;
            sll_split_nodes<T>(h, a, b);
            a = sort_rec(a);
            b = sort_rec(b);
            ret = sll_merge_nodes<T>(a, b);
        }
        return ret;
    };
    head = sort_rec(head);
}
