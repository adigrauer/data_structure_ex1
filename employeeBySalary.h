#ifndef EMPLOYEE_BY_SALARY_H
#define EMPLOYEE_BY_SALARY_H

#include <memory>

using std::shared_ptr;

class EmployeeBySalary {
    private:
        int salary;
        int id;
    public:
        EmployeeBySalary(int salary, int id);
        EmployeeBySalary(const EmployeeBySalary& other) = default;
        ~EmployeeBySalary() = default;

        int getID() const;
        int getSalary() const;

        void setSalary(int new_salary);

        friend bool operator< (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);
        friend bool operator== (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);
};

bool operator!= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);
bool operator<= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);
bool operator>= (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);
bool operator> (const EmployeeBySalary& employee_a, const EmployeeBySalary& employee_b);

#endif /* EMPLOYEE_BY_ID_H */