#include "company.h"

Company::Company(int id, int value, int id_highest_earner, int salary_of_highest_earner, int num_employees):
    company_id(id),
    value(value)
{
}

int Company::getID()
{
    return this->company_id;
}

int Company::getValue()
{
    return this->value;
}

shared_ptr<NonEmptyCompany> Company::getNonEmptyCompany()
{
    return this->non_empty_company;
}

void Company::setValue(int new_value)
{
    value = new_value;
}

void Company::setNonEmptyCompany(shared_ptr<NonEmptyCompany> non_empty)
{
    non_empty_company = non_empty;
}

bool operator< (const Company& company_a, const Company& company_b)
{
    return company_a.company_id < company_b.company_id;
}

bool operator== (const Company& company_a, const Company& company_b)
{
    return company_a.company_id == company_b.company_id;
}

bool operator!= (const Company& company_a, const Company& company_b)
{
    return !(company_a == company_b);
}

bool operator<= (const Company& company_a, const Company& company_b)
{
    return !(company_b < company_a);
}

bool operator>= (const Company& company_a, const Company& company_b)
{
    return company_b <= company_a;
}

bool operator> (const Company& company_a, const Company& company_b)
{
    return company_b < company_a;
}