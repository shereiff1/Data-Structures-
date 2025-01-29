#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
template <class T>
struct RBTNode
{
    string color;
    T data;
    RBTNode *right, *left, *parent;
    RBTNode(T Data) : color("Red"), data(Data), right(nullptr), left(nullptr), parent(nullptr) {};
};
template <class T>
class RBT
{
    RBTNode<T> *root = nullptr;
    void leftRotation(RBTNode<T> *&node);
    void rightRotation(RBTNode<T> *&node);
    void insertionHandler(RBTNode<T> *&node);
    void deletionHandler(RBTNode<T> *&node);
    void printHandler(RBTNode<T> *node, string s);
    RBTNode<T> *successor(RBTNode<T> *node);
    RBTNode<T> *determineNodeTobeDeleted(RBTNode<T> *node);
    void deleteTree(RBTNode<T> *node);

public:
    void insert(T element);
    void remove(T element);
    void print();
    void search(T element);
    ~RBT();
};
// RBT implementation
template <class T>
void RBT<T>::leftRotation(RBTNode<T> *&node)
{
    if (!node)
        return;
    RBTNode<T> *rightNode = node->right;
    RBTNode<T> *parentNode = node->parent;
    if (rightNode)
    {
        node->right = rightNode->left;
        if (rightNode->left)
            rightNode->left->parent = node;
        rightNode->left = node;
        node->parent = rightNode;
        rightNode->parent = parentNode;
        if (parentNode == nullptr)
        {
            root = rightNode;
        }
        else
        {
            if (parentNode->left == node)
                parentNode->left = rightNode;
            else
            {
                parentNode->right = rightNode;
            }
        }
    }
}
template <class T>
void RBT<T>::rightRotation(RBTNode<T> *&node)
{
    if (!node)
        return;
    RBTNode<T> *leftChild = node->left, *parentNode = node->parent;
    if (leftChild)
    {
        node->left = leftChild->right;
        if (leftChild->right)
            leftChild->right->parent = node;
        leftChild->right = node;
        node->parent = leftChild;
        leftChild->parent = parentNode;
        if (parentNode == nullptr)
            root = leftChild;
        else
        {
            if (parentNode->left == node)
                parentNode->left = leftChild;
            else
                parentNode->right = leftChild;
        }
    }
}
template <class T>
void RBT<T>::insertionHandler(RBTNode<T> *&node)
{
    RBTNode<T> *parentNode = node->parent;
    if (!parentNode)
    {
        node->color = "Black";
        return;
    }
    RBTNode<T> *grandParent = parentNode->parent;
    if (!grandParent)
    {
        parentNode->color = "Black";
        return;
    }
    if (!(parentNode->color == "Red" && node->color == "Red"))
    {
        return;
    }
    RBTNode<T> *Uncle = nullptr;
    string uncleColor = "Black";
    if (grandParent->left == parentNode)
        Uncle = grandParent->right;
    else
        Uncle = grandParent->left;
    if (Uncle)
        uncleColor = Uncle->color;
    if (uncleColor == "Red")
    {
        grandParent->color = "Red";
        parentNode->color = "Black";
        Uncle->color = "Black";
        insertionHandler(grandParent);
    }
    else
    {
        if (parentNode->left == node && grandParent->left == parentNode)
        {
            rightRotation(grandParent);
            parentNode->color = "Black";
            grandParent->color = "Red";
        }
        else if (parentNode->right == node && grandParent->right == parentNode)
        {
            leftRotation(grandParent);
            parentNode->color = "Black";
            grandParent->color = "Red";
        }
        else if (parentNode->left == node && grandParent->right == parentNode)
        {
            rightRotation(parentNode);
            insertionHandler(parentNode);
        }
        else
        {
            leftRotation(parentNode);
            insertionHandler(parentNode);
        }
    }
}
template <class T>
void RBT<T>::printHandler(RBTNode<T> *root, string s)
{
    if (!root)
        return;
    cout << s;
    cout << root->data << " " << root->color << endl;
    s += " ";
    printHandler(root->left, s);
    printHandler(root->right, s);
}
template <class T>
void RBT<T>::print()
{
    printHandler(root, "");
}
template <class T>
void RBT<T>::insert(T element)
{
    RBTNode<T> *current = root;
    RBTNode<T> *parent = nullptr;
    if (!current)
    {
        root = new RBTNode<T>(element);
        root->color = "Black";
        return;
    }
    while (current)
    {
        parent = current;
        if (current->data > element)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    RBTNode<T> *newNode = new RBTNode<T>(element);
    if (newNode->data > parent->data)
    {
        parent->right = newNode;
    }
    else
    {
        parent->left = newNode;
    }
    newNode->parent = parent;
    insertionHandler(newNode);
}
template <class T>
void RBT<T>::deletionHandler(RBTNode<T> *&node)
{
    if (!node)
        return;

    RBTNode<T> *parentNode = node->parent;
    RBTNode<T> *sibling = nullptr;

    if (parentNode)
    {
        sibling = (parentNode->left == node) ? parentNode->right : parentNode->left;
    }
    else
    {
        node->color = "Black";
        return;
    }
    if (node->color == "DB")
    {
        if (sibling && sibling->color == "Red")
        {
            sibling->color = "Black";
            parentNode->color = "Red";
            if (parentNode->left == node)
                leftRotation(parentNode);
            else
                rightRotation(parentNode);
            sibling = (parentNode->left == node) ? parentNode->right : parentNode->left;
        }
        if (sibling)
        {
            bool farChildRed = false;
            bool nearChildRed = false;
            RBTNode<T> *farchild = nullptr, *nearChild = nullptr;
            if (parentNode->left == node)
            {
                farchild = sibling->right;
                nearChild = sibling->left;
                farChildRed = (sibling->right && sibling->right->color == "Red");
                nearChildRed = (sibling->left && sibling->left->color == "Red");
            }
            else
            {
                farchild = sibling->left;
                nearChild = sibling->right;
                farChildRed = (sibling->left && sibling->left->color == "Red");
                nearChildRed = (sibling->right && sibling->right->color == "Red");
            }
            if (farChildRed)
            {
                farchild->color = "Black";
                swap(parentNode->color, sibling->color);
                if (parentNode->left == node)
                {
                    leftRotation(parentNode);
                }
                else
                {
                    rightRotation(parentNode);
                }
            }
            else if (nearChildRed)
            {
                sibling->color = "Red";
                nearChild->color = "Black";
                if (parentNode->right == sibling)
                    rightRotation(sibling);
                else
                    leftRotation(sibling);
                deletionHandler(node);
            }
            else
            {
                sibling->color = "Red";
                if (parentNode->color == "Red")
                    parentNode->color = "Black";
                else
                    parentNode->color = "DB";
                if (parentNode->color == "DB")
                    deletionHandler(parentNode);
            }
        }
    }

    if (node == root)
    {
        delete root;
        root = nullptr;
    }
}

template <class T>
RBTNode<T> *RBT<T>::successor(RBTNode<T> *node)
{
    if (!node)
        return nullptr;
    RBTNode<T> *current = node->right;
    while (current && current->left)
    {
        current = current->left;
    }
    return current;
}
template <class T>
RBTNode<T> *RBT<T>::determineNodeTobeDeleted(RBTNode<T> *node)
{
    if (!node->left && !node->right)
        return node;
    if (node->left && node->right)
    {
        RBTNode<T> *successorNode = successor(node);
        node->data = successorNode->data;
        return determineNodeTobeDeleted(successorNode);
    }
    if (node->left)
    {
        node->data = node->left->data;
        return determineNodeTobeDeleted(node->left);
    }
    else
    {
        node->data = node->right->data;
        return determineNodeTobeDeleted(node->right);
    }
}
template <class T>
void RBT<T>::remove(T element)
{
    RBTNode<T> *current = root;
    RBTNode<T> *toDelete = nullptr;

    while (current)
    {
        if (element < current->data)
        {
            current = current->left;
        }
        else if (element > current->data)
        {
            current = current->right;
        }
        else
        {
            toDelete = current;
            break;
        }
    }

    if (!toDelete)
    {
        std::cout << "Element not found." << std::endl;
        return;
    }
    RBTNode<T> *deletedNode = determineNodeTobeDeleted(toDelete);
    if (deletedNode->color == "Black")
        deletedNode->color = "DB";
    RBTNode<T> *root2 = root;
    deletionHandler(deletedNode);
    RBTNode<T> *root3 = root;
    bool ck = false;
    if (deletedNode->parent)
    {
        ck = true;
        if (deletedNode->parent->left == deletedNode)
            deletedNode->parent->left = nullptr;
        else
            deletedNode->parent->right = nullptr;
    }
    if (!ck)
    {
        delete root;
        root = nullptr;
    }
    else
    {
        delete deletedNode;
        deletedNode = nullptr;
    }
}
template <class T>
RBT<T>::~RBT()
{
    deleteTree(root);
}
template <class T>
void RBT<T>::deleteTree(RBTNode<T> *node)
{
    if (!node)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
template <class T>
void RBT<T>::search(T element)
{
    RBTNode<T> *current = root;
    while (current)
    {
        if (current->data > element)
        {
            current = current->left;
        }
        else if (current->data < element)
        {
            current = current->right;
        }
        else
        {
            break;
        }
    }
    if (current)
    {
        cout << "Element found." << endl;
    }
    else
    {
        cout << "Element not found." << endl;
    }
}

int main()
{
    // example from the Advanced data structure midterm
    RBT<int> redBlackTree;
    redBlackTree.insert(6);
    redBlackTree.insert(1);
    redBlackTree.insert(7);
    redBlackTree.insert(2);
    redBlackTree.insert(3);
    redBlackTree.insert(5);
    redBlackTree.insert(4);
    redBlackTree.remove(4);
    redBlackTree.remove(5);
    redBlackTree.remove(3);
    redBlackTree.remove(2);
    redBlackTree.remove(6);
    redBlackTree.remove(7);
    redBlackTree.remove(1);
    redBlackTree.print();
    cout << "#######################" << endl;
    // example from slides
    RBT<int> redBlackTree2;
    redBlackTree2.insert(7);
    redBlackTree2.insert(5);
    redBlackTree2.insert(9);
    redBlackTree2.insert(6);
    redBlackTree2.remove(6);
    redBlackTree2.insert(8);
    redBlackTree2.insert(12);
    redBlackTree2.insert(11);
    redBlackTree2.remove(10);
    redBlackTree2.remove(7);
    redBlackTree2.print();
    cout << "#######################" << endl;
    // // another example from Advanced data structures midterm
    RBT<int> redBlackTree3;
    redBlackTree3.insert(5);
    redBlackTree3.insert(1);
    redBlackTree3.insert(6);
    redBlackTree3.insert(2);
    redBlackTree3.insert(3);
    redBlackTree3.insert(4);
    redBlackTree3.remove(6);
    redBlackTree3.remove(3);
    redBlackTree3.remove(1);
    redBlackTree3.print();
    cout << "#######################" << endl;
    // // another example from Advanced data structures final
    RBT<int> redBlackTree4;
    redBlackTree4.insert(1);
    redBlackTree4.insert(6);
    redBlackTree4.insert(7);
    redBlackTree4.insert(8);
    redBlackTree4.insert(2);
    redBlackTree4.insert(0);
    redBlackTree4.insert(4);
    redBlackTree4.insert(3);
    redBlackTree4.insert(5);
    redBlackTree4.remove(8);
    redBlackTree4.remove(0);
    redBlackTree4.remove(1);
    redBlackTree4.print();
    cout << "#######################" << endl;
    // search check
    redBlackTree4.search(7);
    redBlackTree4.search(1);
    redBlackTree4.search(0);
    redBlackTree4.search(9);
}