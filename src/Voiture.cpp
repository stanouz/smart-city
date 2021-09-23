#include "Voiture.h"

Voiture::Voiture(){

}

Voiture::Voiture(Voiture & v){
    immatriculation = v.immatriculation;
}

Voiture::~Voiture(){

}

string Voiture::getImat() const{
    return immatriculation;
}

Voiture::sendMessage(){
    Message m;
    string mess = "Bonjour";
    m.contenu.texte = mess;
    BoiteAuxLettres[0].pushback(m);
}