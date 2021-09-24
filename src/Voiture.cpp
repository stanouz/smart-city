#include "Voiture.h"
#include <unistd.h>

#include <iostream>

using namespace std;

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

void Voiture::Boucle(){
    
    time_t currentTime = time(0);
    tm * ltm = localtime(&currentTime);
    int sec;
    
    for(int i=0; i<5; i++){
        sendMessage();
    }


    while(true){
        sec = ltm->tm_sec;
        
        sendMessage();
        
        usleep(1600000);
    }
}