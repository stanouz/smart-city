#ifndef __PLACE__
#define __PLACE__

#include "Reservation.h"
#include <vector>

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    int getID() const;
    vector<Reservation> getReservations() const;
    bool GetIsOccupied() const;

private:
    int ID;
    vector<Reservation> reservations;
    bool isOccupied;

};



#endif