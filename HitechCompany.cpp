#include "HitechCompany.h"
void hitechCompany::updateHighstPaid(){
	if (salaryTree->isEmpty()){
		highestSalary = -1;
		highestPaidEm = -1;
		return;
	}
	engineer tmpEn = salaryTree->treeMaxValue();
	highestPaidEm = tmpEn.getID();
	highestSalary = tmpEn.getSalary();
}

void hitechCompany::insert(engineer e){
	company::insert(e);
	updateHighstPaid();
}

void hitechCompany::remove(int id){
	company::remove(id);
	updateHighstPaid();
}

void hitechCompany::giveBonus(int id, int amount){

	engineer e = getEngineer(id);
	remove(id);
	e.setSalary(e.getSalary() + amount);
	insert(e);
}

void hitechCompany::cutBacks(int salaryThd, int salaryDecrease){
	if (getNumImployee() == 0){
		throw CompanyIsEmpty();
	}
	CutBack<int> cutBackByID(salaryThd, salaryDecrease);
	idTree->inorderTreeWalk(idTree->getRootKey(), cutBackByID);
	CutBack<engineerKey> ekcb(salaryThd, salaryDecrease);
	engineerKeyMaker ekm;
	engineer mock(-1, -1);
	treeChanger<engineerKey, engineer, CutBack<engineerKey>, engineerKeyMaker> cutBackChanger(salaryTree->getSize(), mock, ekcb, ekm);
	salaryTree->inorderTreeWalk(salaryTree->getRootKey(), cutBackChanger);
	cutBackChanger.treeChangerSort();
	salaryTree->inorderTreeWalk(salaryTree->getRootKey(), cutBackChanger);
	updateHighstPaid();
}
