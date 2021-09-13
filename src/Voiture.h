#ifndef __VOITURE__
#define __VOITURE__

#include <string>

using namespace std;

class Voiture{
public:
    Voiture();
    ~Voiture();
    string getImat() const;
    void setImat(string & imat);

private:
    string immatriculation;
};

#endif