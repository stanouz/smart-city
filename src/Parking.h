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
    bool IsCompleted() const;
private:
    int nbPlaces;
    map<string, int> historiqueClient;
    vector<Place> places;
    int grilleTarifaire[7][24];
    bool isCompleted; // pour voir si on a des places disponibles ou pas 
};


#endif