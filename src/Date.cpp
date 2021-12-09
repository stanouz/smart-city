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
        case 1: weekDay = monday; break;
        case 2: weekDay = tuesday; break;
        case 3: weekDay = wednesday; break;
        case 4: weekDay = thursday; break;
        case 5: weekDay = friday; break;
        case 6: weekDay = saturday; break;
        case 7: weekDay = sunday; break;
        default: weekDay = monday; break;
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

Date::Date(Date & d, double hoursToAdd){
    *this = d;


    
    minute += hoursToAdd*60;
   

    if(minute >= 60){
        hour += minute/60;
        minute %= 60;
    }
    
    if(hour >= 24){
        int addDay = (hour+ hour/24 - hour%24) / 24;
        day += addDay;
        hour = hour % 24;
        
        // Nombre de jour minimum dans un mois 
        if(day>28){

            if(month==1 || month==3 || month==5 || month==7 ||
               month==8 || month==10 || month==12){

                if(day>31){
                    month += day/31;
                    day = day%31 + 1;
                }
            }

            if(month==4 || month==6 || month==9 || month==11){
                if(day>30){
                    month += day/30;
                    day = day%30 + 1;
                }
            }
            
            
            if(month==2){
                if(year%4==0){
                    if(day>29){
                        month += day/29;
                        day = day%29 + 1;
                    }
                }
                else{
                    if(day>28){
                        month += day/28;
                        day = day%28 + 1;
                    }
                }
            }
        }
           
        

    }
}


Date::~Date(){

}

bool Date::isBetween(Date date1, Date date2) const{
    if(date1 <= date2){
        if(*this >= date1 && *this <= date2){
            return true;
        }      
    } 
    else{
        if(*this >= date2 && *this <= date1){
            return true;
        }
    } 
    return false;
}

bool Date::operator<=(const Date &d2) const{
    // Cas où ils sont égaux
    if(*this == d2){
        return true;
    }


    if(year < d2.year){ return true; }
    else if(year != d2.year){ return false; }

    if(month < d2.month){ return true; }
    else if(month != d2.month){  return false; }

    if(day < d2.day){ return true; }
    else if(day != d2.day){ return false; }

    if(hour < d2.hour){ return true; }
    else if(hour != d2.hour){ return false; }

    if(minute < d2.minute){ return true; }
    else if(minute != d2.minute){  return false; }
      
    return false;
}

bool Date::operator==(const Date &d2) const{
    if(minute != d2.minute)
        return false;

    if(hour != d2.hour)
        return false;

    if(day != d2.day)
        return false;

    if(month != d2.month)
        return false;

    if(year != d2.year)
        return false;

    return true;
}

bool Date::operator>=(const Date &d2) const{
        
    return !(*this <= d2) || (*this==d2);
}

void Date::operator=(const Date &d2){
    year = d2.year;
    month = d2.month;
    day = d2.day;
    hour = d2.hour;
    minute = d2.minute;

    weekDay = d2.weekDay;
}


string Date::DateToString() const{
    string strWeekDay;
    switch(weekDay)
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

    string resultat = strWeekDay + " " + to_string(day) + "/" + to_string(month) + "/" + to_string(year)+ " - " + to_string(hour)+":"+to_string(minute);
   
    return resultat;
}


void Date::Test(){

    Date now;
    srand(time(NULL));


    for(int i=0; i<10; i++){
        Date now_1(now, (rand()%100)/10.);
        Date now_2(now, (rand()%100)/10.);

        cout << "now   : "<<now.DateToString() << endl;
        cout << "now_1 : "<< now_1.DateToString() << endl;
        cout << "now_2 : "<< now_2.DateToString() << endl << endl;

        cout <<"now_1 >= now_2 : "<< (now_1 >= now_2) << endl;
        cout <<"now_1 <= now_2 : "<< (now_1 <= now_2) << endl << endl;

        cout << "now_2 >= now_1 : " << (now_2 >= now_1) << endl;
        cout << "now_2 <= now_1 : " << (now_2 <= now_1) << endl << endl;
        
        
        cout <<"now <= now_1 <= now_2 : "<< now_1.isBetween(now, now_2) << endl;
        cout <<"now <= now_2 <= now_1 : "<< now_2.isBetween(now, now_1) << endl;

        cout << "========================" << endl;
    }
}