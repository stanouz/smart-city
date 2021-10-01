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
    string checkMessage();
    Message & GetLastUnreadMsg();
    void Boucle();

private:
    map<string, int> historiqueClient;
    vector<Place> places;
    float prix;
    string ID;
};


#endif