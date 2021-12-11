#include "Contenu.h"

#include<iostream>
#include<string>

Contenu::Contenu():dateDebut(){
    duree = 0;
    prix=0;
    texte = "pas de texte";
}

Contenu::Contenu(Date date, double d, double _prix, string t){
    dateDebut = date;
    duree = d;
    prix = _prix;
    texte = t;
}

void Contenu::operator=(Contenu c){
    dateDebut = c.dateDebut;
    duree = c.duree;
    prix = c.prix;
    texte = c.texte;

    posX = c.posX;
    posY = c.posY;
    direction = c.direction;
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

Date Contenu::getDate(){
    return dateDebut;
}


void Contenu::setDuree(double d){
    duree = d;
}

void Contenu::setPrix(double p){
    prix = p;
}

void Contenu::setTexte(string t){
    texte = t;
}


void Contenu::setDate(Date d){
    dateDebut = d;
}