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
    vector<vector<int> > map;

    vector<thread> tabThreads;
public:
    Ville();
    ~Ville();

    vector<Parking> & getTabParkings();
    vector<Voiture> & getTabVoitures();
    vector<vector<int> > & getMap();

    bool immatExists(string immat);
    string randomImmat();

};


#endif