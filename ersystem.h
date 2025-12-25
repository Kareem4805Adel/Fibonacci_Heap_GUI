#ifndef ERSYSTEM_H
#define ERSYSTEM_H

#include "heap.h"
#include "patient.h"

class ERsystem
{
public:
    ERsystem();
    node* AddToList(patient p);
    void RemoveFromList(patient p);
    node* AcceptPatiant();
    void IncreasePriority(patient p, int priority);
    node* getHighestPriority();


private:
    FibonacciHeap *waitingList = new FibonacciHeap();
};

#endif // ERSYSTEM_H
