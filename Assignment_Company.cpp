#include "Assignment_Company.h"

void assignmentCompany::addJobSearcher(int engineerID, int reqSalary){
	engineer e(engineerID, reqSalary);
	insert(e);
}

void assignmentCompany::removeJobSercher(int engineerID) {
	if (!isIn(engineerID)){
		throw NotFound();
	}
	if ((idTree->getValue(engineerID)).isHired()){
		throw AlreadyHired();
	}
	remove(engineerID);
}



void assignmentCompany::assign(int companyID, int id){
	if (companyID >= numOfCompanies){
		throw illegalCompany();
	}
	if (!isIn(id)){
		throw NotFound();
	}
	if ((idTree->getValue(id)).isHired()){
		throw AlreadyHired();
	}
	if (compArr.get(companyID) == NULL){
		compArr.store(companyID, new hitechCompany);
	}
	hitechCompany* comp = compArr.get(companyID);
	engineer newEng = getEngineer(id);
	newEng.changeStatus();
	remove(id);
	insertToId(newEng);
	comp->insert(newEng);
	
	
}

void assignmentCompany::bonus(int companyID, int engineerID, int bonus){
	if (compArr.get(companyID) == NULL){
		throw NotFound();
	}
	hitechCompany* comp = compArr.get(companyID);
	
	comp->giveBonus(engineerID, bonus);
}

void assignmentCompany::Fire(int companyID, int engineerID){
	if (compArr.get(companyID) == NULL){
		throw NotFound();
	}
	hitechCompany* comp = compArr.get(companyID);
	if (!(comp->isIn(engineerID))){
		throw NotFound();
	}
	engineer e = comp->getEngineer(engineerID);
	comp->remove(engineerID);
	e.changeStatus();
	removeFromId(engineerID);
	
	insert(e);
	
}



void assignmentCompany::assignBySalary(int companyId, int salaryThd){
	int maxID = idTree->treeMaxValue().getID();
	engineer e(maxID, salaryThd);
	engineerKey EK(e);
	engineer tmpe = salaryTree->getSEValue(EK);
	
	int id = tmpe.getID();
	assign(companyId, id);
}

void assignmentCompany::cutbacks(int companyID, int salaryThd, int salaryDecrease){
	if (compArr.get(companyID) == NULL){
		throw NotFound();
	}
	hitechCompany* comp = compArr.get(companyID);
	comp->cutBacks(salaryThd, salaryDecrease);
}