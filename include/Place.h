#ifndef __PLACE__
#define __PLACE__

#include "Agenda.h"

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    string getOccupant();
    bool getIsOccupied();
    Date getDateDepart();

 
    string updateStatus();
    bool addReservations(Reservation newReserv);

private:
    Agenda agenda;
    bool isOccupied;
};



#endif