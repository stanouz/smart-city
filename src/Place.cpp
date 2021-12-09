#include "Place.h"

#include <iostream>

using namespace std;

Place::Place(){
    isOccupied=false;
}

Place::~Place(){
}

string Place::getOccupant(){
    if(isOccupied){
        return reservationEnCours.getImmatriculation();
    }
    return "NULL";
}

Date & Place::getDateDepart(){
    return reservationEnCours.getDateFin();
}

bool Place::getIsOccupied(){
    return isOccupied;
}


string Place::updateStatus(){
    if(isOccupied){
        if(reservationEnCours.dateFinPasse()){
            cout << "La date de fin " << reservationEnCours.getDateFin().DateToString() << " est passée " << endl;
            
            string tmp_occupant = getOccupant();
            isOccupied=false;
          
            return tmp_occupant;
        }
    }


    int i=0;
    while(!isOccupied && i<(int)reservationFutures.size()){

        if(reservationFutures[i].dateDebutPasse()){
            reservationEnCours = reservationFutures[i];
            reservationFutures.erase(reservationFutures.begin()+i);
            isOccupied = true;
        }


        i++;
    }


    return "NULL";
}


bool Place::addReservations(Reservation newReserv){

    if(newReserv.intersectionDate(reservationEnCours)){
        return false;
    }

    for(int i=0; i<(int)reservationFutures.size(); i++){
        if(newReserv.intersectionDate(reservationFutures[i])){
            return false;
        }
    }   

    reservationFutures.push_back(newReserv);
    return true;
}
