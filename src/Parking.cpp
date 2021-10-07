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
        if(places[i].getIsOccupied()==false){
            return true;
        }
    }
    return false;
}

void Parking::updatePlacesStatus(){
    for(int i=0; i<places.size(); i++){
        places[i].updateStatus();
    }
}

void Parking::sendMessage(string id_destinataire, Message & m){
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push(m);
}



bool Parking::GetLastUnreadMsg(Message & m){
    if(!BoiteAuxLettres[ID].empty()){
        m = BoiteAuxLettres[ID].front();
        BoiteAuxLettresPrivé.push_back(m);
        BoiteAuxLettres[ID].pop();
        return true;
    }
    return false;
}



void Parking::Boucle(){

    while(true){
        int compteur =0;
        Message recu;
        if(GetLastUnreadMsg(recu)){
            
            if(recu.performatif==DemandePlace){
                bool propositionAccepte = false;
                while(compteur<3 && !propositionAccepte){
                    recu.display();
                    
                
                    Message toSend(ID, Reponse);
                    float prixNegocie = recu.contenuMessage.getPrix();

                    if(prixNegocie >= prix*0.9){
                        toSend.contenuMessage.setTexte("Ok");
                        propositionAccepte=true;
                    }
                    else{
                        toSend.contenuMessage.setTexte("Non");
                    }
                    
                    sendMessage(recu.emmeteur, toSend);

                    while(!GetLastUnreadMsg(recu))
                    {
        
                    }
                    compteur++;
                }
            }
        }
        

        usleep(600000);
    }
}



