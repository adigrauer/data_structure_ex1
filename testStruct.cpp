#include "EmployeeByID.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    EmployeeByID Lottem(1);
    EmployeeByID Adi(2);
    EmployeeByID Arava(1);
    if (Adi == Lottem) {
        cout << "problem 1" << endl;
    }
    if (Adi<Lottem){
        cout << "problem 2" << endl;
    }
    if(Arava != Lottem){
        cout << "problem 3" << endl;
    }
    if (Lottem>Adi) {
        cout << "problem 4" << endl;
    }
    cout << "Lottem id" << Lottem.getID() << endl;
    cout << "Adi id" << Adi.getID() << endl;
    return 0;
}