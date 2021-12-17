#ifndef __RESERVATION_H__
#define __RESERVATION_H__

#include "Date.h"
#include <string>

using namespace std;

class Reservation{
private:
    Date dateDepart;
    string ID;
public:
    Reservation();
    Reservation(double duree, string ID); // duree en heures

    void operator=(Reservation r);

    bool dateDepartPasse();

    string getID();
    Date & getDateDepart();    
};


#endif

