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
        if(tabPlaces[i].updateStatus()){
            nb_place_occup--;
        }
        
    }
}

double Parking::pourcentageRemplissage()
{
    return (nb_place_occup/NB_PLACES_TOTAL)*100;
}

void Parking::sendMessage(string id_destinataire, Message & m){
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push(m);
}

void Parking::ajouteVoiture(string occupant, Date dateDepart){

    int i=0;
    bool ajouter = false;
    while(i<NB_PLACES_TOTAL && !ajouter){
        ajouter = tabPlaces[i].ajouteVoiture(occupant, dateDepart);
    }
    if(ajouter){
        nb_place_occup++;
    }
}




bool Parking::GetLastUnreadMsg(Message & m, string emeteur){
    if(!BoiteAuxLettres[ID].empty()){
        Message tmp;
        tmp = BoiteAuxLettres[ID].front();
        if(emeteur=="NULL"){
            m = tmp;
            BoiteAuxLettresPrivé.push_back(m);
            BoiteAuxLettres[ID].pop();
            return true;
        }
        else{
            if(emeteur==tmp.emmeteur){
                m = tmp;
                BoiteAuxLettresPrivé.push_back(m);
                BoiteAuxLettres[ID].pop();
                return true;
            }
            else{
                
                BoiteAuxLettres[ID].pop();
                BoiteAuxLettres[ID].push(tmp);
            }

        }
        
    }
    return false;
}

void Parking::processusNegocitation(){
    Message recu;
    
    // Si pas de message recu on quitte la fonction
    if(!GetLastUnreadMsg(recu, "NULL")){
        return;
    }
    else{
        // Si il y a un message recu mais ce n'est pas une demande de 
        // place on quitte aussi
        if(recu.performatif!=DemandePlace){
            return;
        }
    }

    // Si le parking est plein on refuse directement 
    if(IsFull()){
        Message toSend(ID, Refut);
        toSend.contenuMessage.setTexte("Désolé nous sommes complet");
        sendMessage(recu.emmeteur, toSend);
        return;
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

            double duree = recu.contenuMessage.getDuree();
            Date now;
            Date nowPlusDuree(now, duree);

            // On ajoute la voiture dans le parking
            ajouteVoiture(recu.emmeteur, nowPlusDuree);

            return;
        }
        else{
            toSend.contenuMessage.setTexte("Proposition refusée");
            toSend.contenuMessage.setPrix(prix + 0.1*prix);
            sendMessage(recu.emmeteur, toSend);
        }
                    

        // Boucle bloquant l'attente d'un nouveau message
        while(!GetLastUnreadMsg(recu, recu.emmeteur)){
        }
        
        compteur++;
    }
}


void Parking::Boucle(){


    while(true){

        processusNegocitation();
        updatePlacesStatus();
    }
}



