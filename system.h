#ifndef SYSTEM
#define SYSTEM

#include "library1.h"
#include "employeeByID.h"
#include "employeeBySalary.h"
#include "company.h"
#include "nonEmptyCompany.h"
#include "tree.h"
#include "treeNode.h"
#include <memory>

using std::shared_ptr;

template <class T> class Tree;
class Company;
class EmployeeByID;
class EmployeeBySalary;
class NonEmptyCompany;

class System{
        private:
                int id_highest_earner;
                int salary_of_highest_earner;
                int num_all_employees;
                shared_ptr<Tree<EmployeeByID>> all_employees_by_id_tree;
                shared_ptr<Tree<EmployeeBySalary>> all_employees_by_salary_tree;
                shared_ptr<Tree<Company>> all_companies;
                shared_ptr<Tree<NonEmptyCompany>> non_empty_companies;
        public:
        System(int id_highest_earner=0, int salary_of_highest_earner=0, int num_all_employees=0);
        System(const System& other) = default;
        ~System() = default;
        StatusType addCompany(int CompanyID, int Value);
        StatusType addEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);
        StatusType removeCompany(int CompanyID);
        StatusType removeEmployee(int EmployeeID);
        StatusType getCompanyInfo(int CompanyID, int *Value, int *NumEmployees);
        StatusType getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);
        /*StatusType increaseCompanyValue(int CompanyID, int ValueIncrease);
        */
        StatusType promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);
        //StatusType hireEmployee(int EmployeeID, int NewCompanyID);
        /*StatusType acquireCompany(int AcquirerID, int TargetID, double Factor);
        */StatusType getHighestEarner(int CompanyID, int *EmployeeID);
        StatusType getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);
        /*StatusType getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);
        StatusType getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
        void quit();
        */

        //helper functions
        void updateHighestEarner(shared_ptr<EmployeeBySalary> employee);
        shared_ptr<Tree<NonEmptyCompany>> getNonEmptyCompanyTree();
        shared_ptr<Tree<Company>> getAllCompaniesTree();
        shared_ptr<Tree<EmployeeBySalary>> getAllEmployeesBySalaryTree();
        shared_ptr<Tree<EmployeeByID>> getAllEmployeesByIdTree();
        void systemDestroy();
};

#endif  /* SYSTEM */

