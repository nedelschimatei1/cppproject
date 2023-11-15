#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "classes.cpp"

int main() {
	EventLocation ev("Bucuresti",5000,2,2,20);
	ev.getAvailableSeats();
	std::cout << "----" << endl;
	ev.setAvailableSeats(2,7);
	ev.buyaSeat(2,7);
	ev.getAvailableSeats();
	_CrtDumpMemoryLeaks();
	return 0;
}