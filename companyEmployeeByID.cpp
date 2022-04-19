#include "companyEmployeeByID.h"

CompanyEmployeeByID::CompanyEmployeeByID(int salary, int id) :
    id(id), salary(salary)
{
}

int CompanyEmployeeByID::getID() const{
    return this->id;
}

int CompanyEmployeeByID::getSalary() const{
    return this->salary;
}

void CompanyEmployeeByID::setSalary(int new_salary){
    this->salary = new_salary;
}

bool operator< (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return employee_a.id < employee_b.id;
}

bool operator== (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return (employee_a.id == employee_b.id);
}

bool operator!= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return !(employee_a == employee_b);
}

bool operator<= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return !(employee_b < employee_a);
}

bool operator>= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return employee_b <= employee_a;
}

bool operator> (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b){
    return employee_b < employee_a;
}