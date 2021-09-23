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
    ~Voiture();
    string getImat() const;
    void sendMessage();

private:
    string immatriculation;
};

#endif