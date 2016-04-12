#include "Engineer.h"

bool engineer::operator < (const engineer& other) const {
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT < EKO;
}

bool engineer::operator >(const engineer& other) const {
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT > EKO;
}

bool engineer::operator <= (const engineer& other) const{
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT <= EKO;
}

bool engineer::operator >= (const engineer& other) const{
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT >= EKO;
}

bool engineer::operator == (const engineer& other) const{
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT == EKO;
}

bool engineer::operator != (const engineer& other) const{
	engineerKey EKT(*this);
	engineerKey EKO(other);
	return EKT != EKO;
}

bool engineerKey::operator < (const engineerKey& other) const{
	if (salary<other.salary){
		return true;
	}
	if (salary == other.salary){
		return (id < other.id);
	}
	return false;
}

bool engineerKey::operator >(const engineerKey& other) const{
	if (salary>other.salary){
		return true;
	}
	if (salary == other.salary){
		return (id > other.id);
	}
	return false;
}
std::ostream& operator<<(std::ostream& out, const engineerKey& eng){
	out<< eng.id << ","<<eng.salary <<std::endl;
	return out;
}
std::ostream& operator<<(std::ostream& out, const engineer& eng){
	out<<"id:"<< eng.id<<"salary:"<< eng.salary<<std::endl;
	return out;
}