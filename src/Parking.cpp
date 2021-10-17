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
        BoiteAuxLettresPrive.push_back(m);
        BoiteAuxLettres[ID].pop();
        return true;
    }
    return false;
}

void Parking::processusNegocitation(){
    Message recu;

    // Si pas de message recu on quitte la fonction
    if(!GetLastUnreadMsg(recu)){
        return;
    }
    else{
        // Si il y a un message recu mais ce n'est pas une demande de 
        // place on quitte aussi
        if(recu.performatif!=DemandePlace){
            return;
        }
    }


    int compteur =0;
    Message toSend(ID, Reponse);
    while(compteur<3){
        

        cout << "===== COMPTEUR " << compteur << "=======" << endl;
        recu.display();
        float prixDemande = recu.contenuMessage.getPrix();
        
        if(prixDemande >= prix*0.9){
            // Si la proposition est accepté on previent la voiture et 
            // on quitte le processus de négociation.
            toSend.contenuMessage.setTexte("Proposition acceptée");
            sendMessage(recu.emmeteur, toSend);

            // Appeller une fonction qui gare la voiture à la première place 
            // libre
            return;
        }
        else{
            toSend.contenuMessage.setTexte("Proposition refusée");
            sendMessage(recu.emmeteur, toSend);
        }
                    

        // Boucle bloquant l'attente d'un nouveau message
        while(!GetLastUnreadMsg(recu)){
            cout << "Boucle d'attente" << endl;
        }
        
        compteur++;
    }
}


void Parking::Boucle(){

    while(true){

        processusNegocitation();
        

        usleep(600000);
    }
}



