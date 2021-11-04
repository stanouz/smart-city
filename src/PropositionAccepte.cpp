#include "PropositionAccepte.h"



PropositionAccepte::PropositionAccepte(double prix_, string ID){
    prix = prix_;
    ID_parking = ID;

}


PropositionAccepte::~PropositionAccepte(){

}

string PropositionAccepte::getId() const{
    return ID_parking;
}

double PropositionAccepte::getPrix() const{
    return prix;
}