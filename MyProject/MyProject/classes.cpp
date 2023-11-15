#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <string>

using namespace std;

class EventLocation {
private:
    string locationName = "";
    const int maxnrSeats;
    int nrZones = 0 ;
    int nrRows = 0;
    int seatsPerRow = 0;
    int** availableSeats = nullptr;

public:

    // Setters
    void setLocationName(const string location) {
        if (location.length() < 3 || location.length() > 20) {
            throw exception("You entered an invalid string please enter another valid one (minimum 3 characters,maximum 20, for ex:`BUC`");
        };
        this->locationName = location;
    }

    void setNumRows(int rows) {
        if (rows < 0) {
            throw exception("Negative number of rows, please enter another number");
        }
        this->nrRows = rows;
    }

    void setNumZones(int zones) {
        if (zones < 0) {
            throw exception("Negative number of zones, please enter another number");
        }
        this->nrZones = zones;
    }

    void setSeatsPerRow(int seats) {
        if (seats < 0) {
            throw exception("Negative number of seats, please enter another number");
        }
        this->seatsPerRow = seats;
    }

   void setAvailableSeats(int rows,int seats) {
       if (this->availableSeats != nullptr) {
           for (int i = 0; i < this->nrRows; ++i) {
               delete[](this->availableSeats)[i];
           }
           delete[](this->availableSeats);
           this->availableSeats = nullptr;
       }
       if ((this->nrRows * this->seatsPerRow) < (this->maxnrSeats) && (this->nrRows)>0 && (this->seatsPerRow) > 0) {
            setNumRows(rows);
            setSeatsPerRow(seats);
            this->availableSeats = new int*[this->seatsPerRow];
            for (int i = 0; i < this->seatsPerRow; ++i) {
                this->availableSeats[i] = new int[this->seatsPerRow];
            }
            for (int i = 0; i < this->nrRows; ++i) {
                for (int j = 0; j < this->seatsPerRow; ++j) {
                    this->availableSeats[i][j] = 0;
                }
            }
        }
    }

   void buyaSeat(int row,int seat) {
       for (int i = 0; i < this->nrRows; ++i) {
           for (int j = 0; j < this->seatsPerRow; ++j) {
               this->availableSeats[row-1][seat-1] = 1;
           }
       }
   }


    // Accessor methods
    string getLocationName() {
        return this->locationName;
    }

    int getMaxSeats() {
        return this->maxnrSeats;
    }

    int getNumRows() {
        return this->nrRows;
    }
    
    int getSeatsPerRow() {
        return this->seatsPerRow;
    }

    int getNumZones() {
        return this->nrZones;
    }

    void getAvailableSeats() {
        for (int i = 0; i < this->nrRows; i++) {
            for (int j = 0; j < this->seatsPerRow; j++) {
                cout << this->availableSeats[i][j] << " ";
            }
            cout << endl;
        }
    }
    // Other processing method
    // 
    //void printLocationDetails();

    //Constructors
    EventLocation(const string locationName, int maxnrSeats, int nrZones, int nrRows, int seatsPerRow) :maxnrSeats(maxnrSeats) {
        setLocationName(locationName);
        setNumZones(nrZones);
        setNumRows(nrRows);
        setSeatsPerRow(seatsPerRow);
        setAvailableSeats(nrRows,seatsPerRow);
        cout << "Object Created"<<endl;

    }

    //Destructor
    ~EventLocation() {
        if (this->availableSeats != nullptr) {
            for (int i = 0; i < this->nrRows; ++i) {
                delete[] (this->availableSeats)[i];
            }
            delete[] (this->availableSeats);
            this->availableSeats = nullptr;
            }
        }
};

