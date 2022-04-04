// –еализуйте функции и методы классов и при необходимости добавьте свои
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
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);

    //   /* ??? */ Find(const Date& date) const;

    void Print() const {
        for (const auto& [date, events_set] : date_to_events) {
            for (const auto& event : events_set) {
                std::cout << date << ' ' << event << std::endl;
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
        // —читайте команды с потока ввода и обработайте каждую
        if (command.empty()) { continue; }
        stringstream ss(command);
        string operation;
        ss >> operation;
        if (operation == "Add") {
            Date date;
            string event;
            ss >> date >> event;
            db.AddEvent(date, event);

        }

    }
    db.Print();
    return 0;
}