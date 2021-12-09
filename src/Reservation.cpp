#include "Reservation.h"

#include <iostream>

using namespace std;

Reservation::Reservation(){

}


Reservation::Reservation(Date dateDeb, double duree, string immat):
    dateDebut(dateDeb), dateFin(dateDeb, duree){
    immatriculation = immat;
}



void Reservation::operator=(Reservation r){
    dateDebut = r.dateDebut;
    dateFin = r.dateFin;
    immatriculation = r.immatriculation;
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


string Reservation::getImmatriculation(){
    return immatriculation;
}



void Reservation::reset(){
    immatriculation = "NULL";
}