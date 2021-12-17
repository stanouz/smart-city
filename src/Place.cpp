#include "Place.h"

#include <iostream>

using namespace std;

Place::Place(){
    isOccupied=false;
}

Place::~Place(){
}

string Place::getOccupant(){
    return reservation.getID();
}

Date Place::getDateDepart(){
    return reservation.getDateDepart();
}

bool Place::getIsOccupied(){
    return isOccupied;
}


string Place::updateStatus(){
    if(isOccupied){
        if(reservation.dateDepartPasse()){
            isOccupied = false;
            return reservation.getID();
        }
    }
        
    return "NULL";
}


bool Place::addReservations(string immat, double duree){
    if(isOccupied)
        return false;

    reservation = Reservation(duree, immat);
    isOccupied = true;
    return true;
}
