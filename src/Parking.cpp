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

void Parking::ajouteVoiture(string occupant, Date dateDepart){

    int i=0;
    bool ajouter = false;
    while(i<NB_PLACES_TOTAL && !ajouter){
        ajouter = tabPlaces[i].ajouteVoiture(occupant, dateDepart);
        i++;
    }
    if(ajouter){
        nb_place_occup++;
    }
}






void Parking::propositionAcceptee(Message recu)
{
    Message toSend(ID, Reponse);

    // Si la proposition est accepté on previent la voiture et 
    // on quitte le processus de négociation.
    toSend.contenuMessage.setTexte("Proposition acceptée");
    sendMessage(toSend, ID, recu.emmeteur);

    double duree = recu.contenuMessage.getDuree();
    Date now;
    Date nowPlusDuree(now, duree);

    // On ajoute la voiture dans le parking
    ajouteVoiture(recu.emmeteur, nowPlusDuree);

}

void Parking::propositionRefusee(float _prix, Message recu)
{
    Message toSend(ID, Reponse);

    toSend.contenuMessage.setTexte("Proposition refusée");

    float prix_remplissage = pourcentageRemplissage()+0.50;
    float prix_total = _prix+_prix*prix_remplissage;
    cout<<"prix total = "<<prix_total<<endl;
    toSend.contenuMessage.setPrix(prix_total);
    sendMessage(toSend, ID, recu.emmeteur);
}

void Parking::processusNegocitation(){

    Message recu = getMessage(ID);

    // Si le parking est plein on refuse directement 
    if(IsFull()){
        Message toSend(ID, Refut);
        toSend.contenuMessage.setTexte("Désolé nous sommes complet");
        sendMessage(toSend, ID, recu.emmeteur);
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
            sendMessage(toSend, ID, recu.emmeteur);

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
            sendMessage(toSend, ID, recu.emmeteur);
        }
                    

        // Boucle bloquant l'attente d'un nouveau message
        recu = getMessageFrom(ID, recu.emmeteur);
        
        compteur++;
    }
}


void Parking::Boucle(){

    while(true){
        if(!BoiteAuxLettres[ID].empty())
            processusNegocitation();
        updatePlacesStatus();
        
    }
}



