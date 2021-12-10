#include "Reservation.h"

#include <iostream>

using namespace std;

Reservation::Reservation(){
    dateFin = Date();
    dateDebut = Date();
    ID = "NULL";
}


Reservation::Reservation(Date dateDeb, double duree, string id_):
    dateDebut(dateDeb), dateFin(dateDeb, duree){
    ID = id_;
}



void Reservation::operator=(Reservation r){
    dateDebut = r.dateDebut;
    dateFin = r.dateFin;
    ID = r.ID;
}

Date & Reservation::getDateDebut(){
    return dateDebut;
}

Date & Reservation::getDateFin(){
    return dateFin;
}

bool Reservation::dateDebutPasse(){
    Date now;
    return dateDebut <= now; 
}

bool Reservation::dateFinPasse(){
    Date now;
    return dateFin <= now; 
}

bool Reservation::intersectionDate(Reservation & resa){

    

    
    return dateDebut.isBetween(resa.dateDebut, resa.dateFin) ||  
           dateFin.isBetween(resa.dateDebut, resa.dateFin)   ||
           resa.dateDebut.isBetween(dateDebut, dateFin)      ||
           resa.dateFin.isBetween(dateDebut, dateFin);
}


string Reservation::getID(){
    return ID;
}



void Reservation::reset(){
    ID = "NULL";
}