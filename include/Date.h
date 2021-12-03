#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>
#include <string>

using namespace std;

enum WeekDay{monday, tuesday, wednesday, thursday, friday, saturday, sunday};

class Date{
public:
    Date();
    Date(Date & d, double hour);
    ~Date();

    
    bool isBetween(Date date1, Date date2) const;
    bool operator<=(Date &d2) const;
    bool operator>=(Date &d2) const;
    void operator=(Date &d2);

    string DateToString() const;
private:
    int day, month, year;
    int hour, minute;
    WeekDay weekDay;
};


#endif