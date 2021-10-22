#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu();
    Contenu(double duree, float _prix, string t);
    ~Contenu();

    void display() const;


    double getDuree();
    float getPrix();
    string getTexte();

    void setDuree(double d);
    void setPrix(float _prix);
    void setTexte(string t);

private:
    double duree; // en heures
    float prix;
    string texte;
};

#endif