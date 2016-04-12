#ifndef _ASSIGNMENT_COMPANY_H_
#define _ASSIGNMENT_COMPANY_H_

#include "Company.h"
#include "HitechCompany.h"
#include "Oone_array.h"

class assignmentCompany : public company{
private:
	Oone_Array<hitechCompany*> compArr;
	int numOfCompanies;
	virtual void FooBar(){} //empty implementation to the pure virtual function
	assignmentCompany(const assignmentCompany& other)::compArr(0, NULL), numOfCompanies(0) {}
	void operator = (const assignmentCompany&){}
public:
	assignmentCompany(int k) : compArr(k, NULL), numOfCompanies(k) {}
	/*
	 * the function receives id an requested salary and add an engineer
	 * to the database of the assignment company.
	 * EXCEPTIONS:
	 * throw an exception (keyAlreadyIn) if the engineer with the
	 * same id already exist in the database of the assignment company;
	 */
	void addJobSearcher(int engineerID, int reqSalary);
	/*
	 * the function receives id of the engineer we want to remove from the
	 * database of the assignment company.
	 * EXCEPTIONS:
	 *  NotFound - if the engineer not found in the assignment comp database.
	 *  AlreadyHired- if the engineer is already assigned to hitech company.
	 */
	void removeJobSercher(int engineerID);
	/*
	 * the function receives the id of the company we want to assign to,
	 * and the id of the job searcher. and assign it to the hitech company.
	 * EXCEPTIONS:
	 * illegalCompany- if the hitech company was not found in the assingnment compdatabase
	 * NotFound- if the id is not found at the assignment company
	 * AlreadyHired- if the engineer is already hired.
	 */
	void assign(int companyID, int id);

	/*
	 * 	the function receives the id of the company we want to assign to,
	 *	and salary limit. and assign the engineer with the lower or equal
	 * 	requested salary that is found in assignment company to the hitech
	 *  company.
	 * EXCEPTIONS:
	 * 	KeyOutOfBundries- if we didnt find engineer with lower or equal requested salary
	 * 	illegalCompany- if the hitech company was not found in the assingnment compdatabase
	 * 	NotFound- if the id is not found at the assignment company
	 * 	AlreadyHired- if the engineer is already hired.
	 */
	void assignBySalary(int companyId, int salaryThd);
	/*
	 * the function updates the salary of an engineer working in the hitech company
	 * EXCEPTIONS:
	 * NotFound- if the company is empty
	 * KeyNotFound- if the engineer is not found in the hitech company
	 */
	void bonus(int companyID, int engineerID, int bonus);

	/*
	 * the function remove an engineer from the hitech company and put it
	 * back in to the assignment company
	 * EXCEPTIONS:
	 * NotFound- if the company not found or the engineer is not found.
	 */
	void Fire(int companyID, int engineerID);

	/*
	 * the function returns the number of engineers in a hitech company.
	 * using the function of AVL_Tree
	 * no throwing.
	 */
	inline int getNumEmployee(int companyID){
		if (compArr.get(companyID) == NULL){
			return 0;
		}
		return compArr.get(companyID)->getNumImployee();
	}
	/*
	 * the function returns the id of engineer with the  salary
	 *   in a hitech company.
	 * using the function of AVL_Tree
	 * EXCEPTIONS:
	 * NotFound- if fthe company is empty.
	 */
	inline int highstPaid(int companyID){
		if ((compArr.get(companyID) == NULL) || (compArr.get(companyID)->getNumImployee()==0)){
			throw NotFound();
		}
		return compArr.get(companyID)->highestPaid();
	}

	/*
	 * the function perform cut back  at the hitech company for all engineers with
	 * requested salary more than the salaryThd. the salary decreased by  salaryDecrease
	 * EXCEPTIONS:
	 * NotFound- if the company is empty.
	 */
	void cutbacks(int companyID, int salaryThd, int salaryDecrease);


	/*
	 * return the member numOfCompanies of the assignment company
	 */
	inline int getNumCompanies() const{
		return numOfCompanies;
	}
	/* destructor*/
	~assignmentCompany(){
		for (int i = 0; i < numOfCompanies; ++i){
			delete compArr.get(i);
		}
	}
};

#endif

