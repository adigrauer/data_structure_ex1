#ifndef EMPLOYEE_BY_ID_H
#define EMPLOYEE_BY_ID_H

#include "employeeBySalary.h"
#include "nonEmptyCompany.h"
#include <memory>

using std::shared_ptr;

class NonEmptyCompany;

class EmployeeByID{
    private:
        int id;
        int grade;
        shared_ptr<EmployeeBySalary> ptr_salary_employee;
        shared_ptr<NonEmptyCompany> ptr_my_company;

    public:
        EmployeeByID(int id, int grade);
        EmployeeByID(const EmployeeByID& employee) = default;
        ~EmployeeByID () = default;

        int getID();
        int getGrade();
        shared_ptr<EmployeeBySalary> getSalaryPtr();
        shared_ptr<NonEmptyCompany> getCompanyPtr();

        void setGrade();
        void setSalaryPtr(shared_ptr<EmployeeBySalary> new_ptr);
        void setCompanyPtr(shared_ptr<NonEmptyCompany> new_ptr);

        friend bool operator< (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
        friend bool operator== (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
};

bool operator!= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator<= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator>= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator> (const EmployeeByID& employee_a, const EmployeeByID& employee_b);

#endif /* EMPLOYEE_BY_ID_H */
