#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include "heap.h"
using namespace std;
class patient
{
private:
    string name;
    string phoneNo;
    string bloodType;
    int age;
    int priority;
    const static int Wcapcity=100;

public:
    static int id;
    static patient* arrP[Wcapcity];
    static node* arrPN[Wcapcity];
    patient(string n,string p,string b,int a,int pr){
        name=n;
        phoneNo=p;
        bloodType=b;
        age=a;
        priority=pr;
        arrP[id-1]=this;
        id++;
    };
    static patient* getPatient(int i);
    void setAge(int a);
    int getAge();
    void setName(string n);
    string getName();
    void setPhoneNo(string p);
    string getPhoneNo();
    void SetBloodType(string b);
    string GetBloodType();
    void SetPriority(int pr);
    int GetPriotiry();
};
#endif // PATIENT_H
