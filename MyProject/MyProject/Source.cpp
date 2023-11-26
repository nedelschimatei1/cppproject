#include <iostream>
#include <ctime>
#include "classes.cpp"

using namespace std;

int main() {
	Seat s1(0, true, false);
	Row r1(s1);
	Row r2(s1);
	Row r3(s1);
	Zone z1("VIP", 100, r1);
	z1.addRow(r2);
	Zone z2("Category 1", 50, r3);
	EventLocation ev1("Bucharest", z1);
	EventLocation ev3("Hong Kong");
	ev3 = ev1;
	ev3.addZone(z2);
	ev3.printLocationDetails();
	ev3.displaySeatsFromZones();
	ev1.printLocationDetails();
	ev1.displaySeatsFromZones();
	EventDetails eve1("Name", "01-10-2003", "20:11");
	EventDetails eventdet2 = eve1;
	cout << eventdet2.getEventName()<<endl;
	cout << eventdet2.getEventTime()<<endl;
	cout << eventdet2.getEventDate()<<endl;
	return 0;
}