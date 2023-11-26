#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Seat {
    int seatNumber = 0;
    bool isAvailable = true;
    bool isStandard = false;
    bool isForDisabled = false;
    bool isBlocked = false;
    bool isChosen = false;
    bool isVIP = false;

public:
    //Setters
    void setSeatNumber(int number) {
        if (number >= 0) {
            this->seatNumber = number;
        }
        else
            throw exception("The number you entered for the seat number is not a positive int.");
    }

    void setIsVIP(bool itis) {
        if (itis) {
            this->isVIP = true;
            this->isStandard = false;
        }
        else
            this->isStandard = true;
    }

    void setIsStandard(bool itis) {
        if (itis) {
            this->isVIP = false;
            this->isStandard = true;
        }
    }

    void isForDisable() {
        this->isForDisabled = true;
    }
    
    void isNotForDisabled() {
        this->isForDisabled = false;
    }

    void blockSeat(){
        this->isBlocked = true;
        this->isAvailable = false;
    }

    void unblockSeat() {
        this->isBlocked = false;
        this->isAvailable = true;
    }

    void chooseSeat() {
        this->isChosen = true;
    }
    
    //Getters
    int getSeatNumber() {
        return this->seatNumber;
    }

    bool checkIfItsAvailable() {
        return this->isAvailable;
    }
    
    bool checkIfItsForDisabled() {
        return this->isForDisabled;
    }

    bool checkIfItsBlocked() {
        return this->isBlocked;
    }


    void displaySeat() {
        cout << "[" << this->seatNumber << "]" << " ";
    }
  
    //Overloading ! operator
    friend bool operator!(const Seat& s) {
        if (s.seatNumber >= 0) {
            return true;
        }
        else {
            return false;
        }
    }

    //Constructors
    Seat(int number, bool available, bool isVip,bool blocked) {
        this->isAvailable = available;
        setSeatNumber(number);
        setIsVIP(isVip);
        if (blocked) {
            blockSeat();
        }
    }

    Seat(int number, bool available, bool isVip) {
        this->isAvailable = available;
        setSeatNumber(number);
        setIsVIP(isVip);
    }

    //Overloading = operator
    Seat& operator=(const Seat& source) {
        if (this->seatNumber == source.seatNumber) {
            exit;
        }
        else if (!source) {
            this->seatNumber = source.seatNumber;
            this->isAvailable = source.isAvailable;
            this->isStandard = source.isStandard;
            this->isForDisabled = source.isForDisabled;
            this->isBlocked = source.isBlocked;
            this->isChosen = source.isChosen;
        }
        else {
            throw exception("Source seat object when passed in = has a negative seat number.");
        }
        return *this;
    }

    //Copy CTR
    Seat(const Seat& source) {
        if (this->seatNumber == source.seatNumber) {
            return;
        }
        if (!source) {
            this->seatNumber = source.seatNumber;
            this->isAvailable = source.isAvailable;
            this->isStandard = source.isStandard;
            this->isForDisabled = source.isForDisabled;
            this->isBlocked = source.isBlocked;
            this->isChosen = source.isChosen;
        }
        else {
            throw exception("Source seat object when passed in the copy ctr has a negative seat number.");
        }
    }


    Seat() {

    }

};


class Row {
    int noSeats = 0;
    Seat* seats = nullptr;

public:
    //Setters
    void setNoSeats(int nrseats) {
        if (nrseats < 0 || nrseats == 0) {
            throw exception("Invalid number of seats, enter an integer number bigger than 0.");
        }
        this->noSeats = nrseats;
    }

    void addSeats(const Seat& s) {
        if (!s) {
            this->noSeats += 1;
            Seat* copy = new Seat[this->noSeats];
            copy[this->noSeats - 1] = s;
            if (this->seats != nullptr) {
                for (int i = 0; i < this->noSeats - 1; i++) {
                    copy[i] = this->seats[i];
            }
                delete[] this->seats;
                this->seats = nullptr;
            }
            this->seats = copy;
        }
        else {
            throw exception("Trying to add a Row object with the seats attribute = to a nullptr");
        }
    }

    void setSeatsWithVectorOfSeats(const Seat* vector,int sizeofvect) {
        if (sizeofvect <= 0) {
            throw exception("Size of vector 0 or negative, enter a valid one.");
        }

        if (this->seats != nullptr) {
            delete[] this->seats;
            this->seats = nullptr;
        }
        seats = new Seat[sizeofvect];
        for (int i = 0; i < sizeofvect; i++) {
            seats[i] = vector[i];
        }
    }


    //Getters
    int getNoSeats() {
        return this->noSeats;
    }
    
    
    Seat* getSeats() {
        if (this->seats != nullptr) {
            Seat* copy = new Seat[this->noSeats];
            for (int i = 0; i < this->noSeats; i++) {
                copy[i] = this->seats[i];
            }
            return copy;
        }
        else {
            throw exception("No seats in this row.");
        }
    }


    //Displaying attribute function
    void displaySeats() {
        if (this->noSeats != 0) {
            for (int i = 0; i < this->noSeats; i++) {
                seats[i].displaySeat();
            }
            cout << endl;
        }
    }

    //Constructors
    Row(const Seat& s) {
        addSeats(s);
    };

    Row(const Seat* vector,int sizeofvector) {
        setNoSeats(sizeofvector);
        setSeatsWithVectorOfSeats(vector,sizeofvector);
    };

    Row() {

    };

    //Overloading !
    friend bool operator!(const Row& r) {
        if (r.seats != nullptr) {
            return true;
        }
        else
            return false;
    }

    //Overloading =
    Row& operator=(const Row& source) {
        this->noSeats = source.noSeats;
        if (this->seats == source.seats) {
            exit;
        }
        else if(!source){
            delete[] this->seats;
            this->seats = new Seat[source.noSeats];
            for (int i = 0; i < source.noSeats; i++) {
                this->seats[i] = source.seats[i];
            }
        }
        else {
            throw exception("Source row object when passed in = has a nullpointer for the seats");
        }
        return *this;
    }

    //Copy CTR
    Row(const Row& r) {
        if (this->seats == r.seats) {
            return;
        }
        if (!r) {
            this->seats = new Seat[r.noSeats];
            for (int i = 0; i < r.noSeats; i++) {
                seats[i] = r.seats[i];
            }
            this->noSeats = r.noSeats;
        }
        else {
            throw exception("Source row object when passed in the copy ctr has a nullpointer for the seats");
        }
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
        if (zoneName.length() > 3 || zoneName.length() < 20) {
            this->zoneName = zoneName;
        }
        else throw exception("Lenght of zoneName < 3 or zoneName > 20, enter a valid one.");
    }

    void setZoneTicketPrice(int price) {
        if (price > 0) {
            this->zoneTicketPrice = price;
        }
        else throw exception("Price for ticket for this zone < 0 || == 0, enter a valid one.");
    }

    void addRow(const Row& r) {
        if (!r) {
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
        else {
            throw exception("Trying to add a Row object with the seats attribute = to a nullptr");
        }
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
    

    Row* getRowsFromZone() {
        if (this->zoneRows != nullptr) {
            Row* copy = new Row[this->nrRows];
            for (int i = 0; i < this->nrRows; i++) {
                copy[i] = this->zoneRows[i];
            }
            return copy;
        }
        else {
            throw exception("No rows in this zone,enter at least one");
        }
    }

    //Func to display attributes
    void displayZoneseats() {
        if (this->zoneRows != nullptr) {
            for (int i = 0; i < this->nrRows; i++) {
                if (zoneRows[i].getNoSeats() != 0) {
                        zoneRows[i].displaySeats();
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

    //Overloading !
    friend bool operator!(const Zone& z) {
        if (z.zoneRows != nullptr) {
            return true;
        }
        else
            return false;
    }

    //Overloading =
    Zone& operator=(const Zone& source) {
        this->zoneName = source.zoneName;
        this->zoneTicketPrice = source.zoneTicketPrice;
        this->nrRows = source.nrRows;
        if (this->zoneRows == source.zoneRows) {
            exit;
        }
        else if(!source){
            delete[] this->zoneRows;
            this->zoneRows = new Row[source.nrRows];
            for (int i = 0; i < source.nrRows; i++) {
                this->zoneRows[i] = source.zoneRows[i];
            }
        }
        else {
            throw exception("Source for zone in = operator has the dynamic rows attribute equal to a nullptr.");
        }
        return *this;
    }

    //Copy CTR
    Zone(const Zone& z) {
        if (this->zoneRows == z.zoneRows) {
            return;
        }
        if (!z) {
            this->zoneName = z.zoneName;
            this->zoneTicketPrice = z.zoneTicketPrice;
            this->zoneRows = new Row[z.nrRows];
            for (int i = 0; i < z.nrRows; i++) {
                this->zoneRows[i] = z.zoneRows[i];
            }
            this->nrRows = z.nrRows;
        }
        else {
            throw exception("Source for zone in copy ctr has the dynamic rows attribute equal to a nullptr.");
        }
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
        if (!z) {
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
        else throw exception("Trying to add a zone with the zoneRows equal to a nullptr");
    }

    // Getters
    string getLocationName() {
        return this->locationName;
    }


    int getNumZones() {
        return this->nrZones;
    }

    Zone* getZones() {
        if (this->zones !=nullptr) {
            Zone* copy = new Zone[this->nrZones];
            for (int i = 0; i < this->nrZones; i++) {
                copy[i] = zones[i];
            }
            return copy;
        }
        else {
            throw exception("No available zones to get.");
        }
    }


    void getAvailableZoneNames() {
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones; i++) {
                cout << this->zones[i].getZoneName() << "\t";
            }
            cout << endl;
        }
        else {
            throw exception("No zones available! Please add at least one");
        }
    }

    //Displaying attributes methods
    void displaySeatsFromZones() {
        if (this->zones != nullptr) {
            for (int i = 0; i < this->nrZones; i++) {
                if (this->zones[i].getNrRowsForZone() != 0) {
                    cout << "Zone: " << i+1 << endl;
                    this->zones[i].displayZoneseats();
                }
                else {
                    throw exception("Zone got zero rows.");
                }
            }
        }
        else {
            cout << "No zones to display seats from." << endl;
        }
    }

    void printLocationDetails() {
        cout <<"The location name is: " << getLocationName()<< endl;
        cout << "The location has " << getNumZones() << " zones: ";
        getAvailableZoneNames();
    }

    //Constructors
    EventLocation(const string locationName,Zone& z) {
        setLocationName(locationName);
        addZone(z);
    }

    EventLocation(const string locationName) {
        setLocationName(locationName);

    }

    EventLocation() {

    }

    //Overloading !;
    friend bool operator!(const EventLocation& ev) {
        if (ev.zones != nullptr)
            return true;
        else
            return false;
    }
    
    //Overloading the "=" operator
    EventLocation& operator=(const EventLocation& source) {
        this->locationName = source.locationName; 
        if (this->zones == source.zones) {
            exit;
        }
        else if(!source){
                delete[] this->zones;
                this->zones = new Zone[source.nrZones];
                for (int i = 0; i < source.nrZones; i++) {
                    this->zones[i] = source.zones[i];
                }
                this->nrZones = source.nrZones;
        }
        else {
            throw exception("Trying to assing with = a source with the dynamic attribute zones equal to a nullptr");
            }
        return *this;
    }

    //Copy CTR
    EventLocation(const EventLocation& ev) {
        if (this->zones == ev.zones) {
            return;
        }
        if (!ev) {
            this->locationName = ev.locationName;
            if (ev.nrZones != 0) {
                this->zones = new Zone[ev.nrZones];
                for (int i = 0; i < ev.nrZones; i++) {
                    this->zones[i] = ev.zones[i];
                }
                this->nrZones = ev.nrZones;
            }
        }
        else {
            throw exception("Trying to copy with the copy ctr an object with the dynamic attribute zones equal to a nullptr.");
        }
    }

    //Destructor
    ~EventLocation() {
        if (zones != nullptr) {
            delete[] this->zones;
            this->zones = nullptr;
        }
    }
};

class EventDetails {
    char* eventName = nullptr;
    string eventDate = "";
    string eventTime = "";
    
    EventDetails() {
    }
public:

    //Check function for date time format hh:mm
    bool isValidTimeFormat(const std::string& timeStr) {
        if (timeStr.size() != 5 || timeStr[2] != ':') {
            return false;
        }

        for (int i : {0, 1, 3, 4}) {
            if (!std::isdigit(timeStr[i])) {
                return false;
            }
        }

        int hour = std::stoi(timeStr.substr(0, 2));
        int minute = std::stoi(timeStr.substr(3, 2));

        if (minute < 0 || minute > 59 || hour < 0 || hour > 23 ) {
            return false;
        }

        return true;
    }

    //Check function for date format string dd-mm-yyyy
    bool isValidDateFormat(const std::string& value){
        if (value.size() != 10 || value[2] != '-' || value[5] != '-') {
            return false;
        }

        for (int i : {0, 1, 3, 4, 6, 7, 8, 9}) {
            if (!std::isdigit(value[i])) {
                return false;
            }
        }

        int day = std::stoi(value.substr(0, 2));
        int month = std::stoi(value.substr(3, 2));
        int year = std::stoi(value.substr(6, 4));

        if (month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        return true;
    }

    //Setters
    void setEventName(const char* newName) {
        if (this->eventName != nullptr) {
            delete[] this->eventName;
            this->eventName = nullptr;
        }
        this->eventName = new char[strlen(newName) + 1];
        strcpy_s(this->eventName, strlen(newName) + 1, newName);
    }

    void setEventDate(const string& newDate) {
        if (isValidDateFormat(newDate)) {
            this->eventDate = newDate;
        }
        else
            throw exception("The string that you wanted to initialize eventDate with has an invalid date format, enter a dd-mm-yyyy one.");
    }

    void setEventTime(const string& newTime) {
        if (isValidTimeFormat(newTime)) {
            this->eventTime = newTime;
        }
        else
            throw exception("The string that you wanted to initialize eventTime with has an invalid time format, enter a hh:mm one.");
    }

    //Getter
    char* getEventName() {
        if (this->eventName != nullptr) {
            char* copy = new char[strlen(this->eventName) + 1];
            strcpy_s(copy, strlen(this->eventName) + 1, this->eventName);
            return copy;
        }
        else {
            throw exception("No eventName to get.");
        }
    }
    
    string getEventDate() {
        return this->eventDate;
    }

    string getEventTime(){
        return this->eventTime;
    }

    //Constructors
    EventDetails(const char* name, const string& datestr, const string& timestr) {
        setEventName(name);
        setEventDate(datestr);
        setEventTime(timestr);
    }

    EventDetails(const char* name, const string& datestr) {
        setEventName(name);
        setEventDate(datestr);
    }

    //Overloading ! operator
    friend bool operator!(const EventDetails& s) {
        if (s.eventName != nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    //Overloading the "=" operator
    EventDetails& operator=(const EventDetails& source) {
        this->eventDate = source.eventDate;
        this->eventTime = source.eventTime;
        if (this->eventName == source.eventName) {
            exit;
        }
        else if (!source) {
            delete[] this->eventName;
            this->eventName = new char[strlen(source.eventName) + 1];
            strcpy_s(this->eventName,strlen(source.eventName) + 1, source.eventName);
        }
        else {
            throw exception("Trying to assing with = a source with the dynamic attribute eventName equal to a nullptr");
        }
        return *this;
    }

    //Copy CTR
    EventDetails(const EventDetails& source) {
        if (this->eventName == source.eventName) {
            return;
        }
        if (!source) {
            this->eventDate = source.eventDate;
            this->eventTime = source.eventTime;
            this->eventName = new char[strlen(source.eventName) + 1];
            strcpy_s(this->eventName, strlen(source.eventName) + 1, source.eventName);
        }
        else {
            throw exception("Source for eventDetails in copy ctr has the dynamic eventName attribute equal to a nullptr.");
        }
    }

    //Destructor
    ~EventDetails() {
        if (this->eventName != nullptr) {
            delete[] this->eventName;
            this->eventName = nullptr;
        }
    }
};

class Ticket {
    const int uniqueIdCounter;
    char* ticketType = nullptr;
    string holderName = "";

public:
    static int ticketsSold;

    int generateRandomNumber() {
        time_t currentTime = time(nullptr);
        srand(static_cast<unsigned int>(currentTime));
        int randomNumber = rand();
        return randomNumber;
    }

    void printTicketDetails() {
        cout << "Unique id of the ticket:" << this->uniqueIdCounter << endl;
        cout << "Ticket type: " << this->ticketType << endl;
        cout << "Holder name: " << this->holderName<< endl;
    }

    //Setters
    void setTicketType(const char* newType) {
        if (strlen(newType) > 0 && strlen(newType) < 10) {
            if (this->ticketType != nullptr) {
                delete[] this->ticketType;
                this->ticketType = nullptr;
            }
            this->ticketType = new char[strlen(newType) + 1];
        }
        else
            throw exception("The ticket type you are trying to set is invalid.");
    }

    void setHoldersName(const string& name) {
        if (name.length() > 3 || name.length() < 20) {
            this->holderName = name;
        }
        else throw exception("Lenght of holdersName < 3 or holdersName > 20, enter a valid one.");
    }

    //Getters
    char* getTicketType() {
        if (this->ticketType != nullptr) {
            char* copy = new char[strlen(this->ticketType) + 1];
            strcpy_s(copy, strlen(this->ticketType) + 1, this->ticketType);
            return copy;
        }
        else {
            throw exception("No ticketType to get.");
        }
    }

    string getHoldersName() {
        return this->holderName;
    }

    Ticket(const char* type) :uniqueIdCounter(generateRandomNumber()) {
        setTicketType(type);
    }

    Ticket(const char* type, const string& holdername) :uniqueIdCounter(generateRandomNumber()) {
        setTicketType(type);
        setHoldersName(holdername);
    }

    friend bool operator!(const Ticket& s) {
        if (s.ticketType != nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    ~Ticket() {
        if (this->ticketType != nullptr) {
            delete[] this->ticketType;
            this->ticketType = nullptr;
        }
    }
};