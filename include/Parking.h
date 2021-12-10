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
    Parking(string id);
    
    
    bool IsFull() const;

    

    void updatePlacesStatus();
    void Boucle();

    void processusNegocitation();
    void propositionAcceptee(Message recu);
    void propositionRefusee(Message recu, int compteur);
    double prixFinal(float duree, string immatriculation);
    void ajouteVoiture(string occupant, Date dateDepart);
    double pourcentageRemplissage();

    string getId();
    int getNbplace();
    int getNbPlaceOccupe();
    Place & getPlace(int ind);
    
private:
    Place tabPlaces[10];
    const int NB_PLACES_TOTAL = 10;
    int nb_place_occup;
    float prix;
    string ID;
    map<string, double> score;
    double tabP1x[2] = {10.,13.};
    double tabP1y[5] = {7.2,8.2,9.2,10.2,11.2};

    double tabP2x[2] = {17.,20.};
    double tabP2y[5] = {19.,20.,21.,22.,23.};
    int indX,indY;
};


#endif