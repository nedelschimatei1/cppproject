#include <iostream>
#include <ctime>
#include "classes.cpp"

using namespace std;

int Ticket::ticketsSold = 0;

int main() {
	Row r1(5);
	r1.buySeat(1);
	Row r2(9);
	Row r3(10);
	Zone z1("VIP", 100, r1);
	z1.addRow(r2);
	Zone z2("Category 1", 50, r3);
	EventLocation ev1("Bucharest", z1);
	EventLocation ev3("Hong Kong");
	ev1.printLocationDetails();
	ev1.displaySeatsFromZones();
	EventDetails eve1("Name", "01-10-2003", "20:11");
	EventDetails eve2 = eve1;
	cout << eve2.getEventName()<<endl;
	cout << eve2.getEventTime()<<endl;
	cout << eve2.getEventDate()<<endl;
	FootballTicketFactory FootballFactory;
	Ticket footballTicket = FootballFactory.generateTicket("Matei", ev1, eve1);
	Ticket footballTicket1 = FootballFactory.generateTicket("Jean", ev1, eve2);
	cout<< footballTicket.getHoldersName()<<endl;
	cout << footballTicket.getTicketType()<<endl;
	cout << footballTicket1.getHoldersName() << endl;
	cout << footballTicket1.getTicketType() << endl;
	cout << Ticket::ticketsSold;
	return 0;
}