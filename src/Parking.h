#ifndef __PARKING__
#define __PARKING__

#include <map>
#include <string>
#include <vector>
#include "Place.h"

using namespace std;

class Parking{
    
public:
    Parking();
    ~Parking();
private:
    int nbPlaces;
    map<string, int> historiqueClient;
    vector<Place> places;
};


#endif