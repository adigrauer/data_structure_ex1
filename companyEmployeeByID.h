#ifndef COMPANY_EMPLOYEE_BY_ID_H
#define COMPANY_EMPLOYEE_BY_ID_H

class CompanyEmployeeByID{
    private:
        int id;
        int salary;
    public:
        CompanyEmployeeByID(int salary, int id);
        CompanyEmployeeByID(const CompanyEmployeeByID& other) = default;
        ~CompanyEmployeeByID() = default;

        int getID() const;
        int getSalary() const;

        void setSalary(int new_salary);

        friend bool operator< (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);
        friend bool operator== (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);
};

bool operator!= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);
bool operator<= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);
bool operator>= (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);
bool operator> (const CompanyEmployeeByID& employee_a, const CompanyEmployeeByID& employee_b);

#endif /* COMPANY_EMPLOYEE_BY_ID_H */