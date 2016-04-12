#include "Company.h"
void company::insert(engineer e){
	int id = e.getID();
	engineerKey EK(e);
	idTree->insert(id, e);
	salaryTree->insert(EK, e);
}

void company::insertToSalary(engineer e){
	engineerKey EK(e);
	salaryTree->insert(EK, e);
}
void company::insertToId(engineer e){
	int id = e.getID();
	idTree->insert(id, e);
}


void company::remove(int id){
	engineer e = idTree->getValue(id);
	engineerKey EK(e);
	idTree->remove(id);
	salaryTree->remove(EK);
}

void company::removeFromSalary(int id){
	engineer e = idTree->getValue(id);
	engineerKey EK(e);
	salaryTree->remove(EK);
}

void company::removeFromId(int id){
	idTree->remove(id);
}

