#include "Contenu.h"

Contenu::Contenu(){

}

Contenu::Contenu(Date dd, Date df, float _prix, string t){
    dateDebut = dd;
    dateFin = df;
    prix = _prix;
    texte = t;
}

Contenu::~Contenu(){

}


Date Contenu:: getDateDebut()
{
    return dateDebut;
}

Date Contenu:: getDateFin()
{
    return dateFin;
}

float Contenu:: getPrix()
{
    return prix;
}

string Contenu:: getTexte()
{
    return texte;
}


void Contenu:: setDateDebut(Date d)
{
    dateDebut = d;
}

void Contenu:: setDateFin(Date d)
{
    dateFin = d;
}

void Contenu:: setPrix(float p)
{
    prix = p;
}

void Contenu:: setTexte(string t)
{
    texte = t;
}