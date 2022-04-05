
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
    char c;
    std::string datesring;
    is>>datesring;
    stringstream ss(datesring);
    ss >> date.year;
    if (ss.fail()){throw invalid_argument("Wrong date format: "+datesring);}
    ss>>c;
    if (c!='-'){throw invalid_argument("Wrong date format: "+datesring);}
    ss >> date.month;
    if (ss.fail()){throw invalid_argument("Wrong date format: "+datesring);}
     if (date.month<1||date.month>12){throw domain_error("Month value is invalid: "+to_string(date.month)); }
    ss>>c;
    if (c!='-'){throw invalid_argument("Wrong date format: "+datesring);}
    ss >> date.day;
    if (ss.fail()){throw invalid_argument("Wrong date format: "+datesring);}
    if (date.day<1||date.day>31){throw domain_error("Day value is invalid: "+to_string(date.day)); }
    if (!ss.eof()){throw invalid_argument("Wrong date format: "+datesring);}
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
    void Find(const Date& date) const{
    if (date_to_events.count(date)==0){return;}
    for (const auto& event : date_to_events.at(date)) {
                 std::cout << event << std::endl;
            }    
        
    }

    void Print() const {
 
        for (const auto& [date, events_set] : date_to_events) {
            for (const auto& event : events_set) {
                 std::cout << date << ' '<< event << std::endl;
            }
            
        }
    };

private:
    std::map<Date, std::set<std::string>> date_to_events;
};



int main() {
    try {
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
            Date date;
            ss>>date;
            db.Find(date);
            
        }else if (operation == "Print"){
            db.Print();   
        }else{std::cout<<"Unknown command: "<<operation;}

    }
    }catch(invalid_argument&ex){
        std::cout<<ex.what();
    }catch(domain_error&ex){
        std::cout<<ex.what();
    }catch(exception&ex){
        
    }
    
    return 0;
}
