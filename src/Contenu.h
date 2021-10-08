#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu();
    Contenu(int duree, float _prix, string t);
    ~Contenu();

    void display() const;


    int getDuree();
    float getPrix();
    string getTexte();

    void setDuree(int d);
    void setPrix(float _prix);
    void setTexte(string t);

private:
    int duree; // en heures
    float prix;
    string texte;
};

#endif