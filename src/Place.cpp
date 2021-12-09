#include "Place.h"

#include <iostream>

using namespace std;

Place::Place(){
    isOccupied=false;
}

Place::~Place(){
}

string Place::getOccupant(){
    return agenda.getCurrendID();
}

Date Place::getDateDepart(){
    return agenda.getCurrentDateFin();
}

bool Place::getIsOccupied(){
    return isOccupied;
}


string Place::updateStatus(){
    string retour = agenda.UpdateCurrentReservation();

    if(retour!="NULL"){
        isOccupied = false;
    }

    if(agenda.UpdateNextReservations()){
        isOccupied = true;
    }

    return "NULL";
}


bool Place::addReservations(Reservation newReserv){
    return agenda.AddReservation(newReserv);
}
