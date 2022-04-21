#include "employeeByID.h"
#include "employeeBySalary.h"
#include "company.h"
#include "system.h"
#include <iostream>
using std::cout;
using std::endl;

int main() 
{
    System system;
    system.addCompany(1,50);
    system.addCompany(2, 500);
    system.addCompany (3, 5000);
    system.addEmployee(11,1,60,70);
    system.addEmployee (12, 2, 600, 700);
    system.addEmployee (13, 3, 6000, 7000);
    system.acquireCompany (3, 2, 1.63);
    system.increaseCompanyValue (1, 100);
    system.promoteEmployee(13, 10, 1);
    //system.getHighestEarner (12);
    //system.getAllEmployeesBySalary (3);
    //GetHighestEarnerInEachCompany 2
    //GetNumEmployeesMatching -1 0 20 100 10
    system.hireEmployee (12, 1);
    //GetCompanyInfo 1
    //GetCompanyInfo 2
    //GetCompanyInfo 3
    //GetEmployeeInfo 11
    //GetEmployeeInfo 12
    //GetEmployeeInfo 13
    system.removeEmployee (13);
    system.removeCompany (3);
}