#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    int size1;
	size1 = lastname.size();
	int size2;
	size2 = rhs.getLastname().size();
	int size3;
	size3 = firstname.size();
	int size4;
	size4 = rhs.getFirstname().size();
	int minlast;
	int minfirst;
	if(size1 <= size2)
	{
		minlast = size1;
	}
	else
	{
		minlast = size2;
	}
	for(int i=0; i<minlast; i++)
	{
		if(lastname[i] < rhs.getLastname()[i])
		{
			return true;
		}
		else if (lastname[i] > rhs.getLastname()[i])
		{
			return false;
		}
		else if(lastname[i] == rhs.getLastname()[i])
		{
			continue;
		}
	}
	if(size3 <= size4)
	{
		minfirst = size3;
	}
	else
	{
		minfirst = size4;
	}
	for(int j=0; j<minfirst; j++)
	{
		if (firstname[j] < rhs.getFirstname()[j])
		{
			return true;
		}
		else if (firstname[j] > rhs.getFirstname()[j])
		{
			return false;
		}
		else if(firstname[j] == rhs.getFirstname()[j])
		{
			continue;
		}
	}
	return false;
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
