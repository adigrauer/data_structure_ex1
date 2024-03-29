#include "employeeByID.h"
#include "employeeBySalary.h"
#include "company.h"
#include "system.h"
#include <iostream>
using std::cout;
using std::endl;

/*
//heper function
void printBalance ();
void printBalance (){
    int balance = 0;
    all_employees_by_id_tree->inorderCheckHieght(all_employees_by_id_tree->getRoot() ,&balance);
    cout << "balance = " << balance << endl;
}
*/

void testEmployeeById ();
void testEmployeeBySalary ();
void testSystemAdi ();
void testSystemLottem ();
void newtest1();
void newtest2();

int main(){
    //testEmployeeById();
    //testCompany();
    //testEmployeeBySalary();
    //testSystemAdi ();
    //testSystemLottem ();
    newtest1();
    //newtest2();
    return 0;
}

void newtest2(){
    System system;
    system.addCompany(1,1);
    system.addCompany(2,2);
    system.addCompany(3,1);
}

void newtest1 (){
    System system;
    system.addCompany(1,1);
    system.addCompany(2,20);
    system.addCompany(3,1);
    system.addCompany(4,200);
    system.addCompany(5,1);
    system.addCompany(6,20);
    system.addCompany(7,1);
    system.addCompany(8,100);
    system.addEmployee(1, 1, 5, 5);
    system.addEmployee(2, 1, 5, 5);
    system.addEmployee(3, 1, 5, 5);
    system.addEmployee(4, 1, 5, 5);
    system.addEmployee(5, 2, 5, 5);
    system.addEmployee(6, 2, 1, 5);
    system.addEmployee(7, 2, 2, 5);
    system.addEmployee(8, 3, 3, 5);
    system.addEmployee(9, 3, 10, 5);
    system.addEmployee(10, 4, 100, 5);
    system.addEmployee(11, 5, 200, 5);
    system.hireEmployee(11, 6);
    system.promoteEmployee(11, 6, 0);
    system.removeEmployee(11);
    int heighst_earner;
    int* array2 = &heighst_earner;
    system.getHighestEarnerInEachCompany(3, &array2);
    if (array2[0] != 1 || array2[1] != 5 || array2[2] != 9)
    {
        free(array2);
        return;
    }
    free(array2);
    cout << "completeddd" <<endl;
    system.acquireCompany(8,1,2);
    cout << "acquired 8->1 done" <<endl;
    system.acquireCompany(2,7,1);
    cout << "acquired 2->7 done" <<endl;
}
void testSystemAdi (){
    System system;
    cout << endl;
    cout << "create system- done" << endl;
    cout << endl;
    system.addCompany(1,1);
    system.addCompany(2,20);
    system.addEmployee(5, 2, 5, 5);
    system.addEmployee(7, 1, 7, 7);
    system.acquireCompany(2,1,1);
    int company_id;
    int grade;
    int salary;
    int value;
    int num_employees;
    system.getEmployeeInfo(7, &company_id, &salary, &grade);
    system.getCompanyInfo(2, &value, &num_employees);
    cout << "get employee 7 info- done" << endl;
    cout << "company id = " << company_id << endl;
    cout << "grade = " << grade << endl;
    cout << "salary = " << salary << endl;
    system.systemDestroy();
    cout << "doneeeeeeeee!!!" << endl;
    cout << endl;
    
    //system.increaseCompanyValue(1, 10);
    //system.increaseCompanyValue(2, 20);
    //system.getEmployeeInfo(5, &company_id, &salary, &grade);
    cout << endl;

    /*cout << "get employee 5 info- done" << endl;
    cout << "company id = " << company_id << endl;
    cout << "grade = " << grade << endl;
    cout << "salary = " << salary << endl;
    cout << endl;
    cout << endl;
    
    cout << endl;
    system.removeEmployee(5);
    system.removeEmployee(7);
    cout << "remove 5,7 employees- done" << endl;
    system.systemDestroy();
    cout << endl;
    */
}

void testSystemLottem (){
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

    int heighst_earner;
    system.getHighestEarner(-1, &heighst_earner);
    if (heighst_earner != 5){
        return;
    }
    system.addEmployee(7, 2, 7, 7);
    system.getHighestEarner(2, &heighst_earner);
    if (heighst_earner != 7){
        return;
    }
    cout << "getheighestEarner - done" << endl;
    cout << endl;
    int x;
    int* array = &x;
    int employees;
    system.getAllEmployeesBySalary(-1, &array, &employees);
    if(array[0] != 5 || array[1] != 7)
    {
        free(array);
        return;
    }
    free(array);
    system.getAllEmployeesBySalary(2, &array, &employees);
    if(array[0] != 7)
    {
        free(array);
        return;
    }
    free(array);
    cout << "getAllEmployeesBySalary - done" << endl;
    cout << endl;

    //test gethighestearnerincompanies
    int y;
    int* array2 = &y;
    system.getHighestEarnerInEachCompany(2, &array2);
    if (array2[0] != 5 || array2[1] != 7)
    {
        free(array2);
        return;
    }
    free(array2);

    cout << "getHighestEarnerInEachCompany - done" << endl;
    cout << endl;
    
    int total;
    int total_above_salary;
    system.getNumEmployeesMatching(-1, 1, 10, 50, 0, &total, &total_above_salary);
    if (total != 2 || total_above_salary != 1)
    {
        return;
    }
    cout << "getNumEmployeesMatching - done" << endl;
    cout << endl;
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