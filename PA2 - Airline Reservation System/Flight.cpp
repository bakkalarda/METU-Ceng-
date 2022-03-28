#include "Flight.h"

Flight::Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    this->flightCode = flightCode;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->departureCity = departureCity;
    this->arrivalCity = arrivalCity;
    this->economyCapacity = economyCapacity;
    this->businessCapacity = businessCapacity;
    this->completed = false;
}

const std::string &Flight::getFlightCode() const {
    return flightCode;
}

const std::string &Flight::getDepartureTime() const {
    return departureTime;
}

const std::string &Flight::getArrivalTime() const {
    return arrivalTime;
}

const std::string &Flight::getDepartureCity() const {
    return departureCity;
}

const std::string &Flight::getArrivalCity() const {
    return arrivalCity;
}

int Flight::getEconomyCapacity() const {
    return economyCapacity;
}

int Flight::getBusinessCapacity() const {
    return businessCapacity;
}

bool Flight::isCompleted() const {
    return completed;
}

void Flight::setCompleted(bool completed) {
    this->completed = completed;
}

bool Flight::addTicket(const Ticket &ticket) {
    
    if(ticket.getTicketType() == economy)
    {
       
        int total_eco = 0;
        for(int i=0; i<(int)(tickets.size()); i++)
        {
            if(tickets[i].getTicketType() == economy)
            {
                total_eco++;
            }
        }
        
        if(total_eco < economyCapacity)
        {
            tickets.push_back(ticket);
            return true;
        }
    }
    else if(ticket.getTicketType() == business)
    {
        int total_business = 0;
        for(int j=0; j<(int)(tickets.size()); j++)
        {
            
            if(tickets[j].getTicketType() == business)
            {
                total_business++;
            }
        }
        
        if(total_business < businessCapacity)
        {
            tickets.push_back(ticket);
            return true;
        }
    }
    return false;
}

bool Flight::operator<(const Flight &rhs) const {
    int size1;
	size1 = this->getFlightCode().size();
    int size2;
	size2 = rhs.getFlightCode().size();
    int minsize;
	if(size1 <= size2)
	{
		minsize = size1;
	}
	else
	{
		minsize = size2;
	}
	for(int i=0; i<minsize; i++)
	{
		if(this->getFlightCode()[i] < rhs.getFlightCode()[i])
		{
			return true;
		}
		else if(this->getFlightCode()[i] > rhs.getFlightCode()[i])
		{
			return false;
		}
		else if(this->getFlightCode()[i] == rhs.getFlightCode()[i])
		{
		    continue;
		}
	}
	return false;
}

bool Flight::operator>(const Flight &rhs) const {
    return rhs < *this;
}

bool Flight::operator==(const Flight &rhs) const {
    return flightCode == rhs.flightCode;
}

bool Flight::operator!=(const Flight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Flight(flightCode: " << flight.flightCode;
    os << ", departureTime: " << flight.departureTime;
    os << ", arrivalTime: " << flight.arrivalTime;
    os << ", departureCity: " << flight.departureCity;
    os << ", arrivalCity: " << flight.arrivalCity;
    os << ", economyCapacity: " << flight.economyCapacity;
    os << ", businessCapacity: " << flight.businessCapacity;
    os << ", completed: " << (flight.completed ? "yes" : "no");
    os << ", tickets: [";
    for (int i = 0 ; i < flight.tickets.size() ; ++i) {
        os << flight.tickets[i];
        if (i != (flight.tickets.size() - 1)) os << ", ";
    }
    os << "])";
    return os;
}
