//
//  main.cpp
//  hmw_2_2.cpp
//
//  Created by Gaurav Gulati on 10/16/18.
//  Copyright © 2018 Gaurav Gulati. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class declarations
class Appointment {
    public:
        Appointment();
        Appointment(string description, string date, string time);
        string getTime();
        string getDesc();
        virtual bool occurs_on(int year, int month, int day);
        virtual ~Appointment(); // destructor
    protected:
        string description;
        string date;
        string time;
};

class Onetime: public Appointment {
    public:
        Onetime();
        Onetime(string description, string date, string time);
        ~Onetime();
        bool occurs_on(int year, int month, int day);
    private:
};

class Daily: public Appointment {
    public:
        Daily();
        Daily(string description, string date, string time);
        ~Daily();
        bool occurs_on(int year, int month, int day);
private:
};

class Weekly: public Appointment {
    public:
        Weekly();
        Weekly(string description, string date, string time);
        ~Weekly();
        bool occurs_on(int year, int month, int day);
    private:
};

class Monthly: public Appointment {
    public:
        Monthly();
        Monthly(string description, string date, string time);
        ~Monthly();
        bool occurs_on(int year, int month, int day);
    private:
};

// check for leap year
bool isLeapYear(int year){
    if(year%4 != 0){
        // is common year
        return false;
    } else if(year%100 != 0){
        // is a leap year
        return true;
    } else if (year%400 != 0){
        // is a common year
        return false;
    } else {
        // is a leap year
        return true;
    }
}

// find day by date
int findDayByDate (int day, int month, int year){
    int lastDigOfYear = year%100;
    int divBy4 = lastDigOfYear/4;
    int addDay = divBy4 + day;
    
    // add month key value pair
    int addMonthKeyVal;
    if(month == 1 || month == 10) {
        addMonthKeyVal = addDay + 1;
    } else if (month == 2 || month == 3 || month == 11){
        addMonthKeyVal = addDay + 4;
    } else if (month == 4 || month == 7){
        addMonthKeyVal = addDay + 0;
    } else if ( month == 5 ) {
        addMonthKeyVal = addDay+2;
    } else if (month == 6){
        addMonthKeyVal = addDay + 5;
    } else if (month == 8){
        addMonthKeyVal = addDay + 3;
    } else {
        // if month is sept or dec
        addMonthKeyVal = addDay + 6;
    }
    
    bool checkLeapYear = isLeapYear(year);
    if( checkLeapYear &&  (month == 1 || month == 2) ) {
        addMonthKeyVal = addMonthKeyVal - 1;
    }
    
    int centuryVal = addMonthKeyVal;
    int getCentury = (year + 50) / 100 * 100;
    if(getCentury == 1700){
        centuryVal = centuryVal + 4;
    } else if (getCentury == 1800 ){
        centuryVal = centuryVal + 2;
    } else if (getCentury == 2000) {
        centuryVal = centuryVal + 6;
    }else {
        centuryVal = centuryVal + 0;
    }
    
    centuryVal = centuryVal + (year%100);
    
    int dayOfWeek = centuryVal%7;
    return dayOfWeek;
}


int main() {
    vector <Appointment*> calendar;
    cout << "Enter the list of appointments." << endl;
    cout << endl;
    char answer = 'y';
    while(answer != 'n'){
        string description, type, date, time;
        cout << "Appointment's description: ";
        getline(cin, description);
        cout << "Appointment's type: ";
        getline(cin, type);
        cout << "Appointment's starting date: ";
        getline(cin, date);
        cout << "Appointment's time: " ;
        getline(cin, time);
        cout << endl;
        
        if(type == "Onetime"){
            Appointment* ptr = new Onetime(description, date, time);
            calendar.push_back(ptr);
            //cout << "onetime" << endl;
        } else if (type == "Daily") {
            Appointment* ptr = new Daily(description, date, time);
            calendar.push_back(ptr);
            //cout << "daily" << endl;
        } else if (type == "Weekly"){
            Appointment* ptr = new Weekly(description, date, time);
            calendar.push_back(ptr);
            //cout << "weely" << endl;
        } else if (type == "Monthly"){
            Appointment* ptr = new Monthly(description, date, time);
            calendar.push_back(ptr);
            //cout << "monthly" << endl;
        } else {
            cout << "Not valid type" << endl;
            break;
        }
        
        cout << "Another appointment (y/n)? " ;
        cin >> answer;
        cin.ignore(256,'\n');
        cout << endl;
    }
    string userInputDate;
    cout << "------------------------" << endl;
    cout << "Enter a date: " ;
    getline(cin, userInputDate);
    cout << endl;
    
    cout << "The list of appointments that happen on " << userInputDate << ":" <<endl;
    cout << endl;
    
    int inputDay = stod(userInputDate.substr(3,2));
    int inputMonth = stod(userInputDate.substr(0,2));
    int inputYear = stod(userInputDate.substr(6));
    int count = 0;
    for(int i = 0; i < calendar.size(); i++){
        bool doesOccur = calendar[i]->occurs_on(inputYear, inputMonth, inputDay);
        if(doesOccur){
            string event = calendar[i]->getDesc();
            string time = calendar[i]->getTime();
            cout << count << " " << event << ", " << time << endl;
            count++;
        }
    }
    
    for(int i = 0; i < calendar.size(); i++){
        calendar[i]->~Appointment(); // works because all derived classes have the same private variables]
        delete calendar[i];
    }
}


// Appointment Cpp File
Appointment::Appointment(): description(""), date(""), time("") {};

Appointment::Appointment(string description, string date, string time): description(description), date(date), time(time) {};

Appointment::~Appointment() {
    description.clear();
    date.clear();
    time.clear();
}

string Appointment::getTime() {
    return time;
}

string Appointment::getDesc() {
    return description;
}

bool Appointment::occurs_on(int year, int month, int day) {
    return true;
}

// Onetime Cpp File
Onetime::Onetime(): Appointment() {};

Onetime::Onetime(string description, string date, string time): Appointment(description, date, time) {};

Onetime::~Onetime() {
    description.clear();
    date.clear();
    time.clear();
}

bool Onetime::occurs_on(int year, int month, int day) {
    // 10/17/2018
    int userDay = stod(date.substr(3,2));
    int userMonth = stod(date.substr(0,2));
    int userYear = stod(date.substr(6));
    if(year == userYear && day == userDay && month == userMonth){
        return true;
    } else {
        return false;
    }
}

// Daily Cpp File
Daily::Daily(): Appointment() {};

Daily::Daily(string description, string date, string time): Appointment(description, date, time) {};

Daily::~Daily() {
    description.clear();
    date.clear();
    time.clear();
}

bool Daily::occurs_on(int year, int month, int day) {
    // 10/17/2018
    int userDay = stod(date.substr(3,2));
    int userMonth = stod(date.substr(0,2));
    int userYear = stod(date.substr(6));
    if( userDay > day && month == userMonth && userYear == year){
        return false;
    } else if ( userMonth > month && userYear == year){
        return false;
    } else if ( userYear > year ) {
        return false;
    } else {
        return true;
    }

}

// Weekly Cpp File
Weekly::Weekly(): Appointment() {};

Weekly::Weekly(string description, string date, string time): Appointment(description, date, time) {};

Weekly::~Weekly() {
    description.clear();
    date.clear();
    time.clear();
}

bool Weekly::occurs_on(int year, int month, int day) {
    // 10/17/2018
    int userDay = stod(date.substr(3,2));
    int userMonth = stod(date.substr(0,2));
    int userYear = stod(date.substr(6));
    if(month < userMonth && year == userYear){
        return false;
    }
    if ( year < userYear){
        return false;
    }
    if( day < userDay && month == userMonth && userYear == year){
        return false;
    }
    int dayOfGivenEvent = findDayByDate(day, month, year);
    int dayOfThisEvent = findDayByDate(userDay, userMonth, userYear);
    return (dayOfThisEvent == dayOfGivenEvent);
}


// Monthly Cpp File
Monthly::Monthly(): Appointment() {};

Monthly::Monthly(string description, string date, string time): Appointment(description, date, time) {};

Monthly::~Monthly() {
    description.clear();
    date.clear();
    time.clear();
}

bool Monthly::occurs_on(int year, int month, int day) {
    // 10/17/2018
    int userDay = stod(date.substr(3,2));
    int userMonth = stod(date.substr(0,2));
    int userYear = stod(date.substr(6));
    
    if(month < userMonth && year == userYear){
        return false;
    } else if ( year < userYear){
        return false;
    } else if(userDay == day){
        return true;
    } else {
        return false;
    }
}
