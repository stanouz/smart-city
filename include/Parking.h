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
    int tabP1[10][2] = {10,11,9,10,9,9,9,8,9,7,10,11,10,10,10,9,10,8,10,7};
    //int tabP1[10][2] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int indX,indY;
};


#endif