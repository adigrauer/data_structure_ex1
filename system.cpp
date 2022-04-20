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
    shared_ptr<EmployeeByID> employee_id_to_add(new EmployeeByID(EmployeeID, Grade)); 
    shared_ptr<TreeNode<Company>> all_company_node(all_companies->find(company_to_find));
    shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_add));
    if(all_company_node == nullptr || all_employee_id_node != nullptr){
        return FAILURE;
    }

    //cheack if the company is empty- need to add to nonEmptyCompanyTree
    shared_ptr<NonEmptyCompany> non_empty_company_to_add(new NonEmptyCompany(CompanyID, all_company_node->getData()->getValue()));
    if(all_company_node->getData()->getNonEmptyCompany() == nullptr){ 
        non_empty_companies->insert(non_empty_company_to_add);
        all_company_node->getData()->setNonEmptyCompany(non_empty_company_to_add);
    }
    //add employee to all employees by id,salary tree 
    //add employee to all employee by id
    all_employees_by_id_tree->insert(employee_id_to_add);
    //add to all employee by salary
    shared_ptr<EmployeeBySalary> employee_salary_to_add(new EmployeeBySalary(Salary,EmployeeID)); 
    all_employees_by_salary_tree->insert(employee_salary_to_add);
    employee_id_to_add->setSalaryPtr(employee_salary_to_add);
    employee_id_to_add->setCompanyPtr(non_empty_company_to_add);

    //add employee to company employees by id,salary tree 
    shared_ptr<TreeNode<NonEmptyCompany>> non_empty_company_node(non_empty_companies->find(non_empty_company_to_add));
    //add employee to company employee by id
    shared_ptr<Tree<EmployeeByID>> company_id_tree = non_empty_company_node->getData()->getEmployeesByIDTree();
    shared_ptr<EmployeeByID> company_employee_id_to_add(new EmployeeByID(Salary, EmployeeID));
    company_id_tree->insert(company_employee_id_to_add);
    //add to company employee by salary
    shared_ptr<Tree<EmployeeBySalary>> company_salary_tree = non_empty_company_node->getData()->getEmployeesBySalaryTree();
    company_salary_tree->insert(employee_salary_to_add);
    //update company fields
    non_empty_company_node->getData()->updateHighestEarner(employee_salary_to_add);
    non_empty_company_node->getData()->setNumEmployees();

    //update system fields
    this->updateHighestEarner(employee_salary_to_add);
    num_all_employees++;

    return SUCCESS;
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::removeCompany(int CompanyID){
    //invalid arguments
    if(this == nullptr || CompanyID <= 0){
        return INVALID_INPUT;
    }
    //company not exist or not epmty
    shared_ptr<Company> company_to_find(new Company(CompanyID, 0)); 
    shared_ptr<NonEmptyCompany> non_empty_company_to_find(new NonEmptyCompany(CompanyID, 0)); 
    shared_ptr<TreeNode<Company>> all_company_node(all_companies->find(company_to_find));
    shared_ptr<TreeNode<NonEmptyCompany>> non_empty_company_node(non_empty_companies->find(non_empty_company_to_find));
    if(all_company_node == nullptr || non_empty_company_node != nullptr){
        return FAILURE;
    }
    //remove empty company
    all_companies->remove(company_to_find);
    return SUCCESS;
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::removeEmployee(int EmployeeID){
    //invalid arguments
    if(this == nullptr || EmployeeID <= 0){
        return INVALID_INPUT;
    }
    //cheack if employee exist
    shared_ptr<EmployeeByID> employee_id_to_remove(new EmployeeByID(EmployeeID, 1)); //temp grade
    shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_remove));
    if(all_employee_id_node == nullptr){
        return FAILURE;
    }
    shared_ptr<NonEmptyCompany> non_empty_company_node(all_employee_id_node->getData()->getCompanyPtr());
    shared_ptr<EmployeeBySalary> employee_salary_to_remove(new EmployeeBySalary(all_employee_id_node->getData()->getSalaryPtr()->getSalary() ,EmployeeID)); 
    //NEED TO CHECK IF BEST EARNEER
    non_empty_company_node->getEmployeesByIDTree()->remove(employee_id_to_remove);
    non_empty_company_node->getEmployeesBySalaryTree()->remove(employee_salary_to_remove);

    return SUCCESS;
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::getCompanyInfo(int CompanyID, int *Value, int *NumEmployees){
    if(this == nullptr || Value == nullptr || NumEmployees == nullptr || CompanyID <= 0){
        return INVALID_INPUT;
    }
    shared_ptr<Company> company_to_find(new Company(CompanyID, 0));
    shared_ptr<TreeNode<Company>>company = all_companies->find(company_to_find);
    if (company == nullptr) 
    {
        return FAILURE;
    }
    *Value = company->getData()->getValue();
    shared_ptr<NonEmptyCompany> company_for_num_employees = company->getData()->getNonEmptyCompany();
    if(company_for_num_employees == nullptr) {
        *NumEmployees = 0;
    }
    else {
        *NumEmployees = company_for_num_employees->getNumEmployees();
    }
    return SUCCESS;
}
////////////////////////////////////////////

////////////////////////////////////////////
StatusType System::getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    //invalid arguments
    if(this == nullptr || EmployerID == nullptr || Salary == nullptr || Grade == nullptr || EmployeeID <= 0){
        return INVALID_INPUT;
    }
    //cheack if employee exist
    shared_ptr<EmployeeByID> employee_id_to_find(new EmployeeByID(EmployeeID, 1)); //temp grade
    shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_find));
    if(all_employee_id_node == nullptr){
        return FAILURE;
    }
    //update pointers
    *Grade = all_employee_id_node->getData()->getGrade();
    *EmployerID = all_employee_id_node->getData()->getCompanyPtr()->getID();
    *Salary = all_employee_id_node->getData()->getSalaryPtr()->getSalary();
    return SUCCESS;
}
////////////////////////////////////////////

/*
StatusType System::increaseCompanyValue(int CompanyID, int ValueIncrease){

}
*/

////////////////////////////////////////////
StatusType System::promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade){
    if(this == nullptr || EmployeeID <= 0 || SalaryIncrease <= 0 )
    {
        return INVALID_INPUT;  
    }
    shared_ptr<EmployeeByID> employee_to_find(new EmployeeByID(EmployeeID, 0));
    shared_ptr<TreeNode<EmployeeByID>>employee = all_employees_by_id_tree->find(employee_to_find);
    if (employee == nullptr)
    {
        return FAILURE;
    }
    shared_ptr<EmployeeBySalary> salary_employee = employee->getData()->getSalaryPtr();
    salary_employee->setSalary(salary_employee->getSalary() + SalaryIncrease);
    if (BumpGrade>0)
    {
        employee->getData()->setGrade();
    }
    updateHighestEarner(salary_employee);
    shared_ptr<NonEmptyCompany> my_company = employee->getData()->getCompanyPtr();
    if (my_company != nullptr) 
    {
        my_company->updateHighestEarner(salary_employee);
    }
    return SUCCESS;
}
////////////////////////////////////////////

/*
StatusType System::hireEmployee(int EmployeeID, int NewCompanyID){
    if(this == nullptr || EmployeeID <= 0 || NewCompanyID <= 0 )
    {
        return INVALID_INPUT;  
    }
    shared_ptr<EmployeeByID> employee_to_find(new EmployeeByID(EmployeeID, 0));
    shared_ptr<TreeNode<EmployeeByID>>employee = all_employees_by_id_tree->find(employee_to_find);
    if (employee == nullptr)
    {
        return FAILURE;
    }
    shared_ptr<Company> company_to_find(new Company(NewCompanyID, 0));
    shared_ptr<TreeNode<Company>>company = all_companies->find(company_to_find);
    if (company == nullptr)
    {
        return FAILURE;
    }
    //temp variables to save detailes about employee
    int employer_id, salary, grade;
    getEmployeeInfo(EmployeeID, &employer_id, &salary, &grade);
    if (employer_id == NewCompanyID)
    {
        return FAILURE;
    }
    removeEmployee(EmployeeID);
    AddEmployee(this, EmployeeID, NewCompanyID, salary, grade);
    //is there a chance remove or add will fail? if so need to add
    return SUCCESS;
}

StatusType System::acquireCompany(int AcquirerID, int TargetID, double Factor){

}
*/
StatusType System::getHighestEarner(int CompanyID, int *EmployeeID){
    if(this == nullptr || EmployeeID == nullptr || CompanyID == 0 )
    {
        return INVALID_INPUT;  
    }
    if (CompanyID < 0)
    {
        if (num_all_employees == 0)
        {
            return FAILURE;
        }
        *EmployeeID = this->id_highest_earner;
        return SUCCESS;
    }
    shared_ptr<NonEmptyCompany> company_to_find(new NonEmptyCompany(CompanyID, 0));
    shared_ptr<TreeNode<NonEmptyCompany>>company = non_empty_companies->find(company_to_find);
    if (company == nullptr)
    {
        return FAILURE;
    }
    *EmployeeID = company->getData()->getHighestEarner();
    return SUCCESS;
}

StatusType System::getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees){
    if(this == nullptr || Employees == nullptr || NumOfEmployees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;  
    }
    int size = 0;
    shared_ptr<EmployeeBySalary>* tree_array;
    if (CompanyID < 0)
    {
        if (num_all_employees == 0)
        {
            return FAILURE;
        }
        size = num_all_employees;
        tree_array = new shared_ptr<EmployeeBySalary>[size];
        int index = 0;
        all_employees_by_salary_tree->inOrderDataToArray(all_employees_by_salary_tree->getRoot(), tree_array, &index);
    }
    else 
    {
        shared_ptr<NonEmptyCompany> company_to_find(new NonEmptyCompany(CompanyID, 0));
        shared_ptr<TreeNode<NonEmptyCompany>>company = non_empty_companies->find(company_to_find);
        if (company == nullptr)
        {
            return FAILURE;
        }
        size = company->getData()->getNumEmployees();
        tree_array = new shared_ptr<EmployeeBySalary>[size];
        int index = 0;
        company->getData()->getEmployeesBySalaryTree()->inOrderDataToArray(company->getData()->getEmployeesBySalaryTree()->getRoot(), tree_array, &index);
    }
    int* array = (int*)malloc(size*sizeof(int));
    if (array == NULL)
    {
        return ALLOCATION_ERROR;
    }
    int j = 0;
    for (int i = size-1; i>=0; i--)
    {
        array[j] = tree_array[i]->getID();
        j++;
    }
    delete[] tree_array;
    *Employees = array;
    *NumOfEmployees = size;
    return SUCCESS;
}
/*
StatusType System::getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees){

}

StatusType System::getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){

}

void System::quit(){

}
*/

//helper functions
void System::updateHighestEarner(shared_ptr<EmployeeBySalary> employee){
    if(employee->getSalary() > salary_of_highest_earner){
        salary_of_highest_earner = employee->getSalary();
        id_highest_earner = employee->getID();
    }
}

shared_ptr<Tree<NonEmptyCompany>> System::getNonEmptyCompanyTree(){
    return non_empty_companies;
}

shared_ptr<Tree<Company>> System::getAllCompaniesTree(){
    return all_companies;
}

shared_ptr<Tree<EmployeeBySalary>> System::getAllEmployeesBySalaryTree(){
    return all_employees_by_salary_tree;
}

shared_ptr<Tree<EmployeeByID>> System::getAllEmployeesByIdTree(){
    return all_employees_by_id_tree;
}

void System::systemDestroy(){
    shared_ptr<NonEmptyCompany>* nodes = new shared_ptr<NonEmptyCompany>[this->non_empty_companies->getSize()];
    int index = 0;
    this->non_empty_companies->inOrderDataToArray(this->non_empty_companies->getRoot(), nodes, &index);
    for (int iter = 0; iter < this->non_empty_companies->getSize(); iter++){
        nodes[iter]->getEmployeesBySalaryTree()->destroyTree(nodes[iter]->getEmployeesBySalaryTree()->getRoot());
        nodes[iter]->getEmployeesByIDTree()->destroyTree(nodes[iter]->getEmployeesByIDTree()->getRoot());   
    }
    delete[] nodes;
    this->all_companies->destroyTree(this->all_companies->getRoot());
    this->all_employees_by_id_tree->destroyTree(this->all_employees_by_id_tree->getRoot());
    this->all_employees_by_salary_tree->destroyTree(this->all_employees_by_salary_tree->getRoot());
    this->non_empty_companies->destroyTree(this->non_empty_companies->getRoot());
}