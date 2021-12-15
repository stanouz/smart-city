#include "Reservation.h"

#include <iostream>

using namespace std;

Reservation::Reservation(){
    dateDepart = Date();
    ID = "NULL";
}


Reservation::Reservation(double duree, string id_){
    Date now;
    dateDepart = Date(now, duree);
    ID = id_;
}



void Reservation::operator=(Reservation r){
    dateDepart = r.dateDepart;
    ID = r.ID;
}



Date & Reservation::getDateDepart(){
    return dateDepart;
}


bool Reservation::dateDepartPasse(){
    Date now;
    return dateDepart <= now; 
}


string Reservation::getID(){
    return ID;
}
