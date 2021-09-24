#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu();
    Contenu(string obj, Date d, float _prix, string t);
    ~Contenu();
    string getObjet();
    Date getDate();
    float getPrix();
    string getTexte();

    void setObjet(string obj);
    void setDate(Date d);
    void setPrix(float _prix);
    void setTexte(string t);

private:
    string objet;
    Date date;
    float prix;
    string texte;
};

#endif