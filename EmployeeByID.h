#ifndef EMPLOYEE_BY_ID_H
#define EMPLOYEE_BY_ID_H

#include "EmployeeBySalary.h"
#include "Company.h"
#include <memory>

using std::shared_ptr;

class EmployeeByID{
    private:
        int ID;
        shared_ptr<EmployeeBySalary> ptr_salary_employee;
        shared_ptr<Company> ptr_my_company;

    public:
        EmployeeByID(int id);
        EmployeeByID(const EmployeeByID& employee) = default;
        ~EmployeeByID () = default;

        int getID();
        shared_ptr<EmployeeBySalary> getSalaryPtr();
        shared_ptr<Company> getCompanyPtr();

        void setSalaryPtr(shared_ptr<EmployeeBySalary> new_ptr);
        void setCompanyPtr(shared_ptr<Company> new_ptr);

        friend bool operator< (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
        friend bool operator== (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
};

bool operator!= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator<= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator>= (const EmployeeByID& employee_a, const EmployeeByID& employee_b);
bool operator> (const EmployeeByID& employee_a, const EmployeeByID& employee_b);

#endif /*EMPLOYEE_BY_ID_H*/