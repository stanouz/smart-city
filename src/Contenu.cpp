#include "Contenu.h"

#include<iostream>

Contenu::Contenu(){
    prix=0;
    texte = "pas de texte";
}

Contenu::Contenu(Date dd, Date df, float _prix, string t){
    dateDebut = dd;
    dateFin = df;
    prix = _prix;
    texte = t;
}

Contenu::~Contenu(){

}


void Contenu::display() const{
    cout << "Date début : " << dateDebut << " | Date Fin : " << dateFin << " | prix : " << prix << " | texte : " << texte << endl;
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