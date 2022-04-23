#include "system.h"


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


StatusType System::addCompany(int CompanyID, int Value){
    //invalid arguments
    if(this == nullptr || CompanyID <= 0 || Value <= 0){
        return INVALID_INPUT;
    }
    try {
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
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}


StatusType System::addEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    //invalid arguments
    if(this == nullptr || EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0){
        return INVALID_INPUT;
    }
    if(EmployeeID == 1580 || EmployeeID == 194)
    {
        int x =1;
    }
    try {
        //company not exist in allCompanyTree || employee already exist
        shared_ptr<Company> company_to_find(new Company(CompanyID, 0)); 
        shared_ptr<EmployeeByID> employee_id_to_add(new EmployeeByID(EmployeeID, Grade)); 
        shared_ptr<TreeNode<Company>> all_company_node(all_companies->find(company_to_find));
        shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_add));
        if(all_company_node == nullptr || all_employee_id_node != nullptr){
            return FAILURE;
        }

        //cheack if the company is empty- need to add to nonEmptyCompanyTree
        if(all_company_node->getData()->getNonEmptyCompany() == nullptr){ 
            shared_ptr<NonEmptyCompany> non_empty_company_to_add(new NonEmptyCompany(CompanyID, all_company_node->getData()->getValue()));
            non_empty_companies->insert(non_empty_company_to_add);
            all_company_node->getData()->setNonEmptyCompany(non_empty_company_to_add);
        }

        shared_ptr<NonEmptyCompany> non_empty_company_to_add = all_company_node->getData()->getNonEmptyCompany();
        employee_id_to_add->setCompanyPtr(non_empty_company_to_add);
        //add employee to all employees by id,salary tree 
        //add employee to all employee by id
        all_employees_by_id_tree->insert(employee_id_to_add);
        //add to all employee by salary
        shared_ptr<EmployeeBySalary> employee_salary_to_add(new EmployeeBySalary(Salary,EmployeeID)); 
        all_employees_by_salary_tree->insert(employee_salary_to_add);
        employee_id_to_add->setSalaryPtr(employee_salary_to_add);

        //add employee to company employees by id,salary tree 
        shared_ptr<TreeNode<NonEmptyCompany>> non_empty_company_node(non_empty_companies->find(non_empty_company_to_add));
        //add employee to company employee by id
        shared_ptr<Tree<EmployeeByID>> company_id_tree = non_empty_company_node->getData()->getEmployeesByIDTree();
        company_id_tree->insert(employee_id_to_add);
        //add to company employee by salary
        shared_ptr<Tree<EmployeeBySalary>> company_salary_tree = non_empty_company_node->getData()->getEmployeesBySalaryTree();
        company_salary_tree->insert(employee_salary_to_add);
        //update company fields
        non_empty_company_node->getData()->updateHighestEarner(employee_salary_to_add);
        non_empty_company_node->getData()->setNumEmployees(1);

        //update system fields
        this->updateHighestEarner(employee_salary_to_add);
        num_all_employees++;
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


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


StatusType System::removeEmployee(int EmployeeID){
    //invalid arguments
    if(this == nullptr || EmployeeID <= 0){
        return INVALID_INPUT;
    }
    try{
        //check if employee exist
        shared_ptr<EmployeeByID> employee_id_to_remove(new EmployeeByID(EmployeeID, 1)); //temp grade
        shared_ptr<TreeNode<EmployeeByID>> all_employee_id_node(all_employees_by_id_tree->find(employee_id_to_remove));
        if(all_employee_id_node == nullptr){
            return FAILURE;
        }
        //delete employee from company trees
        shared_ptr<NonEmptyCompany> non_empty_company_node(all_employee_id_node->getData()->getCompanyPtr());
        shared_ptr<EmployeeBySalary> employee_salary_to_remove = all_employee_id_node->getData()->getSalaryPtr(); 
        //employee to remove is the only one who hired in comapny and the company will become empty
        if(non_empty_company_node->getNumEmployees() == 1){
            non_empty_company_node->getEmployeesBySalaryTree()->remove(employee_salary_to_remove);
            non_empty_company_node->getEmployeesByIDTree()->remove(employee_id_to_remove);
            non_empty_company_node->setNumEmployees(-1);
            non_empty_companies->remove(non_empty_company_node);
            shared_ptr<Company> company_to_update(new Company(non_empty_company_node->getID(), 0)); //temp value
            shared_ptr<TreeNode<Company>> company_to_update_node(all_companies->find(company_to_update));
            company_to_update_node->getData()->setNonEmptyCompany(nullptr);
        }
        //the company won't remain empty after remove employee
        else{
            if(non_empty_company_node->getHighestEarner() == employee_salary_to_remove->getID()){
                non_empty_company_node->changeHighestEarnerBeforeRemove(employee_salary_to_remove);
            }
            non_empty_company_node->getEmployeesByIDTree()->remove(employee_id_to_remove);
            non_empty_company_node->getEmployeesBySalaryTree()->remove(employee_salary_to_remove);
            non_empty_company_node->setNumEmployees(-1);
        }
        //delete employee from system trees
        //this is the only employee in the system
        if(num_all_employees == 1){
            id_highest_earner = 0;
            salary_of_highest_earner = 0;
            num_all_employees = 0;
            all_employees_by_salary_tree->remove(employee_salary_to_remove);
            all_employees_by_id_tree->remove(employee_id_to_remove);
            return SUCCESS;
        }
        if(id_highest_earner == employee_salary_to_remove->getID()){
            changeHighestEarnerBeforeRemove(employee_salary_to_remove);
        }
        all_employees_by_salary_tree->remove(employee_salary_to_remove);
        all_employees_by_id_tree->remove(employee_id_to_remove);
        num_all_employees -= 1;
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::getCompanyInfo(int CompanyID, int *Value, int *NumEmployees){
    if(this == nullptr || Value == nullptr || NumEmployees == nullptr || CompanyID <= 0){
        return INVALID_INPUT;
    }
    try {
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
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::getEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    //invalid arguments
    if(this == nullptr || EmployerID == nullptr || Salary == nullptr || Grade == nullptr || EmployeeID <= 0){
        return INVALID_INPUT;
    }
    try{
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
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::increaseCompanyValue(int CompanyID, int ValueIncrease){
    //invalid arguments
    if(this == nullptr || CompanyID <= 0 || ValueIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        //check if company exists
        shared_ptr<Company> company_to_find(new Company(CompanyID, 0)); 
        shared_ptr<TreeNode<Company>> all_company_node(all_companies->find(company_to_find));
        if(all_company_node == nullptr){
            return FAILURE;
        }
        //update value in all companies tree
        all_company_node->getData()->addValue(ValueIncrease);
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS; 
}


StatusType System::promoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade){
    if(this == nullptr || EmployeeID <= 0 || SalaryIncrease <= 0 )
    {
        return INVALID_INPUT;  
    }
    try{
        shared_ptr<EmployeeByID> employee_to_find(new EmployeeByID(EmployeeID, 0));
        shared_ptr<TreeNode<EmployeeByID>>employee = all_employees_by_id_tree->find(employee_to_find);
        if (employee == nullptr)
        {
            return FAILURE;
        }
        //temp variables to save detailes about employee
        int employer_id, salary, grade;
        getEmployeeInfo(EmployeeID, &employer_id, &salary, &grade);
        removeEmployee(EmployeeID);
        addEmployee(EmployeeID, employer_id, salary+SalaryIncrease, grade);

        shared_ptr<TreeNode<EmployeeByID>>changed_employee = all_employees_by_id_tree->find(employee_to_find);
        if (BumpGrade>0)
        {
            changed_employee->getData()->setGrade();
        }
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::hireEmployee(int EmployeeID, int NewCompanyID){
    if(this == nullptr || EmployeeID <= 0 || NewCompanyID <= 0 )
    {
        return INVALID_INPUT;  
    }
    try{
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
        addEmployee(EmployeeID, NewCompanyID, salary, grade);
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::acquireCompany(int AcquirerID, int TargetID, double Factor){
    //invalid arguments
    if(this == nullptr || AcquirerID <= 0 || TargetID <= 0 || TargetID == AcquirerID || Factor < 1.00){
        return INVALID_INPUT;  
    }
    //check if companies exist and if the condition to acquirer is contained
    try{
        shared_ptr<Company> acquirer_company_to_find(new Company(AcquirerID, 0)); 
        shared_ptr<Company> target_company_to_find(new Company(TargetID, 0)); 
        shared_ptr<TreeNode<Company>> acquirer_all_company_node(all_companies->find(acquirer_company_to_find));
        shared_ptr<TreeNode<Company>> target_all_company_node(all_companies->find(target_company_to_find));
        if(acquirer_all_company_node == nullptr || target_all_company_node == nullptr || acquirer_all_company_node->getData()->getValue() < 10 * target_all_company_node->getData()->getValue()){
            return FAILURE;
        }
        //calculate merge company fields 
        int new_value = floor(Factor * (acquirer_all_company_node->getData()->getValue() + target_all_company_node->getData()->getValue()));
        //if target company is empty
        if(target_all_company_node->getData()->getNonEmptyCompany() == nullptr){
            acquirer_all_company_node->getData()->setValue(new_value);
            all_companies->remove(target_company_to_find);
            return SUCCESS;
        }
        //if acquired comapny is empty
        //if two companies are not empty
        int new_id_highest_earner;
        int new_salary_of_highest_earner;
        int new_num_employees;
        if(acquirer_all_company_node->getData()->getNonEmptyCompany() != nullptr){
            new_id_highest_earner = max_id(acquirer_all_company_node->getData()->getNonEmptyCompany()->getHighestSalary(), target_all_company_node->getData()->getNonEmptyCompany()->getHighestSalary(),
                acquirer_all_company_node->getData()->getNonEmptyCompany()->getHighestEarner(), target_all_company_node->getData()->getNonEmptyCompany()->getHighestEarner());
            new_salary_of_highest_earner = max(acquirer_all_company_node->getData()->getNonEmptyCompany()->getHighestSalary(), target_all_company_node->getData()->getNonEmptyCompany()->getHighestSalary());
            new_num_employees = acquirer_all_company_node->getData()->getNonEmptyCompany()->getNumEmployees() + target_all_company_node->getData()->getNonEmptyCompany()->getNumEmployees();
        }
        else{
            new_id_highest_earner = target_all_company_node->getData()->getNonEmptyCompany()->getHighestEarner();
            new_salary_of_highest_earner = target_all_company_node->getData()->getNonEmptyCompany()->getHighestSalary();
            new_num_employees = target_all_company_node->getData()->getNonEmptyCompany()->getNumEmployees();
        }
        //create non empty new company
        shared_ptr<NonEmptyCompany> new_non_empty_company(new NonEmptyCompany(AcquirerID, new_value, new_id_highest_earner, new_salary_of_highest_earner, new_num_employees));
        //create new id and salary trees of the merge company
        shared_ptr<Tree<EmployeeByID>> id_merge_tree(new Tree<EmployeeByID>);
        shared_ptr<Tree<EmployeeBySalary>> salary_merge_tree(new Tree<EmployeeBySalary>);
        shared_ptr<Tree<EmployeeByID>> temp_id = nullptr;
        shared_ptr<Tree<EmployeeBySalary>> temp_salary = nullptr;
        if(acquirer_all_company_node->getData()->getNonEmptyCompany() != nullptr){
            salary_merge_tree = mergeTrees(acquirer_all_company_node->getData()->getNonEmptyCompany()->getEmployeesBySalaryTree(), target_all_company_node->getData()->getNonEmptyCompany()->getEmployeesBySalaryTree());
            id_merge_tree = mergeTrees(acquirer_all_company_node->getData()->getNonEmptyCompany()->getEmployeesByIDTree(), target_all_company_node->getData()->getNonEmptyCompany()->getEmployeesByIDTree());
            
        }
        else{
            id_merge_tree = mergeTrees(temp_id, target_all_company_node->getData()->getNonEmptyCompany()->getEmployeesByIDTree());
            salary_merge_tree = mergeTrees(temp_salary, target_all_company_node->getData()->getNonEmptyCompany()->getEmployeesBySalaryTree());
        }
        //updates employeey company ptr
        int index = 0;
        shared_ptr<EmployeeByID>* merge_array = new shared_ptr<EmployeeByID>[new_num_employees];
        id_merge_tree->inOrderDataToArray (id_merge_tree->getRoot(), merge_array, &index);
        for(int i = 0; i < new_num_employees ; i++){
            merge_array[i]->setCompanyPtr(new_non_empty_company);
        }
        delete[] merge_array;
        //create new non_empty_company to add the non empty companise tree
        new_non_empty_company->setEmployeesByIDTree(id_merge_tree);
        new_non_empty_company->setEmployeesBySalaryTree(salary_merge_tree);
        shared_ptr<NonEmptyCompany> acquirer_non_empty_company_to_remove(new NonEmptyCompany(AcquirerID, 0)); 
        shared_ptr<NonEmptyCompany> target_non_empty_company_to_remove(new NonEmptyCompany(TargetID, 0)); 
        non_empty_companies->remove(acquirer_non_empty_company_to_remove);
        non_empty_companies->remove(target_non_empty_company_to_remove);
        non_empty_companies->insert(new_non_empty_company);
        //create new company to add to all companie tree
        all_companies->remove(acquirer_company_to_find);
        all_companies->remove(target_company_to_find);
        shared_ptr<Company> new_company(new Company(AcquirerID, new_value));
        new_company->setNonEmptyCompany(new_non_empty_company);
        all_companies->insert(new_company);
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


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
    try{
        shared_ptr<NonEmptyCompany> company_to_find(new NonEmptyCompany(CompanyID, 0));
        shared_ptr<TreeNode<NonEmptyCompany>>company = non_empty_companies->find(company_to_find);
        if (company == nullptr)
        {
            return FAILURE;
        }
        *EmployeeID = company->getData()->getHighestEarner();
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::getAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees){
    if(this == nullptr || Employees == nullptr || NumOfEmployees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;  
    }
    try{
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
            delete[] tree_array;
            return ALLOCATION_ERROR;
        }
        int j = 0;
        for (int i = size-1 ; i>=0; i--)
        {
            array[j] = tree_array[i]->getID();
            j++;
        }
        delete[] tree_array;
        *NumOfEmployees = size;
        *Employees = array;
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::getHighestEarnerInEachCompany(int NumOfCompanies, int **Employees){
    if(this == nullptr || Employees == nullptr ||  NumOfCompanies < 1)
    {
        return INVALID_INPUT;  
    }
    if (non_empty_companies->getSize() < NumOfCompanies)
    {
        return FAILURE;
    } 
    try{
        shared_ptr<NonEmptyCompany>* data_array = new shared_ptr<NonEmptyCompany>[NumOfCompanies];
        int index = 0;
        int limit_companies = NumOfCompanies;
        non_empty_companies->LimitedinOrderDataToArray(non_empty_companies->getRoot(), data_array, &index, &limit_companies);
        int* array = (int*)malloc(NumOfCompanies*sizeof(int));
        if (array == NULL)
        {
            delete[] data_array;
            return ALLOCATION_ERROR;
        }
        for(int i=0; i<NumOfCompanies; i++)
        {
            array[i] = data_array[i]->getHighestEarner();
        }
        delete[] data_array;
        *Employees = array;
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType System::getNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if(this == nullptr || TotalNumOfEmployees == nullptr ||  NumOfEmployees == nullptr || CompanyID == 0 ||
    MinEmployeeID < 0 || MaxEmployeeId < 0 || MinSalary < 0 || MinGrade < 0 || MaxEmployeeId < MinEmployeeID)
    {
        return INVALID_INPUT;  
    }
    try{
        *NumOfEmployees = 0;
        shared_ptr<EmployeeByID> min_employee(new EmployeeByID(MinEmployeeID, 0));
        shared_ptr<EmployeeByID> max_employee(new EmployeeByID(MaxEmployeeId, 0));
        if (CompanyID < 0)
        {
            if (num_all_employees==0) return FAILURE;
            shared_ptr<EmployeeByID>* data_array = new shared_ptr<EmployeeByID>[num_all_employees];
            int index = 0;
            all_employees_by_id_tree->minMaxInOrderDataToArray(all_employees_by_id_tree->getRoot(), data_array, &index, min_employee, max_employee);
            *TotalNumOfEmployees = index; 
            for (int i=0; i<index; i++)
            {
                if(data_array[i]->getSalaryPtr()->getSalary() >= MinSalary && data_array[i]->getGrade() >= MinGrade)
                {
                    (*NumOfEmployees)++;
                }
            }
            delete [] data_array;
            return SUCCESS;
        }
        else
        {
            shared_ptr<NonEmptyCompany> company_to_find(new NonEmptyCompany(CompanyID, 0));
            shared_ptr<TreeNode<NonEmptyCompany>>company = non_empty_companies->find(company_to_find);
            if (company == nullptr)
            {
                return FAILURE;
            }
            shared_ptr<EmployeeByID>* data_array = new shared_ptr<EmployeeByID>[company->getData()->getNumEmployees()];
            int index = 0;
            company->getData()->getEmployeesByIDTree()->minMaxInOrderDataToArray(company->getData()->getEmployeesByIDTree()->getRoot(), data_array, &index, min_employee, max_employee);
            *TotalNumOfEmployees = index; 
            for (int i=0; i<index; i++)
            {
                if(data_array[i]->getSalaryPtr()->getSalary() >= MinSalary && data_array[i]->getGrade() >= MinGrade)
                {
                    (*NumOfEmployees)++;
                }
            }
            delete [] data_array;
            return SUCCESS;

        }
    }
    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}


void System::quit(){
    systemDestroy();
}


//helper functions
void System::updateHighestEarner(shared_ptr<EmployeeBySalary> employee){
    if(employee->getSalary() == salary_of_highest_earner)
    {
        if(employee->getID() < id_highest_earner)
        {
            id_highest_earner = employee->getID();
        }
    }
    if(employee->getSalary() > salary_of_highest_earner){
        salary_of_highest_earner = employee->getSalary();
        id_highest_earner = employee->getID();
    }
}


void System::changeHighestEarnerBeforeRemove(shared_ptr<EmployeeBySalary> employee){
    if(num_all_employees > 1)
    {
        shared_ptr<TreeNode<EmployeeBySalary>> salary_employee = all_employees_by_salary_tree->find(employee);
        if(salary_employee->getLeft() != nullptr)
        {
            /*
            if(salary_employee->getLeft()->getRight() != nullptr){
                salary_employee = salary_employee->getLeft();
                while(salary_employee->getRight() != nullptr){
                    salary_employee = salary_employee->getRight();
                }
                id_highest_earner = salary_employee->getData()->getID();
                salary_of_highest_earner = salary_employee->getData()->getSalary();
            }
            */
            if(salary_employee->getLeft()->getRight() != nullptr)
            {
                shared_ptr<EmployeeBySalary> next_highest_employee = salary_employee->getLeft()->getRight()->getData();
                id_highest_earner = next_highest_employee->getID();
                salary_of_highest_earner = next_highest_employee->getSalary();
            }
            else{
                shared_ptr<EmployeeBySalary> next_highest_employee = salary_employee->getLeft()->getData();
                id_highest_earner = next_highest_employee->getID();
                salary_of_highest_earner = next_highest_employee->getSalary();
            }
        }
    }
    else {
        id_highest_earner = 0;
        salary_of_highest_earner = 0;
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


int System::max(int a, int b){
    return a > b ? a : b;
}


int System::max_id(int salary_a, int salary_b, int id_a, int id_b){
    if(salary_a == salary_b)
    {
        if(id_a < id_b)
        {
            return id_a;
        }
        return id_b;
    }
    if(salary_a < salary_b)
    {
        return id_b;
    }
    return id_a;
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