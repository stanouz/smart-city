#ifndef __PLACE__
#define __PLACE__

#include "Date.h"
#include <vector>

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    string getOccupant() const;
    bool getIsOccupied() const;
    Date getOccupiedUntil() const;
    string updateStatus();
    bool ajouteVoiture(string immat, Date dateDepart);


private:
    Date occupiedUntil;
    bool isOccupied;
    string occupant;
};



#endif
