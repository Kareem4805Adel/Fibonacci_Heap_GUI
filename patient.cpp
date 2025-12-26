#include "patient.h"
#include "heap.h"
using namespace std;

int patient::id = 1;
patient *patient::arrP[patient::Wcapcity] = {nullptr};
node *patient::arrPN[patient::Wcapcity] = {nullptr};

patient *patient::getPatient(int i)
{
    if (id > 1 && i < id) {
        return arrP[i - 1];
    } else
        return nullptr;
}

void patient::setAge(int a)
{
    this->age = a;
}

int patient::getAge()
{
    return this->age;
}

void patient::setName(string n)
{
    this->name = n;
}

string patient::getName()
{
    return this->name;
}

void patient::SetPriority(int pr)
{
    this->priority = pr;
}

int patient::GetPriotiry()
{
    return this->priority;
}
