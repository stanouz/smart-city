#ifndef __PARKING__
#define __PARKING__

#include <map>
#include <string>
#include <vector>
#include "Place.h"
#include "Agent.h"
#include "Enums.h"

using namespace std;

class Parking: public Agent{
    
public:
    Parking(string id, int posX, int posY, Orientation orient);
    ~Parking();
    
    bool IsFull() const;

    

    void updatePlacesStatus();
    void Boucle();

    void processusNegocitation();
    void propositionAcceptee(Message recu);
    void propositionRefusee(Message recu, int compteur);
    double prixFinal(float duree);
    void ajouteVoiture(Date dateDebut, double duree, string occupant);
    double pourcentageRemplissage();

    string getId();
    int getNbplace();
    int getNbPlaceOccupe();
    Place & getPlace(int ind);

    double getMoyennePrix();


    void getPlacePosition_Orientation(int ind, double & X, double & Y, Direction & dir);
private:
    Place tabPlaces[10];
    const int NB_PLACES_TOTAL = 10;
    int nb_place_occup;
    float prix;
    string ID;

    
    double sommePrix;
    int compteurVoitureGare;


    int posX, posY;
    Orientation orientation;
};


#endif