#include "Contenu.h"

Contenu::Contenu(){

}

Contenu::Contenu(Date d, float _prix, string t){
    date = d;
    prix = _prix;
    texte = t;
}

Contenu::~Contenu(){

}


Date Contenu:: getDate()
{
    return date;
}

float Contenu:: getPrix()
{
    return prix;
}

string Contenu:: getTexte()
{
    return texte;
}


void Contenu:: setDate(Date d)
{
    date = d;
}

void Contenu:: setPrix(float p)
{
    prix = p;
}

void Contenu:: setTexte(string t)
{
    texte = t;
}