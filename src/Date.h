#ifndef __DATE_H_
#define __DATE_H_

#include <iostream>

enum WeekDay{monday, tuesday, wednesday, thursday, friday, saturday, sunday};

class Date{
public:
    Date();
    Date(Date & d, int hour);
    ~Date();
    bool isBetween(Date date1, Date date2) const;
    void setDate(int day_, int month_, int year_);
    void setTime(int hour_, int minute_);

    bool operator<=(Date &d2) const;
    bool operator>=(Date &d2) const;
    void operator=(Date &d2);
    friend std::ostream& operator<<(std::ostream& os, const Date & d);

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    WeekDay getWeekDay() const;

private:
    int day, month, year;
    int hour, minute;
    WeekDay weedDay;
};


#endif