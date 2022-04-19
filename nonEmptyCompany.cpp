#include "nonEmptyCompany.h"

NonEmptyCompany::NonEmptyCompany(int id, int value, int id_highest_earner, int salary_of_highest_earner, int num_employees):
    company_id(id),
    value(value),
    id_highest_earner(id_highest_earner),
    salary_of_highest_earner(salary_of_highest_earner),
    num_employees(num_employees),
    employees_by_id(new Tree<EmployeeByID>),
    employees_by_salary(new Tree<EmployeeBySalary>)
{
}

int NonEmptyCompany::getID()
{
    return this->company_id;
}
int NonEmptyCompany::getHighestEarner()
{
    return this->id_highest_earner;
}

int NonEmptyCompany::getHighestSalary()
{
    return this->salary_of_highest_earner;
}

int NonEmptyCompany::getValue()
{
    return this->value;
}

int NonEmptyCompany::getNumEmployees()
{
    return this->num_employees;
}


shared_ptr<Tree<EmployeeBySalary>> NonEmptyCompany::getEmployeesBySalaryTree()
{
    return this->employees_by_salary;
}

shared_ptr<Tree<EmployeeByID>> NonEmptyCompany::getEmployeesByIDTree()
{
    return this->employees_by_id;
}

void NonEmptyCompany::setHighestEarner(int new_id)
{
    id_highest_earner = new_id;
}

void NonEmptyCompany::setHighestSalary(int new_salary)
{
    salary_of_highest_earner = new_salary;
}

void NonEmptyCompany::setValue(int new_value)
{
    value = new_value;
}

void NonEmptyCompany::setNumEmployees(int new_num_employees)
{
   num_employees = new_num_employees;
}


void NonEmptyCompany::setEmployeesBySalaryTree(shared_ptr<Tree<EmployeeBySalary>> salary_tree)
{
    employees_by_salary = salary_tree;
}

void NonEmptyCompany::setEmployeesByIDTree(shared_ptr<Tree<EmployeeByID>> id_tree)
{
    employees_by_id = id_tree;
}

bool operator< (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return company_a.company_id < company_b.company_id;
}

bool operator== (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return company_a.company_id == company_b.company_id;
}

bool operator!= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return !(company_a == company_b);
}

bool operator<= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return !(company_b < company_a);
}

bool operator>= (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return company_b <= company_a;
}

bool operator> (const NonEmptyCompany& company_a, const NonEmptyCompany& company_b)
{
    return company_b < company_a;
}