#include "PropositionAccepte.h"



PropositionAccepte::PropositionAccepte(double prix_, string ID, double _posX, double _posY){
    prix = prix_;
    ID_parking = ID;
    posX = _posX;
    posY = _posY;
}


PropositionAccepte::~PropositionAccepte(){

}

string PropositionAccepte::getId() const{
    return ID_parking;
}

double PropositionAccepte::getPrix() const{
    return prix;
}

double PropositionAccepte::getPosX()
{
    return posX;
}

double PropositionAccepte::getPosY()
{
    return posY;
}
