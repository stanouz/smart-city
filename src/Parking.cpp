#include "Parking.h"

#include <unistd.h>
#include <iostream>

using namespace std;

Parking::Parking(){
    prix = 5.;
}

Parking::Parking(string id){
    ID = id;
    prix = 5.;
}

Parking::~Parking(){

}

bool Parking::IsFull() const{
    for(int i=0; i<(int)places.size(); i++){
        if(places[i].GetIsOccupied()==false){
            return true;
        }
    }
    return false;
}

void Parking::sendMessage(string id_destinataire, Message & m){
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push_back(m);
}



string Parking::checkMessage(){
    int size = BoiteAuxLettres[ID].size();
    if(size>0 && (size-1)!=lastRead){
        string msg = BoiteAuxLettres[ID][lastRead].contenuMessage.getTexte()+" "+to_string(lastRead);
        Date date = BoiteAuxLettres[ID][lastRead].contenuMessage.getDateDebut();
        float p = BoiteAuxLettres[ID][lastRead].contenuMessage.getPrix();
        string emmeteur = BoiteAuxLettres[ID][lastRead].emmeteur;
        lastRead ++;
        return ID + " : Reçu de " +emmeteur + " : " + msg + "Date :" + date.DateToString() + "Prix : " + to_string(p);
    }
        
    return ID + " : Pas de nouveau message : "+to_string(lastRead)+" messages déjà lu.";
}



Message & Parking::GetLastUnreadMsg(){
    lastRead++;
    return BoiteAuxLettres[ID][lastRead-1];
}



void Parking::Boucle(){

    while(true){
        int size = BoiteAuxLettres[ID].size();
    
        if(size > 0 && size!=lastRead){
            Message recu = GetLastUnreadMsg();
            recu.display();
            if(recu.performatif==DemandePlace){
                Message toSend(ID, Reponse);
                float prixNegocie = recu.contenuMessage.getPrix();

                if(prixNegocie >= prix*0.9){
                    toSend.contenuMessage.setTexte("Ok");
                }
                else{
                    toSend.contenuMessage.setTexte("Non");
                }

                
                sendMessage(recu.emmeteur, toSend);
            }
        }
        

        usleep(600000);
    }
}



