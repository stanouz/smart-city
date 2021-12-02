#include "Contenu.h"

#include<iostream>
#include<string>

Contenu::Contenu(){
    duree = 0;
    prix=0;
    texte = "pas de texte";
}

Contenu::Contenu(double d, double _prix, string t){
    duree = d;
    prix = _prix;
    texte = t;
}


string Contenu::to_string(){
    return "durée : " + std::to_string(duree) + "h | prix : " + std::to_string(prix) + " | texte : " + texte;
}

void Contenu::display(){
    cout << to_string();
}

double Contenu::getDuree(){
    return duree;
}

double Contenu:: getPrix(){
    return prix;
}

string Contenu:: getTexte(){
    return texte;
}


void Contenu::setDuree(double d){
    duree = d;
}

void Contenu:: setPrix(double p){
    prix = p;
}

void Contenu:: setTexte(string t){
    texte = t;
}

void Contenu::setTabPlace(int val, int i, int j)
{
    TabPlace[i][j] = val;
}