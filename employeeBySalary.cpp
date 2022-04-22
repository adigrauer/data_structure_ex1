#include "employeeBySalary.h"

EmployeeBySalary::EmployeeBySalary(int salary, int id) :
    salary(salary), id(id)
{
}

int EmployeeBySalary::getID() const{
    return this->id;
}

int EmployeeBySalary::getSalary() const{
    return this->salary;
}

void EmployeeBySalary::setSalary(int new_salary){
    this->salary = new_salary;
}

bool operator< (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    if(employee_a.salary == employee_b.salary){
        return employee_a.id > employee_b.id;
    }
    return employee_a.salary < employee_b.salary;
}

bool operator== (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    return employee_a.id == employee_b.id;
}

bool operator!= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    return !(employee_a == employee_b);
}

bool operator<= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    return !(employee_b < employee_a);
}

bool operator>= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    return employee_b <= employee_a;
}

bool operator> (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b){
    return employee_b < employee_a;
}