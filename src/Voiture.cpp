#include "Voiture.h"
#include <unistd.h>

#include <iostream>

using namespace std;

Voiture::Voiture(){
}

Voiture::Voiture(Voiture & v): Agent(){
    immatriculation = v.immatriculation;
}

Voiture::Voiture(string immat){
    immatriculation = immat;
}

Voiture::~Voiture(){

}

string Voiture::getImat() const{
    return immatriculation;
}

void Voiture::sendMessage(string id_destinataire){
    Message m;
    string mess = "Bonjour";
    m.contenuMessage.texte = mess;
    BoiteAuxLettres[id_destinataire].push_back(m);
}

void Voiture::Boucle(){
    
    for(int i=0; i<5; i++){
        sendMessage("P1");
    }


    while(true){
        
        sendMessage("P1");
        
        usleep(1600000);
    }
}