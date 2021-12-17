#ifndef __PLACE__
#define __PLACE__

#include "Reservation.h"

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    string getOccupant();
    bool getIsOccupied();
    Date getDateDepart();

 
    string updateStatus();
    bool addReservations(string immat, double duree);

private:
    Reservation reservation;
    bool isOccupied;
};



#endif