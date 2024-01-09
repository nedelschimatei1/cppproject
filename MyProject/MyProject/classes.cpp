#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <cstring>
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

    void occupySeat(bool isvip) {
        this->isAvailable = false;
        if (isvip) {
            this->isStandard = false;
            this->isVIP = true;
        }
    }

    void displaySeat() {
        if (this->isAvailable) {
            cout << this->seatNumber << " ";
        }
        else if (this->isVIP) {
            cout << "V" << " ";
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

    };

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
            cout << "\t";
            for (int i = 0; i < this->noSeats; i++) {
                seats[i].displaySeat();
            }
            cout << endl;
        }
    }

    void buySeat(int num, bool isviporgen) {
        if (!(this->seats[num - 1].checkIfItsAvailable())) {
            throw exception("Seat already occupied.");
        }
        else if(this->noSeats != 0 && num-1 < this->noSeats && num >=1 ) {
            seats[num-1].occupySeat(isviporgen);
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
    void setZoneName(const string& zoneName) {
        char namechar = zoneName.at(0);
        if (zoneName.length() > 3 || zoneName.length() < 20 && !isupper(namechar)){
            this->zoneName = zoneName;
        }
        else throw exception("Lenght of zoneName < 3 or zoneName > 20 or the first letter is not a capital one, enter a valid one.");
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

    void buyZoneSeat(int numRow, int numSeat, bool isvip) {
        if (this->zoneRows == nullptr) {
            throw exception("There are no rows in this Zone when trying to buy a seat.");
        }
        else if (numRow < 1 || numRow > this->nrRows) {
            throw exception("The number of the row in the argument of buyZoneSeat is too high or lower than 1");
        }
        else {
            this->zoneRows[numRow - 1].buySeat(numSeat,isvip);
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
    void setLocationName(const string& location) {
        char localstring = location[0];
        if (location.length() < 3 || location.length() > 10 && !isupper(localstring)){
            throw exception("You entered an invalid string please enter another valid one (minimum 3 characters, maximum 10, capital first letter, for ex:`BUC`");
        }
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
                cout <<"["<<i+1<<"]"<<this->zones[i].getZoneName() << "\t";
            }
            cout << endl;
        }
        else {
            throw exception("No zones available! Please add at least one");
        }
    }

    string getZoneNameWithIndex(int index) {
        return this->zones[index].getZoneName();
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

    void displaySeatsFromZone(int numzone) {
        if (this->zones != nullptr && numzone <= this->nrZones && numzone>=0) {
            this->zones[numzone].displayZoneseats();
        }
        else {
            throw exception("That zone doesn't exist");
        }
    }

    void buyTicketFromZones(int numZone, int numRow, int numSeat,bool isviporgen) {
        if (this->zones == nullptr) {
            throw exception("There are no zones available.");
        }
        else if (numZone < 1 || numZone > this->nrZones) {
            throw exception("When trying to buy a ticket from buyTicketFromZones the zone number is either too high or lower than 1");
        }
        else {
            this->zones[numZone-1].buyZoneSeat(numRow, numSeat,isviporgen);
        }
    }

    virtual void printLocationDetails() {
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
    static bool isValidTimeFormat(const std::string& timeStr) {
        if (timeStr.size() != 5 || timeStr[2] != '-') {
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
    static bool isValidDateFormat(const string& value){
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
        if (EventDetails::isValidDateFormat(newDate)) {
            this->eventDate = newDate;
        }
        else
            throw exception("The string that you wanted to initialize eventDate with has an invalid date format, enter a dd-mm-yyyy one.");
    }

    void setEventTime(const string& newTime) {
        if (EventDetails::isValidTimeFormat(newTime)) {
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

    string getLocationName() {
        return this->location.getLocationName();
    }

    string getEventZoneWithIndex(int index) {
        return this->location.getZoneNameWithIndex(index);
    }

    int getNoZonesFromEvent() {
        return this->location.getNumZones();
    }

    void printLocationDetails() {
        this->location.printLocationDetails();
    }

    void printEventSeats() {
        this->location.displaySeatsFromZones();
    }

    void printEventZoneSeats(int numzone) {
        this->location.displaySeatsFromZone(numzone-1);
    }

    void buySeatFromEvent(int numZone,int numRow,int numSeat,bool isviporgen) {
        this->location.buyTicketFromZones(numZone,numRow,numSeat,isviporgen);
    }

    void getAvailableZoneNames() {
        this->location.getAvailableZoneNames();
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

    virtual void printTicketDetails() {
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
 vector <int> sold_tickets;
public:

    int getSize() {
        return sold_tickets.size();
    }

    void addTicket(int id) {
        sold_tickets.push_back(id);
    }

    bool ticketValidator(int id) {
        for (int i = 0; i < this->sold_tickets.size(); i++) {
            if (sold_tickets[i] == id)
                return true;
        }
        return false;
    }
    
    void printSoldTickets() {
        for (int i = 0; i < this->sold_tickets.size(); i++) {
        cout<< sold_tickets[i]<<" ";
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
class VIPTicketFactory : public TicketFactory {
public:
    VIPTicketFactory(SoldTickets& soldTicketsRef) : TicketFactory(soldTicketsRef) {};
    Ticket generateTicket(const string& name, const EventDetails& details) override {
        Ticket::ticketsSold++;
        Ticket ticket(Ticket::generateRandomNumber(), "VIP", name,details);
        currentcashier.addTicket(ticket.getId());
        return ticket;
    }
};

// Concrete factory for Movie Tickets
class GeneralTicketFactory : public TicketFactory {
public:
    GeneralTicketFactory(SoldTickets& soldTicketsRef) : TicketFactory(soldTicketsRef) {};
    Ticket generateTicket(const string& name, const EventDetails& details) override {
        Ticket::ticketsSold++;
        Ticket ticket(Ticket::generateRandomNumber(), "General", name, details);
        currentcashier.addTicket(ticket.getId());
        return ticket;
    }
};

class TicketingSystem {
protected:
    vector<EventDetails> events;
    vector<SoldTickets> cashiers;
public:
    
    static bool is_number(const std::string& s){
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    void addSampleCashier(const SoldTickets& cashier) {
        this->cashiers.push_back(cashier);
    }

    void addSampleEvent(const EventDetails& sample) {
        this->events.push_back(sample);
    }

    void loadBinary(const string& file) {
        ifstream file1(file, ios::binary);
        if (file1.is_open()) {
            int value;
            while (file1.read((char*)&value, sizeof(int))) {
                this->cashiers[0].addTicket(value);
            }
            file1.close();
        }
    }

    static void writeBinary(const string& file, int id) {
        ofstream file1(file, ios::out | ios::binary | ios::app);
        if (file1.is_open()) {
            file1.write((char*)&id, sizeof(int));
            file1.close();
        }
    }

    void loadEventData(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string zoneName;
            file >> zoneName;
            int ticketprice;
            file >> ticketprice;
            int nrRows;
            file >> nrRows;
            int nrSeats;
            file >> nrSeats;
            string eventlocation;
            file >> eventlocation;
            string eventName;
            file >> eventName;
            string eventDate;
            file >> eventDate;
            string eventTime;
            file >> eventTime;
            Zone zone(zoneName, ticketprice, nrRows, nrSeats);
            EventLocation location(eventlocation, zone);
            char* newname = new char[eventName.length() + 1];
            strcpy_s(newname, eventName.length() + 1,eventName.c_str());
            EventDetails event1(newname, eventDate, eventTime,location);
            this->events.push_back(event1);
            file.close();
        }
        else {
            cout << "The file is not in this directory." << endl;
        }
    }

    void menu() {
         string choice;
         system("cls");
         do {
             cout << "\tMain Menu \n";
             cout << "[1] Buy a ticket from an existing event.\n";
             cout << "[2] Validate a ticket.\n";
             cout << "[3] Create a custom event.\n";
             cout << "[4] Quit Program\n\n";
             cout << "Enter Your Choice :=> ";
             bool boughtTicket = false;
             cin >> choice;
             system("cls");
             if (choice[0] == '1' && isdigit(choice[0]) && choice.length() == 1) {
                 string subChoiceEvents;
                 do {
                     cout << "Sub-menu for selecting an event\n\n";
                     for (int i = 0; i < this->events.size(); i++) {
                         cout << "[" << i + 1 << "]" << " Event : " << this->events[i].getEventName() << " " << this->events[i].getEventDate() << " " << this->events[i].getEventTime() << " " << this->events[i].getLocationName() << endl;
                     }
                     cout << "\nPress the number of an existing event or press q to quit and go to the main menu\n\n";
                     cout << "Enter Your Choice :=> ";
                     cin >> subChoiceEvents;
                     int intformchoice = int(subChoiceEvents[0]) - '0';
                     system("cls");
                     if (subChoiceEvents.length()==1 && isdigit(subChoiceEvents[0])&& intformchoice>0 && intformchoice <= this->events.size()) {
                         string subChoiceZone;
                         do {
                             cout << "You selected event : " << this->events[intformchoice - 1].getEventName() << " " << this->events[intformchoice - 1].getEventDate() << " " << this->events[intformchoice - 1].getEventTime() << " " << this->events[intformchoice - 1].getLocationName() << endl << endl;
                             cout << "This event has " << this->events[intformchoice - 1].getNoZonesFromEvent() << " zones: ";
                             this->events[intformchoice - 1].getAvailableZoneNames();
                             cout << "\nPress the number of an existing zone or press q to quit and go to the event submenu\n\n";
                             cout << "Enter Your Choice :=> ";
                             cin >> subChoiceZone;
                             int intFormSubChoiceZone = int(subChoiceZone[0]) - '0';

                             system("cls");
                             if (subChoiceZone.length()==1 && isdigit(subChoiceZone[0]) && intFormSubChoiceZone>0 && intFormSubChoiceZone <= this->events[intformchoice - 1].getNoZonesFromEvent()) {
                                 string subChoiceRow;
                                 string subChoiceSeat;
                                 do {
                                     cout << "\nThe available rows with the seats :\n";
                                         this->events[intformchoice - 1].printEventZoneSeats(intFormSubChoiceZone);
                                     cout << "Enter the number of the row that you want to be in (or press q to exit):\n ";
                                     cin >> subChoiceRow;
                                     cout << "Enter the number of the seat you want to buy (or press q to exit): ";
                                     cin >> subChoiceSeat;
                                     int intFormSubChoiceRow = int(subChoiceRow[0]) - '0';
                                     int intFormSubChoiceSeat = int(subChoiceSeat[0]) - '0';
                                     system("cls");

                                     if (isdigit(subChoiceRow[0]) && isdigit(subChoiceSeat[0]) && intFormSubChoiceRow > 0 && intFormSubChoiceSeat > 0) {
                                         try {
                                             bool isvip = false;
                                             bool isgen = false;
                                             string subChoiceVipOrGen;
                                             do {
                                                 cout << "Choose: [1]General [2]VIP \n\n";
                                                 cout << "Enter Your Choice :=> ";
                                                 cin >> subChoiceVipOrGen;
                                                 if (subChoiceVipOrGen[0] == '1') {
                                                     cout << "\nYou chose the General Ticket\n";
                                                     isgen = true;
                                                     system("pause");
                                                     system("cls");
                                                     break;
                                                 }
                                                 else if (subChoiceVipOrGen[0] == '2') {
                                                     cout << "\nYou chose the VIP Ticket\n";
                                                     isvip = true;
                                                     system("pause");
                                                     system("cls");
                                                     break;
                                                 }
                                                 else if (subChoiceVipOrGen[0] == '-') {
                                                     cout << "Invalid choice. The first input character is not a number. Please enter a valid option.\n\n";
                                                     system("pause");
                                                     system("cls");
                                                 }
                                                 else if (subChoiceVipOrGen.length() != 1) {
                                                     cout << "Invalid choice. You entered more than one character as an input. Please enter a valid option.\n\n";
                                                     system("pause");
                                                     system("cls");
                                                 }
                                                 else {
                                                     cout << "Invalid choice. Please enter a valid option.\n\n";
                                                     system("pause");
                                                     system("cls");
                                                 }
                                             } while (isvip == false&& isgen ==false);
                                             string name;
                                             string ticketype;
                                             cout << "Enter the customer's full name:"<<endl;
                                             cin >> name;
                                             int id;
                                             if (isvip) {
                                                 this->events[intformchoice - 1].buySeatFromEvent(intFormSubChoiceZone, intFormSubChoiceRow, intFormSubChoiceSeat,isvip);
                                                 VIPTicketFactory vipticketfactory(this->cashiers[0]);
                                                 Ticket ticket = vipticketfactory.generateTicket(name, this->events[intformchoice - 1]);
                                                 id = ticket.getId();
                                                 TicketingSystem::writeBinary("binary.dat", id);
                                                 ticketype = ticket.getTicketType();
                                             }
                                             else {
                                                 this->events[intformchoice - 1].buySeatFromEvent(intFormSubChoiceZone, intFormSubChoiceRow, intFormSubChoiceSeat, false);
                                                 GeneralTicketFactory generalticketfactory(this->cashiers[0]);
                                                 Ticket ticket = generalticketfactory.generateTicket(name, this->events[intformchoice - 1]);
                                                 id = ticket.getId();
                                                 TicketingSystem::writeBinary("binary.dat",id);
                                                 ticketype = ticket.getTicketType();
                                             }
                                             system("pause");
                                             system("cls");
                                             cout << "You sucessfuly bought a ticket\n\n\n";
                                             cout << "----------------------------------------------------------------------------\n";
                                             cout << "\t\t\tName: " << name<<endl;
                                             cout << "\t\t\tEvent Name: " << this->events[intformchoice-1].getEventName() << endl;
                                             cout << "\t\t\tLocation: " << this->events[intformchoice-1].getLocationName() << endl;
                                             cout << "\t\t\tDate: " << this->events[intformchoice-1].getEventDate() << endl;
                                             cout << "\t\t\tTime: " << this->events[intformchoice-1].getEventTime() << endl;
                                             cout << "\t\t\tZone: " << this->events[intformchoice-1].getEventZoneWithIndex(intFormSubChoiceZone-1)<< endl;
                                             cout << "\t\t\tRow: " << intFormSubChoiceRow << endl;
                                             cout << "\t\t\tSeat: " << intFormSubChoiceSeat << endl;
                                             cout << "\t\t\tTicket Type: " << ticketype << endl;
                                             cout << "\t\t\tId: " << id << endl;
                                             cout << "----------------------------------------------------------------------------\n\n\n";
                                             system("pause");
                                             system("cls");
                                             boughtTicket = true;
                                             break;
                                         }
                                         catch (const exception& e) {
                                             cout << e.what() << endl;
                                         }
                                     }
                                     else if (subChoiceRow[0] == 'q' || subChoiceSeat[0]=='q') {
                                         cout << "Returning to select a zone...\n";
                                         system("pause");
                                         system("cls");
                                         break;
                                     }
                                     else if (subChoiceRow[0] == '-' || subChoiceSeat[0] == '-') {
                                         cout << "Invalid choice. The first input character is not a number. Please enter a valid option.\n\n";
                                         system("pause");
                                         system("cls");
                                     }
                                     else if (subChoiceRow.length() != 1 || subChoiceSeat.length() != 1) {
                                         cout << "Invalid choice. You entered more than one character as an input. Please enter a valid option.\n\n";
                                         system("pause");
                                         system("cls");
                                     }
                                     else {
                                         cout << "Invalid choice. Please enter a valid option.\n\n";
                                         system("pause");
                                         system("cls");
                                     }
                                 } while (subChoiceRow[0] != 'q' || subChoiceSeat[0] != 'q');
                             }
                             else if (subChoiceZone[0] == 'q') {
                                 cout << "Returning to select an event...\n";
                                 system("pause");
                                 system("cls");
                                 break;
                             }
                             else if (subChoiceZone[0] == '-') {
                                 cout << "Invalid choice. The first input character is not a number. Please enter a valid option.\n\n";
                                 system("pause");
                                 system("cls");
                             }
                             else if (subChoiceZone.length() != 1) {
                                 cout << "Invalid choice. You entered more than one character as an input. Please enter a valid option.\n\n";
                                 system("pause");
                                 system("cls");
                             }
                             else {
                                 cout << "Invalid choice. Please enter a valid option.\n\n";
                                 system("pause");
                                 system("cls");
                             }
                         } while (subChoiceZone[0] != 'q' && subChoiceZone.length() == 1 && boughtTicket==false);
                     }
                     else if (subChoiceEvents[0] == '-') {
                         cout << "Invalid choice. The first input character is not a number. Please enter a valid option.\n\n";
                         system("pause");
                         system("cls");
                     }
                     else if (subChoiceEvents.length() != 1) {
                         cout << "Invalid choice. You entered more than one character as an input. Please enter a valid option.\n\n";
                         system("pause");
                         system("cls");
                     }
                     else  if (subChoiceEvents[0] == 'q') {
                         cout << "Returning to main menu...\n";
                         system("pause");
                         system("cls");
                         break;
                     }
                     else {
                         cout << "Invalid choice. Please enter a valid option.\n";
                         system("pause");
                         system("cls");
                     }
                 } while (subChoiceEvents[0] != 'q'&& boughtTicket == false);

             }
             else if (choice[0] == '2') {
                 string subChoice2;
                 bool didAction = false;
                 bool isVip;
                 do {
                     cout << "\tSub-menu for validating a ticket:\n";
                     cout << "\tEnter the ticket code manually:\n";
                     cout << "\t[q] Return to the main menu.\n\n";
                     cout << "Enter your ticket id or press q to go to the main menu :=> ";
                     cin >> subChoice2;
                     system("cls");

                     if (is_number(subChoice2)&& stoi(subChoice2)>0) {
                         if (this->cashiers[0].ticketValidator(stoi(subChoice2))){
                             cout << "The ticket is valid!\n\n";
                             system("pause");
                             system("cls");
                             didAction = true;
                         }
                         else {
                             cout << "The ticket is invalid. You need to buy a new one...\n\n";
                             system("pause");
                             system("cls");
                             didAction = true;
                         }
                     }
                     else if (subChoice2[0] == 'q') {
                         cout << "Returning to the main menu...\n\n";
                         system("pause");
                         system("cls");
                     }
                     else {
                         cout << "Invalid choice. Please enter a number not a string of characters or press q.\n\n";
                         system("pause");
                         system("cls");
                     }
                 } while (subChoice2[0] != 'q' && didAction==false);
             }
             else if (choice[0] == '3') {
                 bool quit = false;
                 enum ZoneName {
                     CATEGORY1 = 1, CATEGORY2 = 2, BOX = 3, STAND1 = 4, STAND2 = 5, LAWN = 6
                 };
                 std::map<ZoneName, std::string> m;
                 m[CATEGORY1] = "Category 1";
                 m[CATEGORY2] = "Category 2";
                 m[BOX] = "Box";
                 m[STAND1] = "Stand 1";
                 m[STAND2] = "Stand 2";
                 m[LAWN] = "Lawn";
                 string zonenamestr;
                 string zonenamestr2;
                 int zonechoice;
                 int zonechoice2;
                 int ticketprice;
                 int ticketprice2;
                 int noRows;
                 int noSeatsPerRow;
                 int noRows2;
                 int noSeatsPerRow2;
                 do {
                     cout << "Enter the first zone name you event will have:\n";
                     cout << "CATEGORY1 = 1, CATEGORY2 = 2, BOX = 3, STAND1 = 4, STAND2 = 5, VIP = 6\n";
                     cout << "Enter the choice for zone 1 name: ";
                     cin >> zonechoice;
                     cout << "\nEnter the choice for zone 2 name: ";
                     cin >> zonechoice2;
                     system("pause");
                     system("cls");
                     if (zonechoice >= CATEGORY1 && zonechoice <= LAWN && zonechoice2 >= CATEGORY1 && zonechoice2 <= LAWN) {
                         zonenamestr = m[(ZoneName)zonechoice];
                         zonenamestr2 = m[(ZoneName)zonechoice2];
                         system("cls");
                         do {
                             cout << "Enter the price of tickets for zone 1: ";
                             cin >> ticketprice;
                             cout << "\nEnter the price of tickets for zone 2: ";
                             cin >> ticketprice2;
                             system("pause");
                             system("cls");
                             if (ticketprice > 0 && ticketprice2>0) {
                                 do {
                                     cout << "Enter the number of rows and Seats you want to have in your zones\n\n";
                                     cout << "Enter the number of rows for zone 1: ";
                                     cin >> noRows;
                                     cout << "\nEnter the number of seats per row for zone 1: ";
                                     cin >> noSeatsPerRow;
                                     cout << "\n\nEnter the number of rows for zone 2: ";
                                     cin >> noRows2;
                                     cout << "\nEnter the number of seats per row for zone 2: ";
                                     cin >> noSeatsPerRow2;
                                     system("pause");
                                     system("cls");
                                     if (noRows > 0 && noSeatsPerRow>0 && noRows2>0 && noSeatsPerRow2>0) {
                                         try {
                                             Zone z1(zonenamestr, ticketprice, noRows, noSeatsPerRow);
                                             Zone z2(zonenamestr2,ticketprice2,noRows2,noSeatsPerRow2);
                                             string eventlocationame;
                                             do {
                                                 cout << "Enter the event location: ";
                                                 cin >> eventlocationame;
                                                 char eventlocationamechar=eventlocationame.at(0);
                                                 system("pause");
                                                 system("cls");
                                                 if (eventlocationame.length() > 0 && isalpha(eventlocationamechar) && isupper(eventlocationamechar)) {
                                                     try {
                                                         string eventName;
                                                         EventLocation ev(eventlocationame, z1);
                                                         ev.addZone(z2);
                                                         do {
                                                             cout << "Enter your event name (min 5 characters max 25): ";
                                                             cin >> eventName;
                                                             system("pause");
                                                             system("cls");
                                                             if (eventName.length()>5 && eventName.length()< 25) {
                                                                 try {
                                                                     string eventDate;
                                                                     cout << "Enter the event date (format: dd-mm-yyyy): ";
                                                                     cin >> eventDate;
                                                                     system("pause");
                                                                     system("cls");
                                                                     if (EventDetails::isValidDateFormat(eventDate)) {
                                                                         string eventTime;
                                                                         do {
                                                                             cout << "\nEnter the event time (format: hh-mm ): ";
                                                                             cin >> eventTime;
                                                                             system("pause");
                                                                             system("cls");
                                                                             if (eventTime.length()== 5) {
                                                                                 try {
                                                                                     const char* nameofevent = eventName.c_str();
                                                                                     EventDetails event(nameofevent,eventDate,eventTime,ev);
                                                                                     this->events.push_back(event);
                                                                                     system("pause");
                                                                                     quit = true;
                                                                                     system("cls");
                                                                                     break;
                                                                                 }
                                                                                 catch (const exception& e) {
                                                                                     cout << e.what() << endl;
                                                                                 }
                                                                             }
                                                                             else {
                                                                                 cout << "Invalid time format, try again using this format: hh-mm (for example 20-23).\n";
                                                                                 system("pause");
                                                                                 system("cls");
                                                                             }
                                                                             
                                                                         } while (quit == false);
                                                                     }
                                                                     else {
                                                                         cout << "Invalid date format, try again using this format: dd-mm-yyyy.\n";
                                                                         system("pause");
                                                                         system("cls");
                                                                     }
                                                                 }
                                                                 catch (const exception& e) {
                                                                     cout << e.what() << endl;
                                                                 }
                                                             }
                                                             else {
                                                                 cout << "You entered an invalid event name. Please try again\n";
                                                                 system("pause");
                                                                 system("cls");
                                                             }
                                                         } while (quit == false);
                                                     }catch(exception& e){
                                                         cout << e.what() << endl;
                                                     }
                                                 }
                                                 else{
                                                     cout << "Event Location name length is either <0 or >10 or the first letter is not capital, try again\n\n";
                                                     system("pause");
                                                     system("cls");
                                                 }
                                             } while (quit == false);
                                         }
                                         catch (const exception& e) {
                                             cout << e.what()<<endl;
                                         }
                                     }
                                     else {
                                         cout << "Invalid input , all values need to be > 0\n\n";
                                         system("pause");
                                         system("cls");
                                     }
                                 } while (quit == false);
                             }
                             else {
                                 cout << "Invalid price, try again (should be > 0 )\n\n";
                                 system("pause");
                                 system("cls");
                             }
                         }while (quit == false);
                     }
                     else {
                         cout << "Invalid input, choose between 1 and 6 for both zones\n\n";
                         system("pause");
                         system("cls");
                     }
                 } while (quit == false);
             }
             else if (choice[0] == '4') {
                 cout << "Quitting the program...\n";
             }
             else if (choice[0] == '-') {
                 cout << "Invalid choice. The first input character is not a number. Please enter a valid option.\n\n";
                 system("pause");
                 system("cls");
             }
             else if (choice.length() != 1) {
                 cout << "Invalid choice. You entered more than one character as an input. Please enter a valid option.\n\n";
                 system("pause");
                 system("cls");
             }
            else {
                cout << "Invalid choice. Please enter a valid option.\n\n";
                system("pause");
                system("cls");
            }

         } while (choice[0]!= '4');
    }
};
