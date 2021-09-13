#include "Reservation.h"

Reservation::Reservation(){

}

Reservation::Reservation(Date & d1, Date & d2, Voiture & v){
    if(d1 <= d2){
        dateDebut = d1;
        dateFin = d2;
    }
    else{
        dateDebut = d2;
        dateFin = d1;
    }
    voiture = v;
}

Reservation::~Reservation(){

}