#include "Place.h"

#include <iostream>

using namespace std;

Place::Place(){
    isOccupied=false;
    occupant="NULL";
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


bool Place::updateStatus(){
    if(isOccupied){
        Date now;
        if(now >= occupiedUntil){
            cout << "       La voiture " << occupant << " s'en va" << endl;
            isOccupied=false;
            occupant = "NULL";
            return true;
        }
    }
    return false;
}


bool Place::ajouteVoiture(string occupant_, Date dateDepart){
    if(isOccupied){
        return false;
    }
    occupiedUntil = dateDepart;
    cout << "       La voiture " << occupant_ << " se gare et partira le " << dateDepart << endl;
    occupant = occupant_;
    isOccupied = true;
    return true;
}

