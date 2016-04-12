#ifndef _ENGINEER_H
#define _ENGINEER_H

#include <ostream>
#include <stdio.h>
#include <stdlib.h>

/*
class engineer represents an engineer. contains details about id, salary and hring status
*/
class engineer {
private:
	int id;
	int salary;
	bool hired;
public:
	engineer(int i=-1, int r=-1) : id(i), salary(r), hired(false){}
	/*
	function getID will return the engineer's ID
	*/
	int getID() const{
		return id;
	}
	/*
	function getSalary will return the engineer's salary
	*/
	int getSalary() const{
		return salary;
	}
	/*
	function setSalary will change the engineer's salary
	*/
	void setSalary(int s){
		salary = s;
	}
	/*
	function changeStatus will change the engineer's hiring status
	*/
	void changeStatus(){
		hired = !hired;
	}
	/*
	function isHired will return the engineer's hiring status
	*/
	bool isHired(){
		return hired;
	}

	bool operator < (const engineer& other) const; 
	bool operator > (const engineer& other) const; 
	bool operator <= (const engineer& other) const;
	bool operator >= (const engineer& other) const;
	bool operator == (const engineer& other) const;
	bool operator != (const engineer& other) const;
	friend std::ostream& operator<<(std::ostream& out, const engineer& eng);
};


/*
class engineerKey is a class which represents engineer by salary and then by ID
support every comparing operators an operator <<
*/
class engineerKey{
private:
	int id;
	int salary;
public:
	engineerKey(engineer e) : id(e.getID()), salary(e.getSalary()) {}
	bool operator < (const engineerKey& other) const;
	bool operator >(const engineerKey& other) const;
	bool operator==(const engineerKey& other) const{
		return (id == other.id && salary == other.salary);
	}
	bool operator!=(const engineerKey& other) const{
		return (id != other.id || salary != other.salary);
	}
	bool operator<=(const engineerKey& other) const{
		return (operator<(other) || operator==(other));
	}
	bool operator>=(const engineerKey& other) const{
		return (operator>(other) || operator==(other));
	}
	friend std::ostream& operator<<(std::ostream& out, const engineerKey& eng);
};




/*
class enineerKeyMaker is a function object which gets an engineer and return engineerKey
*/
class engineerKeyMaker{
public:
	engineerKeyMaker(){}
	engineerKey operator()(engineer e){
		engineerKey EK(e);
		return EK;
	}
};


/*
class isEngineerFree is a function object which gets an engineer and return true if he's not hired and faled if he's hired
*/
class isEngineerFree{
public:
	isEngineerFree(){}
	bool operator()(engineer e){
		return !e.isHired();
	}
};
#endif