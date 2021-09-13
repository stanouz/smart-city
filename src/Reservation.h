#ifndef __RESERVATION__
#define __RESERVATION__

#include "Date.h"
#include "Voiture.h"

class Reservation{
public:
    Reservation();
    ~Reservation();

private:
    Date dateDebut;
    Date dateFin;
    Voiture voiture;
};

#endif