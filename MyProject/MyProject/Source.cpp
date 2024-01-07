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
	ev1.addZone(z2);
	EventLocation ev3("Hong Kong");
	EventDetails eve1("Name", "01-10-2003", "20:11",ev1);
	SoldTickets footballcashier;
	FootballTicketFactory FootballFactory(footballcashier);
	Ticket footballTicket = FootballFactory.generateTicket("Matei", eve1);
	/*eve1.printLocationDetails();
	eve1.printEventSeats(); 
	cout<<footballTicket.getHoldersName();*/
	/*try {
		eve1.buySeatFromEvent(2, 2, 3);
	}
	catch (const std::exception& e) {
		std::cout << "Invalid input: " << e.what() << std::endl;
	};*/
	SoldTickets cashier;
	TicketingSystem sys;
	sys.addSampleEvent(eve1);
	sys.addSampleCashier(cashier);
	sys.menu();

	return 0;
}