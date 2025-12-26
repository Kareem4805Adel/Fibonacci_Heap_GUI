#include "ersystem.h"
#include "patient.h"

ERsystem::ERsystem(){
    waitingList = new FibonacciHeap();
}

ERsystem::~ERsystem(){
    delete waitingList;
}

node* ERsystem::AcceptPatiant(){
    return waitingList->extractMin();
}

node* ERsystem::AddToList(patient& p){
    int index = p.myId - 1;  // Use the patient's stored ID
    node* pa = new node(p.GetPriotiry(), p.getName());
    patient::arrPN[index] = pa;  // Store in the static array
    return waitingList->insert(pa);
}

node* ERsystem::getHighestPriority(){
    return waitingList->findMin();
}

void ERsystem::IncreasePriority(patient& p, int priority){
    int index = p.myId - 1;
    if (patient::arrPN[index] != nullptr) {
        waitingList->decreaseKey(patient::arrPN[index], priority);
    }
}

void ERsystem::RemoveFromList(patient& p){
    int index = p.myId - 1;
    if (patient::arrPN[index] != nullptr) {
        waitingList->deleteNode(patient::arrPN[index]);
    }
}
