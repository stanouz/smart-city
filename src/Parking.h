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
    Parking(string id);
    ~Parking();
    bool IsFull() const;

    

    void updatePlacesStatus();
    void Boucle();

    void processusNegocitation();
    void propositionAcceptee(Message recu);
    void propositionRefusee(Message recu, int compteur);
    double prixFinal(float duree);
    void ajouteVoiture(string occupant, Date dateDepart);
    double pourcentageRemplissage();

private:
    Place tabPlaces[100];
    const int NB_PLACES_TOTAL = 100;
    int nb_place_occup;
    float prix;
    string ID;
};


#endif