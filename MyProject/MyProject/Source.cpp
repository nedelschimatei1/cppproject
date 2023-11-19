#include <iostream>
#include "classes.cpp"

using namespace std;

int main() {
	Row r1(15);
	Row r2(7);
	Row r3(5);
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
	return 0;
}