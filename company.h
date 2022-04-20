#ifndef COMPANY_H
#define COMPANY_H

#include "employeeBySalary.h"
#include "employeeByID.h"
#include "nonEmptyCompany.h"
#include "tree.h"
#include "treeNode.h"
#include <memory>

using std::shared_ptr;

class EmployeeByID;

class Company{
    private:
        int company_id;
        int value;
        shared_ptr<NonEmptyCompany> non_empty_company;
    public:
        /* Company C'tor */
        Company(int id, int value);
        
        /* Company copy C'tor */
        Company(const Company& company) = default;
        
        /* Company D'tor */
        ~Company () = default;

        int getID();
        int getValue();
        shared_ptr<NonEmptyCompany> getNonEmptyCompany();

        void setValue(int to_add);
        void setNonEmptyCompany(shared_ptr<NonEmptyCompany> non_empty);
        
        friend bool operator< (const Company& company_a, const Company& company_b);
        friend bool operator== (const Company& company_a, const Company& company_b);
};

bool operator!= (const Company& company_a, const Company& company_b);
bool operator<= (const Company& company_a, const Company& company_b);
bool operator>= (const Company& company_a, const Company& company_b);
bool operator> (const Company& company_a, const Company& company_b);

#endif /*COMPANY_H*/