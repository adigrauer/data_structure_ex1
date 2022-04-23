#ifndef NON_EMPTY_COMPANY
#define NON_EMPTY_COMPANY

#include "employeeBySalary.h"
#include "employeeByID.h"
#include "tree.h"
#include "treeNode.h"
#include <memory>

using std::shared_ptr;

class EmployeeByID;

class NonEmptyCompany{
    private:
        int company_id;
        int id_highest_earner;
        int salary_of_highest_earner;
        int num_employees;
        shared_ptr<Tree<EmployeeByID>> employees_by_id;
        shared_ptr<Tree<EmployeeBySalary>> employees_by_salary;
    public:
        NonEmptyCompany(int id, int value, int id_highest_earner=0, int salary_of_highest_earner=0, int num_employees=0);
        NonEmptyCompany(const NonEmptyCompany& company) = default;
        ~NonEmptyCompany () = default;

        int getID();
        int getHighestEarner();
        int getHighestSalary();
        int getNumEmployees();
        shared_ptr<Tree<EmployeeBySalary>> getEmployeesBySalaryTree();
        shared_ptr<Tree<EmployeeByID>> getEmployeesByIDTree();

        void setHighestEarner(int new_id);
        void setHighestSalary(int new_salary);
        void setNumEmployees(int to_change);
        void setEmployeesBySalaryTree(shared_ptr<Tree<EmployeeBySalary>> salary_tree);
        void setEmployeesByIDTree(shared_ptr<Tree<EmployeeByID>> id_tree);

        void updateHighestEarner(shared_ptr<EmployeeBySalary> employee);
        void changeHighestEarnerBeforeRemove(shared_ptr<EmployeeBySalary> employee);

        friend bool operator< (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);
        friend bool operator== (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);
};

bool operator!= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);
bool operator<= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);
bool operator>= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);
bool operator> (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b);

#endif    /* NON_EMPTY_COMPANY */