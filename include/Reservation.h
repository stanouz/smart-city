#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include "Date.h"
#include <string>

using namespace std;

class Reservation{
private:
    Date dateDebut;
    Date dateFin;
    string ID;
public:
    Reservation();
    Reservation(Date dateDeb, double duree, string ID); // duree en heures

    void operator=(Reservation r);

    bool dateDebutPasse();
    bool dateFinPasse();
    bool intersectionDate(Reservation & resa);

    string getID();
    Date & getDateDebut();
    Date & getDateFin();

    void reset();

    
};


#endif

