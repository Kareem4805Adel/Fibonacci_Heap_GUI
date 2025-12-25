#ifndef HEAP_HPP
#define HEAP_HPP

#include "linkedlist.cpp"
#include <iostream>

using namespace std;
#include <string>
class node
{
public:
    int key, degree;
    string Taskname;
    bool mark; // to check if the node has lost a child since it became a child of another node
    node *left;
    node *right;
    node *parent;
    CircularDoublyLinkedList<node *> *children;
    // taskname not completed
    node(int val, string Tasknamepara)
        : key(val)
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
        , Taskname(Tasknamepara)
        , mark(false)
        , degree(0)
    {
        //pointing to itself
        right = this;
        left = this;
        children = new CircularDoublyLinkedList<node *>();
    }

    ~node() { delete children; }
};
class FibonacciHeap
{
    node *min;
    CircularDoublyLinkedList<node *> *rootlist;

public:
    FibonacciHeap()
        : min(NULL)
    {
        rootlist = new CircularDoublyLinkedList<node *>();
    }

    ~FibonacciHeap()
    {
        delete rootlist; // Changed from delete[]
    }

    node *insert(node *newNode);
    node *findMin() const;
    node *extractMin();
    void decreaseKey(node *handle, int newKey);
    void deleteNode(node *handle);

private:
    void Link(node *x, node *y);
    void Consolidate();
    void Cut(node *x, node *y);
    void cascading_cut(node *y);
};

#endif
