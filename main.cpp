#include <iostream>
#include <vector>
using namespace std;


class DriverReview;
class User;
class PremiumRider;
class Subscription;
class Rider;
class Ride;

class DriverReview {
    private:
        string passengerName;
        int rideID;
        double rating;
        string reviewMessage;
        string timestamp;
    
    public:
    DriverReview(){}
    DriverReview(string passenger, int ride, double rate, string review, string time) {
    passengerName = passenger;
    rideID = ride;
    rating = (rate >= 1 && rate <= 5) ? rate : 3; // Ensures rating is valid
    reviewMessage = review;
    timestamp = time;
}

// Display Review
void displayReview() {
    cout << "👤 Passenger: " << passengerName << endl;
    cout << "⭐ Rating: " << rating << "/5" << endl;
    cout << "📝 Review: " << reviewMessage << endl;
    cout << "📅 Date: " << timestamp << endl;
    cout << "------------------------------\n";
}

double getRating() {
    return rating;
}
};

// Function to calculate average rating
double calculateAverageRating(DriverReview reviews[], int totalReviews) {
double sum = 0;
for (int i = 0; i < totalReviews; i++) {
    sum += reviews[i].getRating();
}
return (totalReviews > 0) ? (sum / totalReviews) : 0;
}

// Show driver’s reviews before booking
void showDriverProfile(DriverReview reviews[], int totalReviews) {
cout << "\n🚖 Driver Profile & Reviews 🚖" << endl;
double avgRating = calculateAverageRating(reviews, totalReviews);
cout << "⭐ Average Rating: " << avgRating << "/5" << endl;

cout << "\n📌 Recent Reviews:" << endl;
for (int i = 0; i < totalReviews; i++) {
    reviews[i].displayReview();
}
}

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
    DriverReview driver; 
    bool available; 

    public:

    //Default Constructor:
    Driver(){};

    //Parameterized Constructor:
    Driver(string userID, string name, string phoneNum, float rating = 0.0): User (userID, name, phoneNum, "Driver"), available(true) {}

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
        cout << "Driver Review" << endl;
        driver.displayReview();
        cout << "Is Driver Available :" << (available ? "Yes" : "No") << endl;
    }

};

class Rider : public User{
    private:
    // vector <int> rideHistory;
    int rideHistory;

    public:

    //Default Constructor
    Rider(){}

    //Parametrized Constructor
    Rider(string userID, string name, string phoneNum) : User (userID, name, phoneNum, "Rider"), rideHistory(0){}
    
    //Display Function
    void displayInfo() override{
        User ::displayInfo();
        cout << "Total Rides: " << rideHistory << endl;
    }
};

class PremiumRider : public Rider{
    private:
    Subscription plan;

    public:
    //Default Constructor
    PremiumRider(){}

    //Parametrized Constructor
    PremiumRider(string userID, string name, string phoneNum) : Rider (userID, name, phoneNum){}

    
    //Display Function
    void displayInfo() override{
        Rider ::displayInfo();
        plan.displaySubscription();
    }


};

class Subscription {
    private:
        string planType;
        double discount;   // Discount percentage
        string registrationDate;
        string expiryDate; // Expiry date of the subscription
    
    public:
    
        // Function to set plan and assign discount
        void setPlan(int plan) {
            if (plan == 1) {
               planType = "Weekly";
                discount = 5; // 5% discount
                expiryDate = "7 days from today";   //Display date instead of message
            } else if (plan == 2) {
             planType = "Monthly";
                discount = 10; // 10% discount
                expiryDate = "30 days from today";  
            } else if (plan == 3) {
                planType = "Yearly";
                discount = 20; // 20% discount
                expiryDate = "365 days from today";  
            } else {
                cout << "❌ Invalid plan selected! Subscription Failed." << endl;
                return;
            }
        }
    
        // Function to display subscription details
        void displaySubscription() {
            cout << "\n📌---------- Subscription Details ---------- " << endl;
            cout << "Plan Type: " << planType << endl;
            cout << "Discount: " << discount << "% on all rides" << endl;
            cout << "Registration Date: " << registrationDate << endl;
            cout << "Expiry Date: " << expiryDate << endl;
        }
    
        // Function to cancel subscription
        void cancelSubscription() {
            cout << "\n❌ Subscription Cancelled!" << endl;
            planType = "None";
            discount = 0;
            expiryDate = "N/A";
        }
    };

class Ride{

    private:
    double rate;

    public:
    const string type[4] = {"Bike", "Rickshaw", "Comfort", "Economy" };
    
    //Default Constructor
    Ride(){}

    //Parametrized Constructor
    Ride(double rate) : rate (rate) {}

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
