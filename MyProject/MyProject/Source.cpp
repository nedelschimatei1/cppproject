#include <iostream>
#include <ctime>
#include <cctype>
#include "classes.cpp"

using namespace std;

int Ticket::ticketsSold = 0;

int main(int argc, char* argv[]) {


	Zone z1("Category 1", 100, 3, 5);
	Zone z2("Category 2", 50, 5, 5);
	EventLocation ev1("Bucharest", z1);
	ev1.addZone(z2);
	EventLocation ev3("Hong Kong");
	EventDetails eve1("Name", "01-10-2003", "20-11", ev1);
	SoldTickets cashier;
	TicketingSystem sys;
	sys.addSampleEvent(eve1);
	sys.addSampleCashier(cashier);
	sys.loadBinary("binary.dat");
	try {
		if (argc != 2) {
			cerr << "You didn't put the file argument when running the source file, to get the input event\n";
			cerr << "Usage: " << argv[0] << " file_with_data.txt" << endl;
			system("pause");
			system("cls");
		}
		else {
			string filename = argv[1];
			sys.loadEventData(filename);
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		system("pause");
		system("cls");
	}

	sys.menu();

	return 0;
}