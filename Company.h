#ifndef _COMPANY_H_
#define _COMPANY_H_
#include "AVL_Tree.h"
#include<iostream>
#include <exception>
#include <stdio.h>
#include "Engineer.h"



class AlreadyHired : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Engineer is already hired\n";
	}
};

class NotFound : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Object Not Found\n";
	}
};
class illegalCompany : public std::exception{
public:
	virtual const char* what() const throw(){
		return "company index not found\n";
	}
};
class CompanyIsEmpty : public std::exception{
public:
	virtual const char* what() const throw(){
		return "company is empty\n";
	}
};


class company{
protected:
	AVL_Tree<int, engineer>* idTree;
	AVL_Tree<engineerKey, engineer>* salaryTree;
	/*
	 * a pure virtual function to make sure no object of this class is created.
	 */
	virtual void FooBar() = 0;
	
public:
	company() : idTree(new AVL_Tree<int, engineer>), salaryTree(new AVL_Tree<engineerKey, engineer>) {}

	/*
	 * add an- e engineer to both AVL_Trees of the company.
	 * EXCEPTION:
	 *  keyAlreadyIn- if the engineer is already in the company.
	 */
	virtual void insert(engineer e);
	/*
	 * add an- e engineer to AVL_Trees salaryTree of the company.
	 * EXCEPTION:
	 *  keyAlreadyIn- if the engineer is already in the company.
	 */
	virtual void insertToSalary(engineer e);
	/*
		 * add an- e engineer to AVL_Trees idTree of the company.
		 * EXCEPTION:
		 *  keyAlreadyIn- if the engineer is already in the company.
		 */
	virtual void insertToId(engineer e);
	/*
	 * remove an- e engineer from both AVL_Trees  of the company.
	 * EXCEPTION:
	 *  KeyNotFound- if the engineer is already in the company.
	 */
	virtual void remove(int id);
	/*
	 * remove an- e engineer from  AVL_Trees salaryTree  of the company.
	 * EXCEPTION:
	 *  KeyNotFound- if the engineer is already in the company.
	 */
	virtual void removeFromSalary(int id);
	/*
	 * remove an- e engineer from  AVL_Trees idTree  of the company.
	 * EXCEPTION:
	 *  KeyNotFound- if the engineer is already in the company.
	 */
	virtual void removeFromId(int id);

	/*checks if the engineer with the id is in the company
	 * return value: true if found and otherwise false
	 */
	inline bool isIn(int id){
		return idTree->isIn(id);
	}

	/* returns the engineer with the id is in the company
	 * EXCEPTIONS:
	 * KeyNotFound- if the engineer is not found
	 */
	engineer getEngineer(int id){
		return idTree->getValue(id);
	}

	void printEmployee(){
		std::cout <<"printing by id: \n";
		idTree->printAVL();
		std::cout<<"printing by salary: \n";
		salaryTree->printAVL();
	}
	virtual ~company(){
		delete(idTree);
		delete(salaryTree);
	}
};



#endif
