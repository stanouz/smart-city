#include "PropositionAccepte.h"



PropositionAccepte::PropositionAccepte(double prix_, string ID, int _posX, int _posY){
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

int PropositionAccepte::getPosX()
{
    return posX;
}

int PropositionAccepte::getPosY()
{
    return posY;
}