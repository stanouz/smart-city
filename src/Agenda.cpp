#include "Agenda.h"

bool Agenda::AddReservation(Reservation newReservation){
    if(newReservation.intersectionDate(currentReservation)){
        return false;
    }

    for(int i=0; i<(int)nextReservations.size(); i++){
        if(newReservation.intersectionDate(nextReservations[i])){
            return false;
        }
    }   

    nextReservations.push_back(newReservation);
    return true;
}


string Agenda::UpdateCurrentReservation(){
    if(currentReservation.getID()!="NULL"){
        if(currentReservation.dateFinPasse()){
            string tmp_occupant = currentReservation.getID();
            currentReservation.reset();
          
            return tmp_occupant;
        }
    }
    return "NULL";
}


bool Agenda::UpdateNextReservations(){
    for(int i=0; i<(int)nextReservations.size(); i++){
        if(nextReservations[i].dateDebutPasse()){
            currentReservation = nextReservations[i];
            nextReservations.erase(nextReservations.begin()+i);
            return true;
        }
    }

    return false;
}


string Agenda::getCurrendID(){
    return currentReservation.getID();
}

Date Agenda::getCurrentDateFin(){
    return currentReservation.getDateFin();
}