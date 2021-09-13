#ifndef __VOITURE__
#define __VOITURE__

#include <string>

using namespace std;

class Voiture{
public:
    Voiture();
    Voiture(Voiture & v);
    ~Voiture();
    string getImat() const;

private:
    string immatriculation;
};

#endif