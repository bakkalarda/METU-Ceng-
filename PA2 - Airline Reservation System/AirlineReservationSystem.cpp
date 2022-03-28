#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger *x;
    x = searchPassenger(firstname, lastname);
    if(x == NULL)
    {
        Passenger y(firstname, lastname);
        passengers.insert(y);
    }
    return;
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger y(firstname, lastname);
    Passenger *x = &(passengers.search(y)->data);
    if(x == NULL)
    {
        return NULL;
    }
    return x;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    Flight x(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    Flight *y;
    y = &(flights.search(x)->data);
    if(y == NULL)
    {
        flights.insert(x);
    }
    else{
        return;
    }
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    BST<Flight> copy(flights);
    std::vector<Flight *> a;
    std::vector<Flight > b;
    BSTNode<Flight> *x;
    
    while(!flights.isEmpty())
    {
        x = flights.getRoot();
        if((x->data.getDepartureCity() == departureCity) && (x->data.getArrivalCity() == arrivalCity))
        {
            Flight h;
            h = x->data;
            b.push_back(h);
        }
        flights.remove(x->data);
        x = NULL;
    }
    flights = copy;
    for(int i=(int)b.size()-1; i>=0; i--)
    {
        a.push_back(&(flights.search(b[i])->data));
    }
    return a;
}
void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger y(firstname, lastname);
    Passenger *x = &(passengers.search(y)->data);
    if(x == NULL)
    {
        return;
    }
    BST<Flight> copy(flights);
    BSTNode<Flight> *z;
    Flight h;
    while(!copy.isEmpty())
    {
        z = copy.getRoot();
        if(z->data.getFlightCode() == flightCode)
        {
            h = z->data;
            break;
        }
        copy.remove(z->data);
        z = NULL;
    }
    if(copy.isEmpty())
    {
        
        return;
    }
    Flight* k;
    k = &(flights.search(h)->data);
    Ticket new_ticket(x, k, ticketType);
    z = NULL;
    z = flights.search(h);
    z->data.addTicket(new_ticket);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger y(firstname, lastname);
    Passenger *x = &(passengers.search(y)->data);
    if(x == NULL)
    {
        return;
    }
    BST<Flight> copy(flights);
    BSTNode<Flight> *z;
    Flight h;
    Flight* k;
    while(!copy.isEmpty())
    {
        z = copy.getRoot();
        if(z->data.getFlightCode() == flightCode)
        {
            h = z->data;
            break;
        }
        copy.remove(z->data);
        z = NULL;
    }
    if(copy.isEmpty())
    {
        
        return;
    }
    z = NULL;
    k = &(flights.search(h)->data);
    Ticket new_ticket(x, k, ticketType);
    freeTicketRequests.enqueue(new_ticket);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    Queue<Ticket> helper;
    Ticket x;
    BSTNode<Flight> *z;
    Flight h;
    BST<Flight> copy(flights);
    bool add_ticket_success;
    while(!copy.isEmpty())
    {
        z = copy.getRoot();
        if(z->data.getFlightCode() == flightCode)
        {
            h = z->data;
            break;
        }
        copy.remove(z->data);
        z = NULL;
    }
    if(copy.isEmpty())
    {
        
        return;
    }
    z = flights.search(h);
    while(!freeTicketRequests.isEmpty())
    {
        x = freeTicketRequests.dequeue();
        if(x.getFlight()->getFlightCode() == flightCode)
        {
            add_ticket_success= z->data.addTicket(x);
            if(add_ticket_success == false)
            {
                helper.enqueue(x);
            }
        }
        else
        {
            helper.enqueue(x);
        }
    }
    while(!helper.isEmpty())
    {
        x = helper.dequeue();
        freeTicketRequests.enqueue(x);
        
    }
    z->data.setCompleted(true);
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
