#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int value;
    Node *next = nullptr;
};

class LinkedList
{
public:
    Node *start;
    LinkedList() { start = nullptr; }
    void insert(int val)
    {
        Node *node = new Node;
        node->value = val;
        node->next = nullptr;
        Node *prev = start;
        if (start == nullptr || start->value > val)
        {
            node->value = val;
            node->next = start;
            start = node;
            return;
        }

        while (prev->next != nullptr && prev->next->value < val)
        {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
    }
    void erase(int val)
    {
        Node *prev = start;
        Node *temp = start->next;
        if (start == nullptr)
        {
            return;
        }
        if (prev->value == val)
        {
            start = prev->next;
            delete temp;
            return;
        }
        while (temp->value != val && temp != nullptr)
        {
            temp = temp->next;
            prev = prev->next;
        }
        prev->next = temp->next;
        if (temp != nullptr)
        {
            prev->next = temp->next;
        }
        delete temp;
    }

    void print()
    {
        Node *tempNode = start;
        while (tempNode != nullptr)
        {
            cout << tempNode->value << " ";
            tempNode = tempNode->next;
        }
    }
};

int main()
{

    LinkedList ls;
    ls.insert(10);
    ls.insert(8);
    ls.insert(9);
    ls.insert(5);
    ls.insert(3);
    ls.insert(1);
    ls.erase(1);
    ls.erase(5);
    ls.erase(10);
    ls.print();

    return 0;
}