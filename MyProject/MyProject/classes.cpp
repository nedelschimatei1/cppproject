#include <iostream>
#include <string>

using namespace std;

class Row {
    int noSeats = 0;
    int* seats = nullptr;
public:
    //Setters
    void setNoSeats(int nrseats) {
        if (nrseats < 0 || nrseats == 0) {
            throw exception("Invalid number of seats, enter an integer number bigger than 0.");
        }
        this->noSeats = nrseats;
    }

    void setSeats() {
        if (this->seats != nullptr) {
            delete[] this->seats;
            this->seats = nullptr;
        }
        seats = new int[this->noSeats];
        for (int i = 0; i < this->noSeats; i++) {
            seats[i] = 0;
        }
    }

    void setSeatsWithVector(const int* vector,int sizeofvect) {
        if (this->seats != nullptr) {
            delete[] this->seats;
            this->seats = nullptr;
        }
        seats = new int[sizeofvect];
        for (int i = 0; i < sizeofvect; i++) {
            seats[i] = vector[i];
        }
    }


    //Getters
    int getNoSeats() {
        return this->noSeats;
    }

    void getSeats() {
        if (this->noSeats != 0) {
            for (int i = 0; i < this->noSeats; i++) {
                cout << seats[i] << " ";
            }
            cout << endl;
        }
    }

    //Constructors
    Row(int noSeats) {
        setNoSeats(noSeats);
        setSeats();
    };

    Row(const int* vector,int sizeofvector) {
        setNoSeats(sizeofvector);
        setSeatsWithVector(vector,sizeofvector);
    };

    Row() {

    };

    //Overloading =
    Row& operator=(const Row& source) {
        this->noSeats = source.noSeats;
        if (this->seats == source.seats) {
            exit;
        }
        else {
            delete[] this->seats;
            this->seats = new int[source.noSeats];
            for (int i = 0; i < source.noSeats; i++) {
                this->seats[i] = source.seats[i];
            }
        }
        return *this;
    }

    //Copy CTR
    Row(const Row& r) {
        if (this->seats != nullptr) {
            delete[] this->seats;
            this->seats=nullptr;
        }
        this->seats = new int[r.noSeats];
        for (int i = 0; i < r.noSeats; i++) {
            seats[i] = r.seats[i];
        }
        this->noSeats = r.noSeats;
    }

    //Destructor
    ~Row() {
        if (this->seats != nullptr) {
            delete[] this->seats;
            this->seats = nullptr;
        }
    };
};

class Zone {
    string zoneName = "";
    int zoneTicketPrice = 0;
    int nrRows = 0;
    Row* zoneRows = nullptr;

public:
    //Setters
    void setZoneName(const string zoneName) {
        this->zoneName = zoneName;
    }

    void setZoneTicketPrice(int price) {
        this->zoneTicketPrice = price;
    }

    void addRow(const Row& r) {
        this->nrRows += 1;
        Row* copy = new Row[this->nrRows];
        copy[this->nrRows - 1] = r;
        if (this->zoneRows != nullptr) {
            for (int i = 0; i < this->nrRows - 1; i++) {
                copy[i] = this->zoneRows[i];
            }
            delete[] this->zoneRows;
            this->zoneRows = nullptr;
        }
        this->zoneRows = copy;
    }

    //Getters
    string getZoneName() {
        return this->zoneName;
    }

    int getZoneTicketPrice() {
        return this->zoneTicketPrice;
    }

    int getNrRowsForZone() {
        return this->nrRows;
    }
    
    void getZoneseats() {
        if (this->zoneRows != nullptr) {
            for (int i = 0; i < this->nrRows; i++) {
                if (zoneRows[i].getNoSeats() != 0) {
                        zoneRows[i].getSeats();
                }
                else {
                    throw exception("No seats available! Please add at least one row");
                }
            }
        }
    }

    //Constructors
    Zone(const string ZoneName, int zoneTicketPrice,Row& r){
        setZoneName(ZoneName);
        setZoneTicketPrice(zoneTicketPrice);
        addRow(r);
    }

    Zone(const string ZoneName, int zoneTicketPrice) {
        setZoneName(ZoneName);
        setZoneTicketPrice(zoneTicketPrice);
    }

    Zone() {
        
    }

    //Overloading =
    Zone& operator=(const Zone& source) {
        this->zoneName = source.zoneName;
        this->zoneTicketPrice = source.zoneTicketPrice;
        this->nrRows = source.nrRows;
        if (this->zoneRows == source.zoneRows) {
            exit;
        }
        else {
            delete[] this->zoneRows;
            this->zoneRows = new Row[source.nrRows];
            for (int i = 0; i < source.nrRows; i++) {
                this->zoneRows[i] = source.zoneRows[i];
            }
        }
        return *this;
    }

    //Copy CTR
    Zone(const Zone& z) {
        if (this->zoneRows != nullptr) {
            delete[] this->zoneRows;
            this->zoneRows = nullptr;
        }
        this->zoneName = z.zoneName;
        this->zoneTicketPrice = z.zoneTicketPrice;
        this->zoneRows = new Row[z.nrRows];
        for (int i = 0; i < z.nrRows; i++) {
            this->zoneRows[i] = z.zoneRows[i];
        }
        this->nrRows = z.nrRows;

    }

    //Destructor
    ~Zone() {
        if (this->zoneRows != nullptr) {
            delete[] this->zoneRows;
            this->zoneRows = nullptr;
        }
    }
};

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

    string getAvailableZones() {
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones; i++) {
                cout << this->zones[i].getZoneName() << " ";
            }
        }
        else {
            throw exception("No zones available! Please add at least one");
        }
    }

    void displaySeatsFromZones() {
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones; i++) {
                if (this->zones[i].getNrRowsForZone() != 0) {
                    cout << "Zone: " << i+1 << endl;
                    this->zones[i].getZoneseats();
                }
                else {
                    throw exception("Zone got zero rows.");
                }
            }
        }
    }

    // Other processing method
    //void printLocationDetails();

    //Constructors
    EventLocation(const string locationName,Zone& z) {
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