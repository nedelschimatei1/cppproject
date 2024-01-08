#include <iostream>
#include <ctime>
#include <cctype>
#include "classes.cpp"

using namespace std;

int Ticket::ticketsSold = 0;

int main() {
	Zone z1("Category 1", 100, 3, 5);
	Zone z2("Category 2", 50, 5, 5);
	EventLocation ev1("Bucharest",z1);
	ev1.addZone(z2);
	EventLocation ev3("Hong Kong");
	EventDetails eve1("Name", "01-10-2003", "20-11",ev1);
	cout << eve1.getEventTime();
	SoldTickets cashier;
	TicketingSystem sys;
	sys.addSampleEvent(eve1);
	try {
		sys.loadEventData("nice.txt");
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
	sys.addSampleCashier(cashier);
	sys.menu();

	return 0;
}