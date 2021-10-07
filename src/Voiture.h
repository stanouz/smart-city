#ifndef __VOITURE__
#define __VOITURE__

#include <string>
#include "Date.h"
#include "Agent.h"


using namespace std;

class Voiture:public Agent{
public:
    Voiture();
    Voiture(Voiture & v);
    Voiture(string immat);
    ~Voiture();
    string getImat() const;
    void sendMessage(string id_destinataire, Message m);
    void Boucle();
    void negociation(string id_destinataire);
    bool checkLastUnreadMessage(Message & m);

private:
    string immatriculation;
};

#endif