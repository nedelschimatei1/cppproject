#include <iostream>
#include <ctime>
#include "classes.cpp"

using namespace std;

int Ticket::ticketsSold = 0;

int main() {
	Row r2(9);
	Row r3(10);
	Zone z1("VIP", 100, 3, 5);
	z1.addRow(r2);
	Zone z2("Category 1", 50, r3);
	EventLocation ev1("Bucharest",z1);
	EventLocation ev3("Hong Kong");
	ev1.printLocationDetails();
	ev1.buyTicketFromZones(1, 3, 4);
	ev1.displaySeatsFromZones();
	EventDetails eve1("Name", "01-10-2003", "20:11");
	EventDetails eve2 = eve1;
	cout << eve2.getEventName()<<endl;
	cout << eve2.getEventTime()<<endl;
	cout << eve2.getEventDate()<<endl;
	SoldTickets footballcashier;
	FootballTicketFactory FootballFactory(footballcashier);
	Ticket footballTicket = FootballFactory.generateTicket("Matei", ev1, eve1);
	Ticket footballTicket1 = FootballFactory.generateTicket("Jean", ev1, eve2);
	Ticket footballTicket2 = FootballFactory.generateTicket("Jean1", ev1, eve2);
	 footballcashier.printSoldTickets();
	return 0;
}