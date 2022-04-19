#include "EmployeeByID.h"

EmployeeByID::EmployeeByID (int id):
    ID(id),
    ptr_salary_employee(nullptr),
    ptr_my_company(nullptr)
{
}

int EmployeeByID::getID()
{
    return this->ID;
}

shared_ptr<EmployeeBySalary> EmployeeByID::getSalaryPtr()
{
    return this->ptr_salary_employee;
}

shared_ptr<Company> EmployeeByID::getCompanyPtr()
{
    return this->ptr_my_company;
}

void EmployeeByID::setSalaryPtr(shared_ptr<EmployeeBySalary> new_ptr)
{
    ptr_salary_employee = new_ptr;
    return;
}

void EmployeeByID::setCompanyPtr(shared_ptr<Company> new_ptr)
{
    ptr_my_company = new_ptr;
    return;
}

bool operator< (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_a.ID < employee_b.ID;
}

bool operator== (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_a.ID == employee_b.ID;
}

bool operator!= (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return !(employee_a == employee_b);
}

bool operator<= (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return !(employee_b < employee_a);
}

bool operator>= (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_b <= employee_a;
}

bool operator> (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_b < employee_a;
}
