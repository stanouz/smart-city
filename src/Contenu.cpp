#include "Contenu.h"

Contenu::Contenu(){

}

Contenu::Contenu(string obj, Date d, float _prix, string t){
    objet = obj;
    date = d;
    prix = _prix;
    texte = t;
}

Contenu::~Contenu(){

}

string Contenu:: getObjet()
{
    return objet;
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

void Contenu:: setObjet(string obj)
{
    objet = obj;
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