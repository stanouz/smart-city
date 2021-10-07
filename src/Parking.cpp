#include "Parking.h"

#include <unistd.h>
#include <iostream>

using namespace std;

Parking::Parking(){
    prix = 5.;
    nb_place_occup = 0;
}

Parking::Parking(string id){
    ID = id;
    prix = 5.;
    nb_place_occup = 0;
}

Parking::~Parking(){

}

bool Parking::IsFull() const{
    if(nb_place_occup<NB_PLACES_TOTAL){
        return false;
    }
    return true;
}

void Parking::updatePlacesStatus(){
    for(int i=0; i<NB_PLACES_TOTAL; i++){
        tabPlaces[i].updateStatus();
    }
}

int Parking::pourcentageUtilisation()
{
    return nb_place_occup/NB_PLACES_TOTAL*100;
}

void Parking::sendMessage(string id_destinataire, Message & m){
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push(m);
}

void Parking::placeVoiture()
{
    
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
        

        cout << endl<<endl<<endl<<"===== COMPTEUR " << compteur << "=======" << endl;
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
            toSend.contenuMessage.setPrix(prix + 0.1*prix);
            sendMessage(recu.emmeteur, toSend);
        }
                    

        // Boucle bloquant l'attente d'un nouveau message
        while(!GetLastUnreadMsg(recu)){
            //cout << "Boucle d'attente" << endl;
        }
        
        compteur++;
    }
}


void Parking::Boucle(){

    while(!IsFull()){

        processusNegocitation();
        

        usleep(600000);
    }
}



