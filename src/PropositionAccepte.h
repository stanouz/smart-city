#ifndef __PROP_ACCEPTE_H__
#define __PROP_ACCEPTE_H__

#include <string>

using namespace std;

class PropositionAccepte{
    double prix;
    string ID_parking;
public:
    PropositionAccepte(double prix, string ID);
    ~PropositionAccepte();
    string getId() const;
    double getPrix() const;
};


#endif
