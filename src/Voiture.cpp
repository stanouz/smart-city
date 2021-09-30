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
    Message m(immatriculation, DemandePlace);
    string mess = "Bonjour";
    m.contenuMessage.setTexte(mess);
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push_back(m);
}

void Voiture::Boucle(){
    
    int i=0;
    
    while(true){
        
        cout << immatriculation << " envoie un msg : "<< i << endl;
        sendMessage("P1");
        
        usleep(1600000);
        i++;
    }
}