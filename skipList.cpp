#include <bits/stdc++.h>

using namespace std;

struct PairCompare
{
    bool operator()(const pair<int, string> &a, const pair<int, string> &b) const
    {
        if (a.first != b.first)
            return a.first > b.first;
        return a.second < b.second;
    }
};

ostream &operator<<(ostream &os, const pair<int, string> &p)
{
    os << "{" << p.first << ", " << p.second << "}";
    return os;
}

template <typename T>
struct Node
{
    T value;
    Node *next;
    Node *under;

    Node(T val) : value(val), next(nullptr), under(nullptr)
    {
    }
};

template <typename T, typename Compare = less<T>>
class SkipList
{
public:
    Node<T> *start;
    int maxLevel;
    Compare comp;
    mt19937 rng;

    SkipList(int maxLevel) : maxLevel(maxLevel), rng(random_device{}())
    {
        start = new Node<T>(T{});
        Node<T> *current = start;
        for (int i = 1; i < maxLevel; i++)
        {
            Node<T> *newLevel = new Node<T>(T{});
            current->under = newLevel;
            current = newLevel;
        }
    }

    ~SkipList()
    {
        while (start)
        {
            Node<T> *current = start;
            while (current)
            {
                Node<T> *temp = current;
                current = current->next;
                delete temp;
            }
            start = start->under;
        }
    }

    bool search(T val)
    {
        Node<T> *node = start;
        while (node)
        {
            while (node->next && comp(node->next->value, val))
            {
                node = node->next;
            }
            if (node->next && node->next->value == val)
            {
                return true;
            }
            node = node->under;
        }
        return false;
    }

    void insert(T val)
    {
        vector<Node<T> *> prevNodeInLevel(maxLevel);
        Node<T> *node = start;

        for (int i = maxLevel - 1; i >= 0; i--)
        {
            while (node->next != nullptr && comp(node->next->value, val))
            {
                node = node->next;
            }
            prevNodeInLevel[i] = node;
            if (node->under != nullptr)
            {
                node = node->under;
            }
        }

        uniform_int_distribution<> dist(0, 1);
        int levelsProbability = 1;
        while (dist(rng) == 0 && levelsProbability < maxLevel)
        {
            levelsProbability++;
        }

        Node<T> *newNode = nullptr;
        for (int i = 0; i < levelsProbability; i++)
        {
            newNode = new Node<T>(val);
            newNode->next = prevNodeInLevel[i]->next;
            prevNodeInLevel[i]->next = newNode;

            if (i > 0)
            {
                newNode->under = prevNodeInLevel[i - 1]->next;
            }
        }
    }

    void printList()
    {
        Node<T> *level = start;
        int levelNum = maxLevel;
        while (level)
        {
            cout << "Level " << levelNum-- << ": ";
            Node<T> *current = level;
            while (current)
            {
                if (!(current->value == T{}))
                {
                    cout << current->value << " ";
                }
                current = current->next;
            }
            cout << endl;
            level = level->under;
        }
    }

    void deleteNode(T val)
    {
        vector<Node<T> *> prevNodeInLevel(maxLevel);
        Node<T> *current = start;
        for (int i = maxLevel - 1; i >= 0; i--)
        {
            while (current->next != nullptr && comp(current->next->value, val))
            {
                current = current->next;
            }

            prevNodeInLevel[i] = current;

            if (current->under != nullptr)
            {
                current = current->under;
            }
        }
        current = start;
        for (int i = maxLevel - 1; i >= 0; i--)
        {
            while (current->next != nullptr && comp(current->next->value, val))
            {
                current = current->next;
            }

            if (current->next != nullptr && current->next->value == val)
            {
                Node<T> *nodeToDelete = current->next;
                current->next = nodeToDelete->next;

                delete nodeToDelete;
            }

            if (current->under != nullptr)
            {
                current = current->under;
            }
        }
    }
};

class Game : public SkipList<pair<int, string>, PairCompare>
{
    unordered_map<string, int> prevScore;

public:
    Game(int maxLevel) : SkipList(maxLevel)
    {
    }

    void addPlayer(const string &name, int score)
    {
        if (prevScore.count(name))
        {
            int oldScore = prevScore[name];
            deleteNode({oldScore, name});
        }

        insert({score, name});
        prevScore[name] = score;
    }

    void updatePlayerScore(const string &name, int newScore)
    {
        if (prevScore.count(name) == 0)
        {
            addPlayer(name, newScore);
            return;
        }

        int oldScore = prevScore[name];
        if (oldScore == newScore)
        {
            return;
        }

        deleteNode({oldScore, name});
        insert({newScore, name});
        prevScore[name] = newScore;
    }

    void deletePlayer(const string &name)
    {
        if (prevScore.count(name) == 0)
            return;

        int score = prevScore[name];
        deleteNode({score, name});
        prevScore.erase(name);
    }

    int getPlayerScore(const string &name)
    {
        auto it = prevScore.find(name);
        return (it != prevScore.end()) ? it->second : -1;
    }

    void printTopN(int n)
    {
        queue<pair<int, string>> topNPlayres;
        Node<pair<int, string>> *current = start;
        while (current->under != nullptr)
        {
            current = current->under;
        }

        current = current->next;
        while (current != nullptr)
        {
            topNPlayres.push(current->value);
            current = current->next;
        }

        cout << "Top " << min(n, (int)topNPlayres.size()) << " topNPlayres:\n";
        for (int i = 0; i < n && !topNPlayres.empty(); i++)
        {
            cout << topNPlayres.front().second << ": " << topNPlayres.front().first << "\n";
            topNPlayres.pop();
        }
    }
};

int main()
{
    SkipList<int> skiplist(5);
    skiplist.insert(15);
    skiplist.insert(1);
    skiplist.insert(9);
    skiplist.insert(21);
    skiplist.insert(12);
    skiplist.insert(3);
    skiplist.insert(70);
    skiplist.insert(23);
    cout << "First List: \n";
    skiplist.printList();
    cout << "===================================================\n";
    skiplist.deleteNode(1);
    cout << "after deleting 1: \n";
    skiplist.printList();
    cout << "===================================================\n";

    cout << "check if 21 is in the skip list: \n";
    if (skiplist.search(21))
        cout << "found\n";
    else
        cout << "not found\n";
    cout << "===================================================\n";

    cout << "check if 1 is in the skip list: \n";
    if (skiplist.search(1))
        cout << "found\n";
    else
        cout << "not found\n";

    Game game(4);

    game.addPlayer("Alice", 100);
    game.addPlayer("Bob", 200);
    game.addPlayer("David", 1);
    game.addPlayer("Alison", 300);
    cout << "current players list: \n";
    game.printList();
    cout << "===================================================\n";

    game.deletePlayer("Bob");
    cout << "the list after deleting Bob \n";
    game.printList();
    cout << "===================================================\n";

    game.updatePlayerScore("David", 100);
    cout << "the list after updating David to 100 \n";
    game.printList();
    cout << "===================================================\n";

    game.printTopN(3);
    cout << '\n';
    cout << game.getPlayerScore("David");

    return 0;
}
