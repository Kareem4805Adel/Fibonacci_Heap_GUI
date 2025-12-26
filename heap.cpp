#include "heap.h"
#include "linkedlist.cpp"
#include <iostream>

using namespace std;

node *FibonacciHeap::insert(node *newNode)
{
    rootlist->insertLast(newNode);

    if (min == nullptr || newNode->key < min->key) {
        min = newNode;
    }

    return newNode;
}

node *FibonacciHeap::findMin() const
{
    return min;
}

node *FibonacciHeap::extractMin()
{
    node *z = findMin();
    if (z != nullptr) {
        if (!z->children->isEmpty()) {
            int Children = z->children->size();
            CircularDoublyLinkedList<node *> childrenCopy(*z->children);
            Node<node *> *current = childrenCopy.head;
            for (int i = 0; i < Children; i++) {
                node *x = current->data;
                x->parent = nullptr;
                rootlist->insertLast(x);
                current = current->next;
            }
        }

        rootlist->deleteValue(z);

        if (rootlist->isEmpty()) {
            min = nullptr;
        } else {
            min = rootlist->head->data;
            Consolidate();
        }
    }
    return z;
}

void FibonacciHeap::decreaseKey(node *handle, int newKey)
{
    if (newKey > handle->key) {
        cout << "Error: new key is greater than current key" << endl;
        return;
    }

    handle->key = newKey;
    node *parent = handle->parent;

    if (parent != nullptr && handle->key < parent->key) {
        Cut(handle, parent);
        cascading_cut(parent);
    }

    if (min == nullptr || handle->key < min->key) {
        min = handle;
    }
}

void FibonacciHeap::deleteNode(node *handle)
{
    decreaseKey(handle, INT_MIN);
    extractMin();
}

void FibonacciHeap::Consolidate()
{
    const int MAX_DEGREE = 64;
    node *A[MAX_DEGREE];
    for (int i = 0; i < MAX_DEGREE; i++) {
        A[i] = nullptr;
    }

    int rootSize = rootlist->size();
    if (rootSize == 0)
        return;

    CircularDoublyLinkedList<node *> RootListCopy(*rootlist);
    Node<node *> *current = RootListCopy.head;

    for (int i = 0; i < rootSize; i++) {
        node *x = current->data;
        int d = x->degree;

        while (A[d] != nullptr) {
            node *y = A[d];
            if (x->key > y->key) {
                node *temp = x;
                x = y;
                y = temp;
            }
            Link(x, y);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        current = current->next;
    }

    min = nullptr;
    delete rootlist;
    rootlist = new CircularDoublyLinkedList<node *>();
    for (int i = 0; i < MAX_DEGREE; i++) {
        if (A[i] != nullptr) {
            rootlist->insertLast(A[i]);
            if (min == nullptr || A[i]->key < min->key) {
                min = A[i];
            }
        }
    }
}

void FibonacciHeap::Link(node *x, node *y)
{
    rootlist->deleteValue(y);
    x->children->insertLast(y);
    y->parent = x;
    x->degree++;
    y->mark = false;
}

void FibonacciHeap::Cut(node *x, node *y)
{
    y->children->deleteValue(x);
    y->degree--;
    insert(x);
    x->parent = nullptr;
    x->mark = false;
}

void FibonacciHeap::cascading_cut(node *y)
{
    node *z = y->parent;
    if (z != nullptr) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            Cut(y, z);
            cascading_cut(z);
        }
    }
}
