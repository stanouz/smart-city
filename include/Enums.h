#ifndef __ENUMS_H__
#define __ENUMS_H__

#include <string>

using namespace std;


enum Direction{Haut, Bas, Gauche, Droite, Horizontal, Vertical, Aucune};
enum Performatif{DemandePlace, Reponse, Refut, Accepter, LibererPlace, PositionPlace};
enum WeekDay{monday, tuesday, wednesday, thursday, friday, saturday, sunday};



void nextDay(WeekDay & wd, int nbDays);
string dayToString(WeekDay wd);


#endif