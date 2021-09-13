#include "Voiture.h"

Voiture::Voiture(){

}

Voiture::Voiture(Voiture & v){
    immatriculation = v.immatriculation;
}

Voiture::~Voiture(){

}

int Voiture::getImat() const{
    return immatriculation;
}

