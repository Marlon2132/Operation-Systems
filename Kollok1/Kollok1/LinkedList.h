#include <iostream>
#include <vector>

using namespace std;

class LinkedList {
public:
    struct Node {
        double long info;
        Node* next;
        Node(long double v = 0, Node* n = NULL) : info(v), next(n) {};
    };

    ~LinkedList();

    void print();

    void push_back(double long v);
    void clear();
    void recReverse(); // Large lists may cause the stack to overflow

    Node* getHead();

    vector<long double> toVector();

private:
    Node* head_ = NULL;

    Node* reverseRecursive(Node* head);
};