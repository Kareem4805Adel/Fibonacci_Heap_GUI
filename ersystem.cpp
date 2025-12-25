#include "ersystem.h"
#include "patient.h"

ERsystem::ERsystem(){}

node* ERsystem::AcceptPatiant(){
    return waitingList->extractMin();
}

node* ERsystem::AddToList(patient p){
    node* pa = new node(p.GetPriotiry(),p.getName());
    p.arrPN[p.id - 1] = pa;
    return waitingList->insert(pa);
}

node* ERsystem::getHighestPriority(){
    return waitingList->findMin();
}

void ERsystem::IncreasePriority(patient p, int priority){
    waitingList->decreaseKey(p.arrPN[p.id-1], priority);
}

void ERsystem::RemoveFromList(patient p){
    waitingList->deleteNode(p.arrPN[p.id-1]);
}
