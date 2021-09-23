#include "Voiture.h"

Voiture::Voiture(){

}

Voiture::Voiture(Voiture & v): Agent(){
    immatriculation = v.immatriculation;
}

Voiture::~Voiture(){

}

string Voiture::getImat() const{
    return immatriculation;
}

void Voiture::sendMessage(){
    Message m;
    string mess = "Bonjour";
    m.contenuMessage.texte = mess;
    BoiteAuxLettres[0].push_back(m);
}