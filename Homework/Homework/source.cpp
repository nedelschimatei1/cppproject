#include <iostream>
#include <string>
using namespace std;

enum fuelType {GASOLINE,DIESEL,ELECTRIC,HYBRID};

class Car {
    const string vehiclePlates = "";
    string brand = "";
    fuelType fueltype = GASOLINE;
    bool hasAutopilot = false;
    int noTrips = 0;
    float* kmPerTrip = nullptr;
    const static float AVERAGE_LITER_PER_100KM;

public:
    //Setters

    void setBrand(const string& brand) {
        this->brand = brand;
    }

    void setFuelType(fuelType fueltype) {
        this->fueltype = fueltype;
    }

    void setKmPerTripArray(const float* newArr, int sizeNewArr) {
        if (newArr == nullptr || sizeNewArr < 1) {
            throw exception("newArray for setting the kmPerTrip attribute is null");
        }
        else {
            if (this->kmPerTrip != nullptr) {
                delete[] this->kmPerTrip;
                this->kmPerTrip = nullptr;
            }
            this->kmPerTrip = new float[sizeNewArr];
            for (int i = 0; i < sizeNewArr; i++) {
                this->kmPerTrip[i] = newArr[i];
            }
            this->noTrips = sizeNewArr;
        }
    }

    //Getters
    float* getKmPerTripArray() {
        if (this->noTrips > 0 && this->kmPerTrip != nullptr) {
            float* copy = new float[this->noTrips];
            for (int i = 0; i < this->noTrips; i++) {
                copy[i] = this->kmPerTrip[i];
            }
            return copy;
        }
    }
    
    string getVehiclePlates() {
        return this->vehiclePlates;
    }

    string getBrand() {
        return this->brand;
    }

    int getNoTrips() {
        return this->noTrips;
    }

    //Constructor
    Car(const string& plates, const string& brand, fuelType fueltype): vehiclePlates(plates) {
        if (plates.size() < 10)
            throw exception("The plates string you passed in the constructor of the class is smaller than 10 characters.");;
        setBrand(brand);
        setFuelType(fueltype);
    }

    //Copy CTR

    Car( const Car& source):vehiclePlates(source.vehiclePlates) {
        if (source.kmPerTrip != nullptr) {
            this->noTrips = source.noTrips;
            this->kmPerTrip = new float[source.noTrips];
            for (int i = 0; i < source.noTrips; i++) {
                this->kmPerTrip[i] = source.kmPerTrip[i];
            }
            this->brand = source.brand;
            this->fueltype = source.fueltype;
        }
        else throw exception("Source object for copy ctr has the dynamic field value as a nullptr");
    }

    //Overloading of "="

    Car& operator=(const Car& source){
        if (this->kmPerTrip == source.kmPerTrip) {
            exit;
        }
        if (this->kmPerTrip != nullptr && source.kmPerTrip != nullptr) {
            delete[] this->kmPerTrip;
            const_cast <std::string&> (this->vehiclePlates) = source.vehiclePlates;
            this->kmPerTrip = nullptr;
            this->noTrips = source.noTrips;
            this->kmPerTrip = new float[source.noTrips];
            for (int i = 0; i < source.noTrips; i++) {
                this->kmPerTrip[i] = source.kmPerTrip[i];
            }
            this->brand = source.brand;
            this->fueltype = source.fueltype;
            return *this;
        }
        else throw exception("When trying the = operator between 2 object, 1 object has the kmPerTrip value equal to a nullptr or both objects.");
    }

    //Destructor
    ~Car() {
        if (this->kmPerTrip != nullptr) {
            delete[] this->kmPerTrip;
            this->kmPerTrip = nullptr;
        }
    }
};

const float Car::AVERAGE_LITER_PER_100KM = 7.5;

int main() {
    float f1[2] = { 10.2,10.11 };
    float ex[3] = { 11.1,2.33,4.55 };
    Car c1("1111111111111111", "Dacia", DIESEL);
    cout<<c1.getVehiclePlates()<<endl;
    c1.setKmPerTripArray( f1, 2);
    float* f2 = c1.getKmPerTripArray();
    for (int i = 0; i < c1.getNoTrips(); i++) {
        cout << f2[i] << " ";
    }
    cout << endl;
    Car c2("sef-pe-constanta", "Mertan", ELECTRIC);
    c2.setKmPerTripArray(ex, 3);
    Car c3 = Car(c1);
    c1 = c2;
    cout << c1.getBrand()<<endl;
    cout << c1.getVehiclePlates() << endl;
    cout << c3.getBrand() << endl;
    cout << c3.getVehiclePlates() << endl;
    return 0;
}