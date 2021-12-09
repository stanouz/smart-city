#ifndef __PLACE__
#define __PLACE__

#include "Reservation.h"
#include <vector>

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    string getOccupant();
    bool getIsOccupied();
    Date & getDateDepart();

 
    string updateStatus();

    bool addReservations(Reservation newReserv);

private:
    vector<Reservation> reservationFutures;
    Reservation reservationEnCours;
    bool isOccupied;
};



#endif