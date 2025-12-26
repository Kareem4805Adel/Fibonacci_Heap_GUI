#ifndef PATIENT_H
#define PATIENT_H
#include "heap.h"
#include <string>
using namespace std;

class patient
{
private:
    string name;
    int age;
    int priority;

public:
    const static int Wcapcity = 100;
    static int id;
    static patient *arrP[Wcapcity];
    static node *arrPN[Wcapcity];
    int myId;

    patient(string n, int a, int pr)
    {
        name = n;
        age = a;
        priority = pr;
        myId = id;
        arrP[id - 1] = this;
        id++;
    }

    static patient *getPatient(int i);
    void setAge(int a);
    int getAge();
    void setName(string n);
    string getName();
    void SetPriority(int pr);
    int GetPriotiry();
};
#endif
