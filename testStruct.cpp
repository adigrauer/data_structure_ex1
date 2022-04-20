#include "employeeByID.h"
#include "employeeBySalary.h"
#include "company.h"
#include "system.h"
#include <iostream>
using std::cout;
using std::endl;

void testEmployeeById ();
//void testCompany ();
void testEmployeeBySalary ();
void testSystem ();

int main(){
    //testEmployeeById();
    //testCompany();
    //testEmployeeBySalary();
    testSystem ();
    return 0;
}

void testSystem (){
    System system;
    cout << endl;
    cout << "create system- done" << endl;
    cout << endl;
    system.addCompany(1,10);
    //shared_ptr<Tree<Company>> tree(system.getAllCompaniesTree());
    cout << endl;
    cout << "add company- done" << endl;
    cout << endl;
    system.addEmployee(5, 1, 5, 5);
    system.addEmployee(7, 2, 7, 7);
    cout << endl;
    cout << "add employee 5- done" << endl;
    cout << endl;
    system.addCompany(2,10);

    //test lottem added
    int value;
    int num_employees;
    system.getCompanyInfo(2, &value, &num_employees);
    if (value != 10 || num_employees != 0){
        return;
    }
    cout << "getCompanyInfo - done" << endl;
    cout << endl;

    system.promoteEmployee(5, 100, 10);
    //checked with debuger
    cout << "getPromoteEmployee - done" << endl;
    cout << endl;

    // lottem added until here

    system.systemDestroy();
    cout << endl;
}
/*
void testEmployeeById () {
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
    if (Lottem.getID() != 1){
        cout << "problem 5" << endl;
    }
    cout << "***test EmployeeByID completed***" << endl;
}
*/
void testEmployeeBySalary (){
    EmployeeBySalary adi(10, 1);
    EmployeeBySalary gili(13, 2);
    EmployeeBySalary einat(13, 3);
    cout << "adi id " << adi.getID() << endl;
    cout << "adi salary " << adi.getSalary() << endl;
    bool result = adi<gili;
    cout << "adi < gili result = " << result << "  need to be YES "<< endl;
    result = einat != gili;
    cout << "einat != gili result = " << result << "  need to be YES "<< endl;
    result = einat < gili;
    cout << "einat != gili result = " << result << "  need to be YES "<< endl;
    result = einat >= gili;
    cout << "einat >= gili result = " << result << "  need to be NOT "<< endl;
    result = gili > einat;
    cout << "gili > einat result = " << result << "  need to be YES "<< endl;
}

///////seperate the classes company and nonEmptyCompany therefore the tsts incorrect!!!!!
/*
void testCompany (){
    Company apple(1, 100);
    Company technion(2, 50);
    if (apple == technion) {
        cout << "problem 1" << endl;
    }
    if (technion<apple){
        cout << "problem 2" << endl;
    }
    apple.setHighestEarner(10);
    apple.setHighestSalary(10000);
    if(apple.getHighestEarner() != 10 || apple.getHighestSalary() != 10000)
    {
        cout << "problem 3" << endl;
    }
    technion.setValue(500);
    if(technion.getValue() != 500)
    {
        cout << "problem 4" << endl;
    }
    cout << "***test Company completed***" << endl;
}
*/