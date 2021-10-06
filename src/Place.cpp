#include "Place.h"

Place::Place(){
}

Place::~Place(){
}

int Place::getID() const{
    return ID;
}

bool Place::getIsOccupied() const{
    return isOccupied;
}

Date Place::getOccupiedUntil() const{
    return occupiedUntil;
}


void Place::updateStatus(){
    if(isOccupied){
        Date now;
        if(now >= occupiedUntil){
            isOccupied==false;
        }
    }
}

