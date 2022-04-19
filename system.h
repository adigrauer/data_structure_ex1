#ifndef SYSTEM
#define SYSTEM

#include "main1.cpp"
#include "EmployeeByID.cpp"
#include "tree.h"
#include "treeNode.h"

class System{
        private:
                int id_highest_earner;
                int salary_of_highest_earner;
                int num_all_employees;
                shared_ptr<Tree<EmployeeByID>> All_employees_by_id_tree;
                shared_ptr<Tree<EmployeeBySalary>> all_employeesB_byS_salaryT_tree;
        public:
};


void *Init();

StatusType AddCompany(void *DS, int CompanyID, int Value);

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade);

StatusType RemoveCompany(void *DS, int CompanyID);

StatusType RemoveEmployee(void *DS, int EmployeeID);

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees);

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade);

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease);

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade);

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID);

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor);

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID);

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees);

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

void Quit(void** DS);




#endif    /* SYSTEM */

