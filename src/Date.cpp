#include "Date.h"
#include "time.h"

#include<iostream>

Date::Date(){
    time_t currentTime = time(0);
    tm * ltm = localtime(&currentTime);

    day = ltm->tm_mday;
    month = ltm->tm_mon + 1; // ltm->tm_mon = month [0, 11]
    year = ltm->tm_year + 1900; // ltm->tm_year = time since 1900

    switch(ltm->tm_wday){
        case 1: weedDay = monday; break;
        case 2: weedDay = tuesday; break;
        case 3: weedDay = wednesday; break;
        case 4: weedDay = thursday; break;
        case 5: weedDay = friday; break;
        case 6: weedDay = saturday; break;
        case 7: weedDay = sunday; break;
        default: weedDay = monday; break;
    }

    hour = ltm->tm_hour;
    minute = ltm->tm_min;
}

Date::~Date(){

}

bool Date::isBetween(Date date1, Date date2){
    if(date1 <= date2){
        if(*this >= date1 && *this <= date2)
            return true;
    } 
    else{
        if(*this >= date2 && *this <= date1)
            return true;
    } 
    return false;
}

void Date::setDate(int day_, int month_, int year_){
    day = day_;
    month = month_;
    year = year_;    
}

void Date::setTime(int hour_, int minute_){
    hour = hour_;
    minute = minute_;
}

bool Date::operator<=(Date &d2){
    if(year > d2.year)
        return false;
    if(month > d2.month)
        return false;
    if(day > d2.day)
        return false;
    if(hour > d2.hour)
        return false;
    if(minute > d2.minute)
        return false;
    
    return true;
}

bool Date::operator>=(Date &d2){
    if(year < d2.year)
        return false;
    if(month < d2.month)
        return false;
    if(day < d2.day)
        return false;
    if(hour < d2.hour)
        return false;
    if(minute < d2.minute)
        return false;
    
    return true;
}

