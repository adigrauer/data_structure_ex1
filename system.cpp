#include "system.h"

////////////////////////////////////////////
System::System(int id_highest_earner, int salary_of_highest_earner, int num_all_employees) :
    id_highest_earner(id_highest_earner),
    salary_of_highest_earner(salary_of_highest_earner),
    num_all_employees( num_all_employees),
    all_employees_by_id_tree(new Tree<EmployeeByID>),
    all_employees_by_salary_tree(new Tree<EmployeeBySalary>),
    all_companies(new Tree<Company>),
    non_empty_companies(new Tree<NonEmptyCompany>)
{
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::addCompany(int CompanyID, int Value){
    //invalid arguments
    if(this == nullptr || CompanyID <= 0 || Value <= 0){
        return INVALID_INPUT;
    }
    //company alreadt exist
    shared_ptr<Company> company_to_add(new Company(CompanyID, Value));
    shared_ptr<TreeNode<Company>> company_to_find(all_companies->find(company_to_add));
    if(company_to_find != nullptr){
        return FAILURE;
    }
    //add company to all companies treet
    all_companies->insert(company_to_add);
    return SUCCESS;
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::addEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    //invalid arguments
    if(this == nullptr || EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0){
        return INVALID_INPUT;
    }
    //company not exist in allCompanyTree || employee already exist
    shared_ptr<Company> company_to_find(new Company(CompanyID, 0)); 
    shared_ptr<EmployeeByID> employee_id_to_add(new EmployeeByID(EmployeeID)); 
    shared_ptr<TreeNode<Company>> all_company_node(all_companies->find(company_to_find));
    shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_add));
    if(all_company_node == nullptr || all_employee_id_node != nullptr){
        return FAILURE;
    }

    //cheack if the company is empty- need to add to nonEmptyCompanyTree
    if(all_company_node->getData()->getNonEmptyCompany() == nullptr){
        shared_ptr<NonEmptyCompany> non_empty_company_to_add(new NonEmptyCompany(CompanyID, all_company_node->getData()->getNonEmptyCompany()->getValue())); 
        non_empty_companies->insert(non_empty_company_to_add);
        all_company_node->getData()->setNonEmptyCompany(non_empty_company_to_add);
    }

    //add employee to all employees by id,salary and company employees by id,salary
    //add employee to all employee by id
    all_employees_by_id_tree->insert(employee_id_to_add);
    employee_id_to_add->setCompanyPtr(is_company_find->getData());
    //add to all employee by salary
    shared_ptr<EmployeeBySalary> employee_salary_to_add(new EmployeeBySalary(Salary,EmployeeID)); 
    all_employees_by_salary_tree->insert(employee_salary_to_add);
    employee_id_to_add->setSalaryPtr(employee_salary_to_add);
    
    return SUCCESS;
}
////////////////////////////////////////////

/*
StatusType System::removeCompany(int CompanyID){

}

StatusType System::removeEmployee(int EmployeeID){

}

StatusType System::getCompanyInfo(int CompanyID, int *Value, int *NumEmployees){

}

StatusType System::getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade){

}

StatusType System::increaseCompanyValue(int CompanyID, int ValueIncrease){

}

StatusType System::promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade){

}

StatusType System::hireEmployee(int EmployeeID, int NewCompanyID){

}

StatusType System::acquireCompany(int AcquirerID, int TargetID, double Factor){

}

StatusType System::getHighestEarner(int CompanyID, int *EmployeeID){

}

StatusType System::getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees){

}

StatusType System::getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees){

}

StatusType System::getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){

}

void System::quit(){

}
*/