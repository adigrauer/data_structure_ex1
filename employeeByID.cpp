#include "employeeByID.h"

EmployeeByID::EmployeeByID (int id, int grade):
    id(id),
    grade(grade)
{
}

int EmployeeByID::getID()
{
    return this->id;
}

int EmployeeByID::getGrade()
{
    return this->grade;
}

shared_ptr<EmployeeBySalary> EmployeeByID::getSalaryPtr()
{
    return this->ptr_salary_employee;
}

shared_ptr<NonEmptyCompany> EmployeeByID::getCompanyPtr()
{
    return this->ptr_my_company;
}

void EmployeeByID::setGrade()
{
    grade++;
    return;
}
void EmployeeByID::setSalaryPtr(shared_ptr<EmployeeBySalary> new_ptr)
{
    ptr_salary_employee = new_ptr;
    return;
}

void EmployeeByID::setCompanyPtr(shared_ptr<NonEmptyCompany> new_ptr)
{
    ptr_my_company = new_ptr;
    return;
}

bool operator< (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_a.id < employee_b.id;
}

bool operator== (const EmployeeByID& employee_a, const EmployeeByID& employee_b)
{
    return employee_a.id == employee_b.id;
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
