#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu();
    Contenu( Date dd, Date df, float _prix, string t);
    ~Contenu();
    Date getDateDebut();
    Date getDateFin();
    float getPrix();
    string getTexte();

    void setDateDebut(Date d);
    void setDateFin(Date d);
    void setPrix(float _prix);
    void setTexte(string t);

private:
    Date dateDebut;
    Date dateFin;
    float prix;
    string texte;
};

#endif