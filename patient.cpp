#include "patient.h"
using namespace std;
int patient :: id=1;
patient* patient :: arrP[Wcapcity]={nullptr};
patient* patient::getPatient(int i) {
    if(id>1&& i<id){
        return arrP[i-1];
    }
    else
        return nullptr;
}
void patient :: setAge(int a){
    this->age=a;
}
int  patient :: getAge(){
    return this->age;
}
void patient :: setName(string n){
    this->name=n;
}
string patient :: getName(){
    return this->name;
}
void patient :: setPhoneNo(string p){
    this->phoneNo=p;
}
string patient :: getPhoneNo(){
    return this->phoneNo;
}
void patient :: SetBloodType(string b){
    this->bloodType=b;
}
string patient::GetBloodType(){
    return this->bloodType;
}
void patient :: SetPriority(int pr){
    this->priority=pr;
}
int patient :: GetPriotiry(){
    return this->priority;
}
