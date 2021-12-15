#ifndef __PARKING__
#define __PARKING__

#include <map>
#include <string>
#include <vector>
#include "Place.h"
#include "Agent.h"
#include "Enums.h"
#include "Position.h"

using namespace std;

class Parking: public Agent{
    
public:
    Parking(string id, int posX, int posY, Direction orient);
    ~Parking();
    
    bool IsFull() const;

    

    void updatePlacesStatus();
    void Boucle();

    void processusNegocitation();
    void propositionAcceptee(Message recu);
    void propositionRefusee(Message recu, int compteur);
    double prixFinal(float duree, string immatriculation);
    void ajouteVoiture(Date dateDebut, double duree, string occupant);
    double pourcentageRemplissage();

    string getId();
    int getNbplace();
    int getNbPlaceOccupe();
    Place & getPlace(int ind);

    double getMoyennePrix();


    Position getPlacePosition_Orientation(int ind);
private:
    Place tabPlaces[10];
    const int NB_PLACES_TOTAL = 10;
    int nb_place_occup;
    float prix;
    string ID;

    
    double sommePrix;
    int compteurVoitureGare;
    map<string, double> score;

    Position position;
    vector<Position> position_sorties;
};


#endif