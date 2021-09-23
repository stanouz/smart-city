#include "Place.h"

Place::Place(){
}

Place::~Place(){
}

int Place::getID() const{
    return ID;
}

const vector<Reservation> & Place::getReservations() const{
    return reservations;
}

bool Place::GetIsOccupied() const{
    return isOccupied;
}