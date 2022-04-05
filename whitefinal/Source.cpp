
#include<string>
#include<iostream>
#include<sstream>
#include<map>
#include<set>
#include<iomanip>
using namespace std;

class Date {
public:

    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

    int year;
    int month;
    int day;
};

istream& operator>>(istream& is, Date& date) {
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;
    return is;
}

ostream& operator<<(ostream& os, const Date& date) {
    os << setfill('0') << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
    return os;
}


bool operator<(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 365 + lhs.GetMonth() * 31 + lhs.GetDay() < rhs.GetYear() * 365 + rhs.GetMonth() * 31 + rhs.GetDay();
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        date_to_events[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        if (date_to_events.count(date)==0){return 0;}
        return date_to_events[date].erase(event);
    }

    int  DeleteDate(const Date& date){
        if (date_to_events.count(date)==0){return 0;}
        int events_deleted=date_to_events[date].size();
        date_to_events.erase(date);
        return events_deleted;
    }

    //   /* ??? */ Find(const Date& date) const;

    void Print() const {
        std::cout<<"size of map: "<<date_to_events.size()<<std::endl;
        for (const auto& [date, events_set] : date_to_events) {
            ;
            for (const auto& event : events_set) {
                 std::cout << date << ' '<< event << std::endl;
            }
            
        }
    };

private:
    std::map<Date, std::set<std::string>> date_to_events;
};



int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
       
        if (command.empty()) { continue; }
        stringstream ss(command);
        string operation;
        ss >> operation;
        if (operation == "Add") {
            Date date;
            string event;
            ss >> date >> event;
            db.AddEvent(date, event);
        }else if (operation == "Del"){
            Date date;
            string event;
            ss >> date >> event;
            if (event.empty()){
                //del all day events
                std::cout<<"Deleted "<<db.DeleteDate(date)<<" events"<<endl;
            }else{
                //del event on day
               if(db.DeleteEvent(date,event)){
                  std::cout<<"Deleted successfully"<<endl; 
               } else{
                   std::cout<<"Event not found"<<endl;
               }
            }
        }else if (operation == "Find"){
            
        }else if (operation == "Print"){
            db.Print();   
        }

    }
    
    return 0;
}
