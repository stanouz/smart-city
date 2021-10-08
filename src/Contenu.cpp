#include "Contenu.h"

#include<iostream>

Contenu::Contenu(){
    duree = 0;
    prix=0;
    texte = "pas de texte";
}

Contenu::Contenu(int d, float _prix, string t){
    duree = d;
    prix = _prix;
    texte = t;
}

Contenu::~Contenu(){

}


void Contenu::display() const{
    cout << " | durée : " << duree << "h | prix : " << prix << " | texte : " << texte << endl;
}

int Contenu::getDuree(){
    return duree;
}

float Contenu:: getPrix()
{
    return prix;
}

string Contenu:: getTexte()
{
    return texte;
}


void Contenu::setDuree(int d){
    duree = d;
}

void Contenu:: setPrix(float p)
{
    prix = p;
}

void Contenu:: setTexte(string t)
{
    texte = t;
}