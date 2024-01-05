#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Seat {
protected:
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

    void occupySeat() {
        this->isAvailable = false;
    }

    void displaySeat() {
        if (this->isAvailable) {
            cout << this->seatNumber << " ";
        }
        else {
            cout << "X" << " ";
        }
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
    Seat(int number, bool available) {
        this->isAvailable = available;
        setSeatNumber(number);
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
protected:
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

    void buySeat(int num) {
        if (!(this->seats[num - 1].checkIfItsAvailable())) {
            throw exception("Seat already occupied.");
        }
        else if(this->noSeats != 0 && num-1 < this->noSeats && num >=1 ) {
            seats[num-1].occupySeat();
        }
        else {
            throw exception("The number of the seat on the row that you're trying to buy is non-existent.");
        }
    }

    //Constructors
    Row(int num) {
        if (num <= 0) {
            throw exception("Invalid number of seats. Enter a positive integer.");
        }
        else {
            this->noSeats = num;
            this->seats = new Seat[num];
            // Initialize seats with sequential numbers
            for (int i = 0; i < noSeats; ++i) {
                this->seats[i] = Seat(i + 1, true);
            }
        }
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
protected:
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

    void buyZoneSeat(int numRow, int numSeat) {
        if (this->zoneRows == nullptr) {
            throw exception("There are no rows in this Zone when trying to buy a seat.");
        }
        else if (numRow < 1 || numRow > this->nrRows) {
            throw exception("The number of the row in the argument of buyZoneSeat is too high or lower than 1");
        }
        else {
            this->zoneRows[numRow - 1].buySeat(numSeat);
        }
    }

    //Constructors
    Zone(const string& ZoneName, int zoneTicketPrice,Row& r){
        setZoneName(ZoneName);
        setZoneTicketPrice(zoneTicketPrice);
        addRow(r);
    }

    Zone(const string& ZoneName, int zoneTicketPrice) {
        setZoneName(ZoneName);
        setZoneTicketPrice(zoneTicketPrice);
    }

    Zone(const string& name, int price, int numRows, int numSeatsPerRow){
        if (numRows > 0) {
            this->nrRows = numRows;
        }
        else {
            throw exception("Number of rows negative or 0 when calling the Zone CTR with rows and seats");
        }
        setZoneName(name);
        setZoneTicketPrice(price);
        zoneRows = new Row[nrRows];

        for (int i = 0; i < nrRows; ++i) {
            zoneRows[i] = Row(numSeatsPerRow);
        }
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
protected:
    string locationName = "";
    int nrZones = 0;
    Zone* zones = nullptr;
public:
    EventLocation() {

    }
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

    void buyTicketFromZones(int numZone, int numRow, int numSeat) {
        if (this->zones == nullptr) {
            throw exception("There are no zones available.");
        }
        else if (numZone < 1 || numZone > this->nrZones) {
            throw exception("When trying to buy a ticket from buyTicketFromZones the zone number is either too high or lower than 1");
        }
        else {
            this->zones[numZone-1].buyZoneSeat(numRow, numSeat);
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
        if (ev.locationName != "") {
            setLocationName(ev.locationName);
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
protected:
    char* eventName = nullptr;
    string eventDate = "";
    string eventTime = "";
    EventLocation location;

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

    void printLocationDetails() {
        this->location.printLocationDetails();
    }

    void printEventSeats() {
        this->location.displaySeatsFromZones();
    }

    void buySeatFromEvent(int numZone,int numRow,int numSeat) {
        this->location.buyTicketFromZones(numZone,numRow,numSeat);
    }



    //Constructors
    EventDetails(const char* name, const string& datestr, const string& timestr, const EventLocation& location1): location(location1){
        setEventName(name);
        setEventDate(datestr);
        setEventTime(timestr);
    }

    EventDetails(const char* name, const string& datestr,const EventLocation& location1):location(location1){
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
    EventDetails(const EventDetails& source): location(source.location){
        setEventDate(source.eventDate);
        setEventTime(source.eventTime);
        if (this->eventName == source.eventName) {
            exit;
        }
        else if (!source) {
            delete[] this->eventName;
            this->eventName = new char[strlen(source.eventName) + 1];
            strcpy_s(this->eventName, strlen(source.eventName) + 1, source.eventName);
        }
        else {
            throw exception("Trying to copy from a source with the dynamic attribute eventName equal to a nullptr(EventDetails Copy CTR)");
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
protected:
    const int uniqueId;
    char* ticketType = nullptr;
    string holderName = "";
    EventDetails details;

public:
    static int ticketsSold;

    static int generateRandomNumber() { 
        return rand();
    }

    void printTicketDetails() {
        cout << "Unique id of the ticket:" << this->uniqueId << endl;
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
            strcpy_s(this->ticketType, strlen(newType) + 1, newType);
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

    int getId() {
        return this->uniqueId;
    }

    Ticket(int id,const char* type,const EventDetails& det) : uniqueId(++id), details(det) {
        setTicketType(type);;
    }

    Ticket(int id,const char* type, const string& holdername,const EventDetails& det) :uniqueId(++id),details(det) {
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

    Ticket& operator=(const Ticket& source){
        if (this->ticketType == source.ticketType) {
            exit;
        }
        this->holderName = source.holderName;
        this->details = source.details;
        if (!source) {
            delete[] this->ticketType;
            this->ticketType = new char[strlen(source.ticketType) + 1];
            strcpy_s(this->ticketType, strlen(source.ticketType) + 1, source.ticketType);
        }
        else {
            throw exception("Trying to copy from a source with the dynamic attribute eventName equal to a nullptr(EventDetails Copy CTR)");
        }
        return *this;
    }

    Ticket(const Ticket& source):uniqueId(source.uniqueId), details(source.details){
        this->holderName = source.holderName;
        if (!source) {
            delete[] this->ticketType;
            this->ticketType= new char[strlen(source.ticketType) + 1];
            strcpy_s(this->ticketType, strlen(source.ticketType) + 1, source.ticketType);
        }
        else {
            throw exception("Trying to copy from a source with the dynamic attribute eventName equal to a nullptr(EventDetails Copy CTR)");
        }
    }

    ~Ticket() {
        if (this->ticketType != nullptr) {
            delete[] this->ticketType;
            this->ticketType = nullptr;
        }
    }
};

class SoldTickets {
protected:
 vector <Ticket> sold_tickets;
public:

    int getSize() {
        return sold_tickets.size();
    }

    void addTicket(Ticket& ticket) {
        sold_tickets.push_back(ticket);
    }

    bool ticketValidator(int id) {
        for (int i = 0; i < this->sold_tickets.size(); i++) {
            if (sold_tickets[i].getId() == id)
                return true;
        }
        return false;
    }
    
    void printSoldTickets() {
        for (int i = 0; i < this->sold_tickets.size(); i++) {
        cout<< sold_tickets[i].getId()<<" ";
        }
    }
};

// Abstract ticket factory
class TicketFactory {
protected:
    SoldTickets& currentcashier;
public:
    TicketFactory(SoldTickets& soldTicketsRef) : currentcashier(soldTicketsRef) {};
    virtual Ticket generateTicket(const string& name,const EventDetails& details) = 0;
    virtual ~TicketFactory() = default;
};

// Concrete factory for Football Tickets
class FootballTicketFactory : public TicketFactory {
public:
    FootballTicketFactory(SoldTickets& soldTicketsRef) : TicketFactory(soldTicketsRef) {};
    Ticket generateTicket(const string& name, const EventDetails& details) override {
        Ticket::ticketsSold++;
        Ticket ticket(Ticket::generateRandomNumber(), "Football", name,details);
        currentcashier.addTicket(ticket);
        return ticket;
    }
};

// Concrete factory for Movie Tickets
class MovieTicketFactory : public TicketFactory {
public:
    MovieTicketFactory(SoldTickets& soldTicketsRef) : TicketFactory(soldTicketsRef) {};
    Ticket generateTicket(const string& name, const EventDetails& details) override {
        Ticket::ticketsSold++;
        Ticket ticket(Ticket::generateRandomNumber(), "Movie", name, details);
        currentcashier.addTicket(ticket);
        return ticket;
    }
};

// Concrete factory for Theater Tickets
class TheaterTicketFactory : public TicketFactory {
public:
    TheaterTicketFactory(SoldTickets& soldTicketsRef) : TicketFactory(soldTicketsRef) {};
    Ticket generateTicket(const string& name,const EventDetails& details) override {
        Ticket::ticketsSold++;
        Ticket ticket(Ticket::generateRandomNumber(), "Theater", name,details);
        currentcashier.addTicket(ticket);
        return ticket;
    }
};

class TicketingSystem {
protected:
    vector<EventDetails> events;
public:

    void runTicketingSystem(int argc, char* argv[]) {
        if (argc != 2) {
            cerr << "Usage: " << argv[0] << " <file_with_data.txt>" << endl;
            exit(EXIT_FAILURE);
        }
        string filename = argv[1];
    }

    void loadEventData(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            exit(EXIT_FAILURE);
        }
        file.close();
    }

    void menu() {
        char choice;

        do {
            std::cout << "[1] Buy a ticket from an existing event.\n";
            std::cout << "[2] Validate a ticket.\n";
            std::cout << "[3] Create a custom ticket.\n";
            std::cout << "[4] Quit Program\n\n";
            std::cout << "Enter Your Choice :=> ";
            std::cin >> choice;

            system("cls");

            if (choice == '1') {
                char subChoice1;
                do {
                    std::cout << "\nSub-menu for buying a ticket:\n";
                    std::cout << "[1] View available events.\n";
                    std::cout << "[2] Select an event to buy a ticket.\n";
                    std::cout << "[3] Return to the main menu.\n\n";
                    std::cout << "Enter Your Choice :=> ";
                    std::cin >> subChoice1;
                    system("cls");

                    if (subChoice1 == '1') {
                        std::cout << "Viewing available events...\n";
                    }
                    else if (subChoice1 == '2') {
                        std::cout << "Selecting an event to buy a ticket...\n";
                    }
                    else if (subChoice1 == '3') {
                        std::cout << "Returning to the main menu...\n";
                        break;
                    }
                    else {
                        std::cout << "Invalid choice. Please enter a valid option.\n";
                    }
                } while (true);

            }
            else if (choice == '2') {
                std::cout << "\nSub-menu for validating a ticket:\n";
                std::cout << "[1] Enter the ticket code manually.\n";
                std::cout << "[2] Return to the main menu.\n\n";
                std::cout << "Enter Your Choice :=> ";

                char subChoice2;
                std::cin >> subChoice2;
                system("cls");

                 if (subChoice2 == '1') {
                    std::cout << "Entering the ticket code manually...\n";
                }
                else if (subChoice2 == '2') {
                    std::cout << "Returning to the main menu...\n";
                }
                else {
                    std::cout << "Invalid choice. Please enter a valid option.\n";
                }

            }
            else if (choice == '3') {
                std::cout << "Creating a custom ticket...\n";
            }
            else if (choice == '4') {
                std::cout << "Quitting the program...\n";
            }
            else {
                std::cout << "Invalid choice. Please enter a valid option.\n\n";
            }

        } while (choice != '4');
    }
};