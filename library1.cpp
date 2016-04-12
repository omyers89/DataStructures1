#include "library1.h"
#include"Assignment_Company.h"

void* Init(int K){
	assignmentCompany* c = new assignmentCompany(K);
	return c;
}

StatusType  AddJobSearcher(void* DS, int engineerID, int reqSalary){
	if (!DS || engineerID < 0 || reqSalary < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		c->addJobSearcher(engineerID, reqSalary);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  RemoveJobSearcher(void* DS, int engineerID){
	if (!DS || engineerID < 0 ){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		c->removeJobSercher(engineerID);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  Hire(void* DS, int companyID, int engineerID){
	if (!DS || engineerID < 0 || companyID < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		c->assign(companyID, engineerID);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;

}

StatusType  HireBySalary(void* DS, int companyID, int salaryThd){
	if (!DS || salaryThd < 0 || companyID < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		c->assignBySalary(companyID,salaryThd);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;

}


StatusType  Bonus(void* DS, int companyID, int engineerID, int bonus){
	if (!DS || engineerID < 0 || companyID < 0 || bonus < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		c->bonus(companyID, engineerID, bonus);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;

}

StatusType  Fire(void* DS, int companyID, int engineerID){
	if (!DS || engineerID < 0 || companyID < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		c->Fire(companyID, engineerID);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;


}

StatusType  GetNumEmployed(void* DS, int companyID, int* num){
	if (!DS || !num || companyID < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		*num = c->getNumEmployee(companyID);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;
}


StatusType  HighestPaid(void* DS, int companyID, int* engineerID){
	if (!DS || !engineerID || companyID < 0){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		*engineerID = c->highstPaid(companyID);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;
}

StatusType  CutBacks(void* DS, int companyID, int salaryThd, int salaryDecrease){
	if (!DS || salaryThd<0 || companyID < 0 || salaryDecrease < 0 || salaryDecrease > salaryThd){
		return INVALID_INPUT;
	}
	try{
		assignmentCompany* c = (assignmentCompany*)DS;
		if (c->getNumCompanies() <= companyID){
			return INVALID_INPUT;
		}
		c->cutbacks(companyID, salaryThd, salaryDecrease);
	}
	catch (std::bad_alloc& ){
		return ALLOCATION_ERROR;
	}
	catch (...){
		return FAILURE;
	}
	return SUCCESS;

}

void        Quit(void** DS){
	assignmentCompany* c = (assignmentCompany*)*DS;
	delete c;
 *DS=NULL;
}