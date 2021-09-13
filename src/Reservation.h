#ifndef __RESERVATION__
#define __RESERVATION__

#include "Date.h"
#include "Voiture.h"

class Reservation{
public:
    Reservation();
    Reservation(Date & d1, Date & d2, Voiture & v);
    ~Reservation();

private:
    Date dateDebut;
    Date dateFin;
    Voiture voiture;
};

#endif