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
    void sendMessage(string id_destinataire, Message & m);
    void negociation();
    bool GetLastUnreadMsg(Message & msg, string emeteur);
    bool GetLastUnreadMsg(Message & msg);
    void updatePlacesStatus();
    void Boucle();
    void processusNegocitation();
    double pourcentageRemplissage();
    void ajouteVoiture(string occupant, Date dateDepart);

private:
    Place tabPlaces[100];
    const int NB_PLACES_TOTAL = 100;
    int nb_place_occup;
    float prix;
    string ID;
};


#endif