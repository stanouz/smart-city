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

    void Boucle();
    void negociation(string id_destinataire, double prixPopositionPrecedente);
   
    void premierMessage(string id_destinataire);
    void processusNegocition();

private:
    string immatriculation;
};

#endif