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

