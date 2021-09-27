#include "Parking.h"

#include <unistd.h>
#include <iostream>

using namespace std;

Parking::Parking(){
    /*
    for(int j=0; j<24; j++){
        grilleTarifaire[0][j]= 5;
        grilleTarifaire[1][j]= 5;
        grilleTarifaire[2][j]= 5;
        grilleTarifaire[3][j]= 5;
        grilleTarifaire[4][j]= 5;
        grilleTarifaire[5][j]= 10;
        grilleTarifaire[6][j]= 10;
    }*/
    
}

Parking::Parking(string id){
    ID = id;
}

Parking::~Parking(){

}

void Parking::sendMessage(string id_destinataire){
    Message m;
    string mess = "Bonjour";
    m.contenuMessage.texte = mess;
    m.emmeteur = ID;
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push_back(m);
}

string Parking::checkMessage(){
    int size = BoiteAuxLettres[ID].size();
    if(size>0 && (size-1)!=lastRead){
        string msg = BoiteAuxLettres[ID][lastRead].contenuMessage.texte+" "+to_string(lastRead);
        string emmeteur = BoiteAuxLettres[ID][lastRead].emmeteur;
        lastRead ++;
        return ID + " : Reçu de " +emmeteur + " : " + msg;
    }
        
    return ID + " : Pas de nouveau message : "+to_string(lastRead)+" messages déjà lu.";
}

void Parking::Boucle(){

    while(true){
        
        cout << checkMessage() << endl;

        usleep(600000);
    }
}

bool Parking::IsFull() const{
    for(int i=0; i<places.size(); i++){
        if(places[i].GetIsOccupied()==false){
            return true;
        }
    }
    return false;
}

