#include <iostream>
using namespace std;

template <class T, int Order>
struct Node
{
    int actual_number_of_keys;
    int t;
    int pos;
    T *keys;
    Node **children;

    Node(int t);
    bool InsertToNode(T value);
    Node *Split(T *med);
    ~Node();
};

template <class T, int Order>
Node<T, Order>::Node(int _t)
{
    t = _t;
    actual_number_of_keys = 0;
    pos = -1;
    keys = new T[t];
    children = new Node *[t + 1];
    for (int i = 0; i <= t; ++i)
        children[i] = nullptr;
}

template <class T, int Order>
bool Node<T, Order>::InsertToNode(T value)
{
    if (children[0] == nullptr)
    {
        pos++;
        actual_number_of_keys++;
        keys[pos] = value;

        for (int i = pos; i > 0; --i)
        {
            if (keys[i] < keys[i - 1])
                swap(keys[i], keys[i - 1]);
        }
    }
    else
    {
        int i = 0;
        while (i < actual_number_of_keys && value > keys[i])
            i++;

        if (children[i]->InsertToNode(value))
        {
            T mid;
            Node *newNode = children[i]->Split(&mid);

            for (int j = actual_number_of_keys; j > i; --j)
            {
                keys[j] = keys[j - 1];
                children[j + 1] = children[j];
            }
            keys[i] = mid;
            children[i + 1] = newNode;

            actual_number_of_keys++;
            pos++;
        }
    }

    return (actual_number_of_keys == t);
}

template <class T, int Order>
Node<T, Order> *Node<T, Order>::Split(T *promotedKey)
{
    int midIndex = actual_number_of_keys / 2;
    *promotedKey = keys[midIndex];

    Node *newNode = new Node(t);

    for (int i = midIndex + 1; i < actual_number_of_keys; ++i)
    {
        newNode->keys[newNode->pos + 1] = keys[i];
        newNode->children[newNode->pos + 1] = children[i];

        newNode->pos += 1;
        newNode->actual_number_of_keys += 1;
    }

    newNode->children[newNode->pos + 1] = children[actual_number_of_keys];
    actual_number_of_keys = midIndex;
    pos = midIndex - 1;

    return newNode;
}

template <class T, int Order>
Node<T, Order>::~Node()
{
    delete[] keys;
    for (int i = 0; i <= actual_number_of_keys; ++i)
        delete children[i];
    delete[] children;
}

template <class T, int Order>
class BTree
{
    Node<T, Order> *Root;
    int order;

public:
    BTree();
    void Insert(T value);
    void Print() const;
    ~BTree();
};

template <class T, int Order>
BTree<T, Order>::BTree()
{
    order = Order;
    Root = nullptr;
}

template <class T, int Order>
void BTree<T, Order>::Insert(T value)
{
    if (Root == nullptr)
    {
        Root = new Node<T, Order>(order);
        Root->keys[++Root->pos] = value;
        Root->actual_number_of_keys = 1;
    }
    else
    {
        if (Root->InsertToNode(value))
        {
            T mid;
            Node<T, Order> *newRoot = new Node<T, Order>(order);
            Node<T, Order> *splittedNode = Root->Split(&mid);

            newRoot->keys[++newRoot->pos] = mid;
            newRoot->actual_number_of_keys = 1;
            newRoot->children[0] = Root;
            newRoot->children[1] = splittedNode;

            Root = newRoot;
        }
    }
}

template <class T, int Order>
void BTree<T, Order>::Print() const
{
    if (Root == nullptr)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    auto printNode = [](auto &self, Node<T, Order> *node, int depth) -> void
    {
        if (node == nullptr)
            return;

        cout << string("  ", depth);

        cout << " ";
        for (int i = 0; i < node->actual_number_of_keys; ++i)
        {
            cout << node->keys[i];
            if (i < node->actual_number_of_keys - 1)
                cout << ",";
        }
        cout << " " << endl;

        for (int i = 0; i <= node->actual_number_of_keys; ++i)
        {
            if (node->children[i] != nullptr)
            {
                self(self, node->children[i], depth + 1);
            }
        }
    };

    printNode(printNode, Root, 0);
}

template <class T, int Order>
BTree<T, Order>::~BTree()
{
    delete Root;
}

int main()
{
    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();

    /*
    1,4
        0
        2,3
        5
    */

    cout << '\n';
    BTree<char, 5> t2;

    t2.Insert('G');
    t2.Insert('I');
    t2.Insert('B');
    t2.Insert('J');
    t2.Insert('C');
    t2.Insert('A');
    t2.Insert('K');
    t2.Insert('E');
    t2.Insert('D');
    t2.Insert('S');
    t2.Insert('T');
    t2.Insert('R');
    t2.Insert('L');
    t2.Insert('F');
    t2.Insert('H');
    t2.Insert('M');
    t2.Insert('N');
    t2.Insert('P');
    t2.Insert('Q');
    t2.Print();
    /*
    K
        C,G
            A,B
             D,E,F
            H,I,J
         N,R
             L,M
             P,Q
            S,T
    */
    return 0;
}
