#include "LinkedList.h"

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::print() {
    if (NULL == head_) {
        throw logic_error("[VecClass::print] -> list is empty!");
    }
    else {
        cout << endl << "Your list" << endl
            << "======================" << endl;

        for (Node* p = head_; p; p = p->next) {
            cout << p->info;
            if (p->next) {
                cout << " -> ";
            }
        }
        cout << endl;

    }
}

void LinkedList::push_back(double long v) {
    Node* node = new Node(v);

    if (!node) {
        throw std::runtime_error("[LinkedList::push_back] -> allocation failed");
    }
    else {
        if (!head_) {
            head_ = node;

            return;
        }

        Node* curr = head_;

        while (curr->next) {
            curr = curr->next;
        }

        curr->next = node;
    }
}

void LinkedList::clear() {
    Node* curr = head_;

    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }

    head_ = NULL;
}

void LinkedList::recReverse() {
    head_ = reverseRecursive(head_);
}

LinkedList::Node* LinkedList::getHead() {
    return head_;
}

vector<long double> LinkedList::toVector() {
    vector<long double> out;

    for (Node* p = head_; p; p = p->next) {
        out.push_back(p->info);
    }

    return out;
}

LinkedList::Node* LinkedList::reverseRecursive(Node* head) {
    if (head == NULL or head->next == NULL) {
        return head;
    }
    else {
        Node* newHead = reverseRecursive(head->next);

        head->next->next = head;

        head->next = NULL;

        return newHead;
    }
}
