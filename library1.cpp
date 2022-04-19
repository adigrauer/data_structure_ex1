#include "library1.h"
#include "system.h"

void *Init(){
    System *DS = new System();
    return (void*)DS;
}

StatusType AddCompany(void *DS, int CompanyID, int Value){
    return ((System*)DS)->addCompany(CompanyID, Value);
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade){
    return ((System*)DS)->addEmployee(EmployeeID, CompanyID, Salary, Grade);
}

StatusType RemoveCompany(void *DS, int CompanyID){
    return ((System*)DS)->removeCompany(CompanyID);
}

StatusType RemoveEmployee(void *DS, int EmployeeID){
    return ((System*)DS)->removeEmployee(EmployeeID);
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees){
    return ((System*)DS)->getCompanyInfo(CompanyID, Value, NumEmployees);
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    return ((System*)DS)->getEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease){
    return ((System*)DS)->increaseCompanyValue(CompanyID, ValueIncrease);
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
    return ((System*)DS)->promoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){
    return ((System*)DS)->hireEmployee(EmployeeID, NewCompanyID);
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor){
    return ((System*)DS)->acquireCompany(AcquirerID, TargetID, Factor);
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID){
    return ((System*)DS)->getHighestEarner(CompanyID, EmployeeID);
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees){
    return ((System*)DS)->getAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees){
    return ((System*)DS)->getHighestEarnerInEachCompany(NumOfCompanies, Employees);
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){
    return ((System*)DS)->getNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId,
        MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);

}

void Quit(void** DS){
    ((System*)DS)->quit();
    delete (System*)DS;
}
