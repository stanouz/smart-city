#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu(double duree, double _prix, string t);
    Contenu();
    
    void display();

    string to_string();

    double getDuree();
    double getPrix();
    string getTexte();

    void setDuree(double d);
    void setPrix(double _prix);
    void setTexte(string t);
    void setPlaceX(double x);
    void setPlaceY(double y);
    double getPlaceX();
    double getPlaceY();


private:
    double duree; // en heures
    double prix;
    string texte;
    double placeX;
    double placeY;
};

#endif
