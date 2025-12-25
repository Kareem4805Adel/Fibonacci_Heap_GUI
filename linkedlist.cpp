#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
using namespace std;

template<typename t>
class Node
{
public:
    t data;
    Node<t> *next;
    Node<t> *prev;

    Node(t value)
    {
        data = value;
        next = this;
        prev = this;
    }
};

template<typename t>
class CircularDoublyLinkedList
{
private:
public:
    Node<t> *head;
    CircularDoublyLinkedList() { head = nullptr; }

    CircularDoublyLinkedList(const CircularDoublyLinkedList<t> &other)
    {
        head = nullptr;

        if (other.head == nullptr)
            return;

        Node<t> *current = other.head;

        do {
            insertLast(current->data);
            current = current->next;
        } while (current != other.head);
    }

    bool isEmpty() { return head == nullptr; }

    void insertFirst(t value)
    {
        Node<t> *newNode = new Node<t>(value);

        if (isEmpty()) {
            head = newNode;
        } else {
            Node<t> *tail = head->prev;

            newNode->next = head;
            newNode->prev = tail;

            tail->next = newNode;
            head->prev = newNode;

            head = newNode;
        }
    }

    void insertLast(t value)
    {
        if (isEmpty()) {
            insertFirst(value);
            return;
        }

        Node<t> *newNode = new Node<t>(value);
        Node<t> *tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;
    }

    void deleteValue(t value)
    {
        if (isEmpty()) {
            cout << "List is empty.";
            return;
        }

        Node<t> *current = head;

        do {
            if (current->data == value) {
                if (current->next == current) {
                    delete current;
                    head = nullptr;
                    return;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;

                if (current == head) {
                    head = current->next;
                }

                delete current;
                return;
            }
            current = current->next;
        } while (current != head);
    }

    int size()
    {
        if (isEmpty())
            return 0;

        int count = 0;
        Node<t> *temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);

        return count;
    }

    void insertAtIndex(int index, t value)
    {
        int n = size();

        if (index < 0 || index > n) {
            cout << "Invalid index" << endl;
            return;
        }

        Node<t> *newNode = new Node<t>(value);

        if (isEmpty()) {
            head = newNode;
            return;
        }

        if (index == 0) {
            Node<t> *tail = head->prev;

            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;

            head = newNode;
            return;
        }

        Node<t> *current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }

    void deleteAtIndex(int index)
    {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        int n = size();

        if (index < 0 || index >= n) {
            cout << "Invalid index" << endl;
            return;
        }

        Node<t> *current = head;

        if (n == 1) {
            delete head;
            head = nullptr;
            return;
        }

        if (index == 0) {
            Node<t> *tail = head->prev;
            Node<t> *toDelete = head;

            head = head->next;

            tail->next = head;
            head->prev = tail;

            delete toDelete;
            return;
        }

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
    }

    // Display Forward
    /*void displayForward() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << " <-> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(HEAD)\n";
    }

    // Display backward
    void displayBackward() {
        if (isEmpty()) {
            cout << "List is empty\n";
            return;
        }

        Node* temp = head->prev;
        Node* tail = temp;

        do {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        } while (temp != tail);

        cout << "(TAIL)\n";
    }*/
};

#endif
