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




bool Parking::GetLastUnreadMsg(Message & m){
    if(!BoiteAuxLettres[ID].empty()){
        cout << "Voiture à un nouveau msg" << endl;
        m = BoiteAuxLettres[ID].front();
        BoiteAuxLettresPrivé.push_back(m);
        BoiteAuxLettres[ID].pop();
        return true;
    }
    return false;
}

void Parking::propositionAcceptee(Message recu)
{
    GetLastUnreadMsg(recu);
    Message toSend(ID, Reponse);

    // Si la proposition est accepté on previent la voiture et 
    // on quitte le processus de négociation.
    toSend.contenuMessage.setTexte("Proposition acceptée");
    sendMessage(recu.emmeteur, toSend);

    // On ajoute la voiture dans le parking
    ajouteVoiture(recu.emmeteur, recu.contenuMessage.getDateFin());
}

void Parking::propositionRefusee(float _prix, Message recu)
{
    GetLastUnreadMsg(recu);
    Message toSend(ID, Reponse);

    toSend.contenuMessage.setTexte("Proposition refusée");
    toSend.contenuMessage.setPrix(_prix+prix*0.1);
    sendMessage(recu.emmeteur, toSend);
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
        
        if(pourcentageRemplissage()>=95)
        {
            if(prixDemande<10)
            {
                propositionRefusee(10, recu);
            }
            else
            {
                propositionAcceptee(recu);
            }
        }
        else if((50<=pourcentageRemplissage()) && (pourcentageRemplissage()<95))
        {
            if(prixDemande<5)
            {
                propositionRefusee(5, recu);
            }
            else 
            {
                propositionAcceptee(recu);
            }
        }
        else if((20<=pourcentageRemplissage()) && (pourcentageRemplissage()<50))
        {
            if(prixDemande<3)
            {
                propositionRefusee(3, recu);
            }
            else 
            {
                propositionAcceptee(recu);
            }
        }
        else if((0<=pourcentageRemplissage()) && (pourcentageRemplissage()<20))
        {
            if(prixDemande<2)
            {
                propositionRefusee(2, recu);
            }
            else 
            {
                propositionAcceptee(recu);
            }
        }
                    
        // Boucle bloquant l'attente d'un nouveau message
        while(!GetLastUnreadMsg(recu)){
            //cout << "Boucle d'attente" << endl;
        }
        
        compteur++;
    }
}


void Parking::Boucle(){

    cout << nb_place_occup << " place occupé" << endl;

    while(!IsFull()){
        Date now;
        cout << nb_place_occup << " place occupé à " << now << endl;
        processusNegocitation();
        updatePlacesStatus();

        usleep(600000);
    }
}



