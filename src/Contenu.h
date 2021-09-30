#ifndef __CONTENU__
#define __CONTENU__

#include <string>
#include "Date.h"

using namespace std;

class Contenu{
public:
    Contenu();
    Contenu( Date d, float _prix, string t);
    ~Contenu();
    Date getDate();
    float getPrix();
    string getTexte();

    void setDate(Date d);
    void setPrix(float _prix);
    void setTexte(string t);

private:
    Date date;
    float prix;
    string texte;
};

#endif