#include <iostream>
#include <vector>
using namespace std;

class User{
    protected:
    string userID;
    string name;
    string phoneNum;
    string role;

    public:

    //Default Constructor:
    User(){};

    //Parameterized Constructor:
    User(string userID, string name, string phoneNum, string role): userID(userID), name(name), phoneNum(phoneNum), role(role) {}

    //Display Function:
    virtual void displayInfo(){
        cout << "User ID : " << userID <<endl;
        cout << "Name :" << name << endl;
        cout << "Phone Number :" << phoneNum << endl;
        cout << "Role :" << role << endl;
    }
};

class Driver : public User{
    private:
    float rating;
    bool available; 

    public:

    //Default Constructor:
    Driver(){};

    //Parameterized Constructor:
    Driver(string userID, string name, string phoneNum, float rating = 5.0): User (userID, name, phoneNum, "Driver"), rating(rating), available(true) {}

    //Check Availability
    void setAvailability(bool status) {
        available = status;
    }

    bool isAvailable() {
        return available;
    }

    //Display Function:
    void displayInfo() override{
        User :: displayInfo();
        cout << "Rating :" << rating << endl;
        cout << "Is Driver Available :" << (available ? "Yes" : "No") << endl;
    }

};

class Rider : public User{    //class name should be passenger instead of rider
    private:
    vector <string> rideHistory;

    public:

    //Default Constructor
    Rider(){}

    //Parametrized Constructor
    Rider(string userID, string name, string phoneNum) : User (userID, name, phoneNum, "Rider"){}
    
    //Display Function
    void displayInfo() override{
        User ::displayInfo();
        cout << "Total Rides: " << rideHistory.size() << endl;
    }
};

class PremiumRider : public Rider{
    private:
    float discount;

    public:
    //Default Constructor
    PremiumRider(){}

    //Parametrized Constructor
    PremiumRider(string userID, string name, string phoneNum, float discount = 0.0) : Rider (userID, name, phoneNum), discount(discount) {}

    float getDiscount(){
        return discount;
    }
    
    //Display Function
    void displayInfo() override{
        Rider ::displayInfo();
        cout << "Discount : " << discount << "%" << endl;
    }


};

class Ride{

    private:
    double rate;

    public:
    string type;
    
    //Default Constructor
    Ride(){}

    //Parametrized Constructor
    Ride(string type, double rate) : type(type), rate (rate) {}

    //Getter Function
    double getRate(){
        return rate;
    }

    //Setter Function
    void setRate(double rate){
        rate = rate;
    }

    
};

int main(){

    return 0;
}
