#ifndef __PARKING__
#define __PARKING__

#include <map>
#include <string>
#include <vector>
#include "Place.h"
#include "Agent.h"

using namespace std;

class Parking: public Agent{
    
public:
    Parking();
    ~Parking();
    bool IsCompleted() const;
    void sendMessage();
    string checkMessage();

private:
    int nbPlaces;
    map<string, int> historiqueClient;
    vector<Place> places;
    int grilleTarifaire[7][24];
    bool isCompleted; // pour voir si on a des places disponibles ou pas 
};


#endif