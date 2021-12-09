#ifndef __AGENDA_H__
#define __AGENDA_H__

#include <vector>
#include <string>

#include "Reservation.h"

using namespace std;


class Agenda{
    Reservation currentReservation;
    vector<Reservation> nextReservations;
public:
    bool AddReservation(Reservation newReservation);

    string UpdateCurrentReservation();
    bool UpdateNextReservations();

    string getCurrendID();
    Date getCurrentDateFin();
};

#endif
 