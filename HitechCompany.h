#ifndef HITECH_COMPANY_H
#define HITECH_COMPANY_H

#include "Company.h"

/*
hitechCompany is a derived class from company
*/
class hitechCompany :public company{
private:
	int highestSalary;
	int highestPaidEm;
	hitechCompany(const hitechCompany&) :highestSalary(0), highestPaidEm(0){}
	void operator = (const hitechCompany&){}
	virtual void FooBar(){}
	/*
	private function updateHighstPaid will update the details about the highst paid engineer hired by the hitech company
	*/
	void updateHighstPaid();
public:
	hitechCompany() : highestSalary(0), highestPaidEm(0){}
	/*
	function insert will insert engineer to the company
	*/
	virtual void insert(engineer e);
	/*
	function remove will remove engineer with the given id from the company
	*/
	virtual void remove(int id);
	/*
	function giveBonus will increase the salary given to the engineer with the given id by amount
	*/
	void giveBonus(int id, int amount);
	/*
	functoin cutBacks will reduce every engineer's salary greater or equel to salaryThd by salaryDecrease
	*/
	void cutBacks(int salaryThd, int salaryDecrease);
	/*
	function getNumImploye will return the numberOfEmployess in the company
	*/
	inline int getNumImployee(){
		return idTree->getSize();
	}
	/*
	function getHighstPaid will return the id of the highst paid engineer in the company
	*/
	inline int highestPaid(){
		return highestPaidEm;
	}

};

/*
class CutBack is a function object which gets an AVL tree node with engineer as data and changes the engineer salart according to the giving threshold and cut
will return true if the data has changed and false otherwise
*/
template <class K>
class CutBack{
private:
	int threshold;
	int cut;
public:
	CutBack(int t, int c) : threshold(t), cut(c) {}
	bool operator()(AVL_Node<K, engineer>* node){
		engineer e = node->getData();
		int salary = e.getSalary();
		if (salary >= threshold){
			salary = salary - cut;
			e.setSalary(salary);
			node->setData(e);
			return true;
		}
		return false;
	}
};



#endif