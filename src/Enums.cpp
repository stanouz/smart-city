#include "Enums.h"

void nextDay(WeekDay & wd, int nbDays){
    for(int i=0; i<nbDays; i++){
        switch(wd){
            case monday: wd = tuesday ; break;
            case tuesday: wd = wednesday ; break;
            case wednesday: wd = thursday ; break;
            case thursday: wd = friday ; break;
            case friday: wd = saturday; break;
            case saturday: wd = sunday ; break;
            case sunday: wd = monday ; break;
            default: break;
        }
    }
}


string dayToString(WeekDay wd){
    string day = "monday";
    switch(wd){
            case tuesday: day = "tuesday" ; break;
            case wednesday: day = "wednesday" ; break;
            case thursday: day = "thursday" ; break;
            case friday: day = "friday"; break;
            case saturday: day = "saturday" ; break;
            case sunday: day = "sunday" ; break;
            default: break;
    }
    return day;
}