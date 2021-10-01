#include "Date.h"
#include "time.h"

#include<iostream>
#include<string>

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

    // Les heures seront des minutes et les minutes des secondes
    // pour accelerer le défilement du temps
    hour = ltm->tm_min%24;
    minute = ltm->tm_sec;
}



/*
A FAIRE :
    Gerer les depassement d'année
    Changement de weedDay 
*/

Date::Date(Date & d, int hours){
    *this = d;

    hour = d.hour + hours;
    if(hour >= 24){
        int addDay = (hour+1 - hour%24) / 24;
        day += addDay;
        hour = hour % 24;
        
        // Nombre de jour minimum dans un mois 
        if(day>28){
            switch (month)
            {
            case 1 :
            case 3 :
            case 5 :
            case 7 :
            case 8 :
            case 10 :
            case 12 :
                if(day>31){
                    month++;
                    day = day%31 + 1;
                }
                break;
            
            case 4 :
            case 6 :
            case 9 :
            case 11 :
                if(day>30){
                    month++;
                    day = day%30 + 1;
                }
                break;

            case 2:
                if(year%4==0){
                    if(day>29){
                        month++;
                        day = day%29 + 1;
                    }
                }
                else{
                    if(day>28){
                        month++;
                        day = day%28 + 1;
                    }
                }
                
                break;

             
            default:
                break;
            }
        }
        

    }
}


Date::~Date(){

}

bool Date::isBetween(Date date1, Date date2) const{
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

bool Date::operator<=(Date &d2) const{
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

bool Date::operator>=(Date &d2) const{
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

void Date::operator=(Date &d2){
    year = d2.year;
    month = d2.month;
    day = d2.day;
    hour = d2.hour;
    minute = d2.minute;

    weedDay = d2.weedDay;
}

std::ostream& operator<<(std::ostream& os, const Date& d){
    std::string strWeekDay;
    switch(d.getWeekDay())
    {
    case monday: strWeekDay="Monday";
        break;

    case tuesday: strWeekDay="Tuesday";
        break;

    case wednesday: strWeekDay="Wednesday";
        break;

    case thursday: strWeekDay="Thursday";
        break;
    
    case friday: strWeekDay="Friday";
        break;
    
    case saturday: strWeekDay="Saturday";
        break;
    
    case sunday: strWeekDay="Sunday";
        break;
    
    default: strWeekDay="Monday";
        break;
    }

    os << strWeekDay << " " << d.getDay() << "/" << d.getMonth() << "/";
    os << d.getYear() << " - "<< d.getHour() << ":" << d.getMinute();
    return os;
}


int Date::getYear() const{
    return year;
}

int Date::getMonth() const{
    return month;
}

int Date::getDay() const{
    return day;
}

int Date::getHour() const{
    return hour;
}

int Date::getMinute() const{
    return minute;
}

WeekDay Date::getWeekDay() const{
    return weedDay;
}
