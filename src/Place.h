#ifndef __PLACE__
#define __PLACE__

#include "Date.h"
#include <vector>

using namespace std;

class Place{
public:
    Place();
    ~Place();
    
    int getID() const;
    bool getIsOccupied() const;
    Date getOccupiedUntil() const;
    void updateStatus();


private:
    int ID;
    Date occupiedUntil;
    bool isOccupied;
};



#endif