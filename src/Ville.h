#ifndef __VILLE_H__
#define __VILLE_H__

#include <vector>
#include <thread>

#include "Parking.h"
#include "Voiture.h"

using namespace std;

class Ville{
private:
    vector<Parking> tab_parkings;
    vector<Voiture> tab_voitures;

public:
    Ville();
    ~Ville();

    void lancerThread();

    vector<Parking> & getTabParkings();
    vector<Voiture> & getTabVoitures();
};


#endif