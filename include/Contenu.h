#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu(Date dateDebut, double duree, double _prix, string t);
    Contenu();
    void operator=(Contenu c);
    
    void display();

    string to_string();

    double getDuree();
    double getPrix();
    string getTexte();
    Date getDate();

    void setDuree(double d);
    void setPrix(double _prix);
    void setTexte(string t);
    void setDate(Date d);
private:
    double duree; // en heures
    Date dateDebut;
    double prix;
    string texte;
};

#endif