#include "Voiture.h"

Voiture::Voiture(){

}

Voiture::~Voiture(){

}

string Voiture::getImat() const{
    return immatriculation;
}

void Voiture::setImat(string & imat){
    immatriculation = imat;
}