#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "heap.h"
using namespace std;

class patient
{
private:
    string name;
    int age;
    int priority;

public:
    const static int Wcapcity = 100;  // Moved to public
    static int id;
    static patient* arrP[Wcapcity];
    static node* arrPN[Wcapcity];
    int myId;  // Instance variable to store this patient's ID

    patient(string n, int a, int pr){
        name = n;
        age = a;
        priority = pr;
        myId = id;  // Store the ID for this patient
        arrP[id-1] = this;
        id++;
    }

    static patient* getPatient(int i);
    void setAge(int a);
    int getAge();
    void setName(string n);
    string getName();
    void SetPriority(int pr);
    int GetPriotiry();
};
#endif // PATIENT_H
