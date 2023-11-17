#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>

using namespace std;

class EventLocation {
private:
    string locationName = "";
    int nrZones = 0;
    Zone* zones = nullptr;

public:

    // Setters
    void setLocationName(const string location) {
        if (location.length() < 3 || location.length() > 20) {
            throw exception("You entered an invalid string please enter another valid one (minimum 3 characters,maximum 20, for ex:`BUC`");
        };
        this->locationName = location;
    }

    void addZone(const Zone& z) {
        this->nrZones += 1;
        Zone* copy = new Zone[nrZones];
        copy[nrZones - 1] = z;
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones - 1; i++) {
                copy[i] = this->zones[i];
            }
            delete[] zones;
            this->zones = nullptr;
        }
        this->zones = copy;
    }

    // Accessor methods
    string getLocationName() {
        return this->locationName;
    }


    int getNumZones() {
        return this->nrZones;
    }

    string getZoneNames() {
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones; i++) {
                cout << this->zones[i].getZoneName() << " ";
            }
        }
        else {
            throw exception("No zones available! Please add at least one");
        }
    }

    // Other processing method
    //void printLocationDetails();

    //Constructors
    EventLocation(const string locationName,const Zone& z) {
        setLocationName(locationName);
        addZone(z);
    }

    EventLocation(const string locationName) {
        setLocationName(locationName);

    }

    //Destructor
    ~EventLocation() {
        if (zones != nullptr) {
            delete[] this->zones;
            this->zones = nullptr;
        }
    };
};

class Zone {
    string zoneName = "";
    int zoneTicketPrice = 0;
    int nrRows = 0;
    Row* zoneSeats = nullptr;

public:
    //Setters
    void zoneName(const string zoneName) {
        this->zoneName = zoneName;
    }

    void setZoneTicketPrice(int price) {
        this->zoneTicketPrice = price;
    }

    void addRow(const Row& r) {
        this->nrRows += 1;
        Row* copy = new Row[nrRows];
        copy[nrRows - 1] = r;
        if (this->zoneSeats != nullptr) {
            for (int i = 0; i < this->nrRows - 1; i++) {
                copy[i] = this->zoneSeats[i];
            }
            delete[] this->zoneSeats;
            this->zoneSeats = nullptr;
        }
        this->zoneSeats = copy;
    }

    //void getZoneseats() {
    //    if (this->zoneSeats != nullptr) {
    //        for (int i = 0; i < this->nrRows; i++) {
    //            for (int i = 0; i < zoneSeats[i].getNoSeats(); i++) {
    //                 cout << zoneSeats[i] << endl;
    //            }
    //        }
    //    }
    //    else {
    //        throw exception("No seats available! Please add at least one row");
    //    }
    //}

    //Getters
    string getZoneName() {
        return this->zoneName;
    }

    int getZoneTicketPrice() {
        return this->zoneTicketPrice;
    }

    ~Zone() {
        if (this->zoneSeats != nullptr) {
            delete[] this->zoneSeats;
            this->zoneSeats = nullptr;
        }
    };

    friend std::ostream& operator <<(std::ostream& os, const Row& c) {
        return  os << c.getSeats();
    };
};


class Row {
    int noSeats = 0; 
    int* seats = nullptr;

public:
    
    void setNoSeats(int nrseats) {
        if (nrseats < 0 || nrseats == 0) {
            throw exception("Invalid number of seats, enter an integer number bigger than 0.");
        }
        this->noSeats = nrseats;
    }


    //Setters
    void setSeats() {
        if(this->seats!=nullptr){
            delete[] this->seats;
            this->seats = nullptr;
        }
        seats = new int[this->noSeats];
        for (int i = 0; i < this->noSeats; i++){
            seats[i] = 0;
        }
    }

    //Getters
    int getNoSeats() {
        return this->noSeats;
    }

    void getSeats() {
        for (int i = 0; i < this->noSeats; i++) {
            cout << seats[i] << "\t";
        }
        cout << endl;
    }

   Row(int noSeats,const int* vector) {
        setNoSeats(noSeats);
        setSeats();
    }

   Row() {

   };


   ~Row() {
       if (this->seats != nullptr) {
           delete[] this->seats;
           this->seats = nullptr;
       }
   };
};
