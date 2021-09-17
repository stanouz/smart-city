#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED

#include "Voiture.h"

class utilisateur
{
private:
    int age;
    char sexe;
    string nom;
    bool handicap;
    Voiture voiture;

public:
    utilisateur();
    ~utilisateur();

};

#endif // UTILISATEUR_H_INCLUDED
