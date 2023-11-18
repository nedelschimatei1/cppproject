#include <iostream>
#include "classes.cpp"

using namespace std;

int main() {
	Row r1(10);
	Row r2(7);
	Row r3(5);
	Zone z1("VIP", 100, r1);
	z1.addRow(r2);
	z1.getZoneseats();
	cout << endl;
	Zone z2("Category 1", 50, r3);
	z2.getZoneseats();
	cout << endl;
	EventLocation ev1("Bucharest", z1);
	ev1.addZone(z2);
	ev1.displaySeatsFromZones();

	return 0;
}