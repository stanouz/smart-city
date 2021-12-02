#ifndef __PROP_ACCEPTE_H__
#define __PROP_ACCEPTE_H__

#include <string>

using namespace std;

class PropositionAccepte{
    double prix;
    string ID_parking;
    int posX,posY;
public:
    PropositionAccepte(double prix, string ID, int posX, int posY);
    ~PropositionAccepte();
    string getId() const;
    double getPrix() const;
    int getPosX();
    int getPosY();
};


#endif
