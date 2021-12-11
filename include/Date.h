#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>
#include <string>

#include "Enums.h"

using namespace std;

class Date{
public:
    Date();
    Date(Date & d, double hour);
    ~Date();

    
    bool isBetween(Date date1, Date date2) const;
    bool operator<=(const Date &d2) const;
    bool operator>=(const Date &d2) const;
    void operator=(const Date &d2);
    bool operator==(const Date &d2) const;

    string DateToString() const;


    void Test();
private:
    int day, month, year;
    int hour, minute;
    WeekDay weekDay;
};


#endif