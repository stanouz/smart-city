#include "Parking.h"

#include <unistd.h>
#include <iostream>

using namespace std;

Parking::Parking(string id){
    ID = id;
    prix = 5.;
    nb_place_occup = 0;
    indX=0;
    indY=0;
}



string Parking::getId(){
    return ID;
}

int Parking::getNbplace(){
    return NB_PLACES_TOTAL;
}

int Parking::getNbPlaceOccupe(){
    return nb_place_occup;
}

Place & Parking::getPlace(int ind){
    return tabPlaces[ind];
}

bool Parking::IsFull() const{
    return nb_place_occup>=NB_PLACES_TOTAL;
}

void Parking::updatePlacesStatus(){
    for(int i=0; i<NB_PLACES_TOTAL; i++){
        string update_immat = tabPlaces[i].updateStatus();
        if(update_immat!="NULL"){
            nb_place_occup--;
            Message msg(ID, LibererPlace);
            sendMessage(msg, ID, update_immat);
        }  
    }
}

double Parking::pourcentageRemplissage(){
    return (double)nb_place_occup/(double)NB_PLACES_TOTAL;
}

void Parking::ajouteVoiture(string occupant, Date dateDepart){

    int i=0;
    bool ajouter = false;
    while(i<NB_PLACES_TOTAL && !ajouter){
        ajouter = tabPlaces[i].ajouteVoiture(occupant, dateDepart);
        i++;
    }
    if(ajouter)
        nb_place_occup++;
}

double Parking::prixFinal(float duree, string immatriculation){
    double reduc=0.;
    double percent = pourcentageRemplissage();
    if(duree<=4){
        reduc = 0.;
    }
    else if(duree<=8){
        reduc = 0.05;
    }
    else if(duree<=12){
        reduc = 0.1;
    }
    else{
        reduc = 0.2;
    }
    double price = prix - (prix*reduc) + (prix*percent);
    return price + price * score[immatriculation];
}


void Parking::propositionAcceptee(Message recu)
{
    // Si la proposition est accepté on previent la voiture 
    Message toSend(ID, Accepter);
    //En fonction du parking, le parking attribut une place à la voiture
    
    if(ID=="P1")
    {   
        //cout<<" ID == "<<ID<<" ";
        if(indY == 4){indX = (indX+1) %2;}
        toSend.contenuMessage.setPlaceX(tabP1x[indX]);
        
        toSend.contenuMessage.setPlaceY(tabP1y[indY]);
        indY = (indY+1)%5;
        
        
        //cout<<" posX = "<<tabP1x[indX];        
        //cout<<" posY = "<<tabP1y[indY]<<endl;
        
    }

    else if(ID=="P2" || ID=="P3")
    {
        //cout<<" ID == "<<ID<<" ";
        if(indY == 4){indX = (indX+1) %2;}
        toSend.contenuMessage.setPlaceX(tabP2x[indX]);
        
        toSend.contenuMessage.setPlaceY(tabP2y[indY]);
        indY = (indY+1)%5;
        
        
        //cout<<" posX = "<<tabP2x[indX];        
        //cout<<" posY = "<<tabP2y[indY]<<endl;
        
        
    }
    
    
    // on envoie le message à la voiture
    toSend.contenuMessage.setTexte("Proposition acceptée");
    sendMessage(toSend, ID, recu.emmeteur);
}

void Parking::propositionRefusee(Message recu, int compteur)
{
    Message toSend(ID, Reponse);

    toSend.contenuMessage.setTexte("Proposition refusée");
    toSend.contenuMessage.setPrix(recu.contenuMessage.getPrix());

    // Si c'est déjà la 3ème proposition on dit de ne pas faire
    // d'autre proposition
    if(compteur==2){
        toSend.performatif=Refut;
    }

    sendMessage(toSend, ID, recu.emmeteur);
}


void Parking::processusNegocitation(){
    // Check si on a recu un message
    Message recu = getMessage(ID);

    // Si le parking est plein on refuse directement 
    if(IsFull()){
        Message toSend(ID, Refut);
        toSend.contenuMessage.setTexte("Désolé nous sommes complet");
        sendMessage(toSend, ID, recu.emmeteur);
        return;
    }

    // Si Perfo est accepter ça veut dire que la négociation à deja
    // eu lieu et que la voiture est d'accord pour se garer
    if(recu.performatif==Accepter){
        double duree = recu.contenuMessage.getDuree();
        Date now;
        Date nowPlusDuree(now, duree);

        // On ajoute la voiture dans le parking
        ajouteVoiture(recu.emmeteur, nowPlusDuree);
        score[recu.emmeteur]-=0.03;
        return;
    }

    if(recu.performatif==Refut){
        
        score[recu.emmeteur]+=0.03;
        return;
    }


    int compteur =0;
    bool accepte = false;
    Message toSend(ID, Reponse);
    while(compteur<3 && !accepte){
    
        float prixDemande = recu.contenuMessage.getPrix();
        float duree = recu.contenuMessage.getDuree();
        
        //cout<<ID<<" PRIX FINAL = "<<prixFinal(duree,recu.emmeteur)<<endl;
        if(prixDemande<prixFinal(duree,recu.emmeteur))
        {
            propositionRefusee(recu, compteur);
            if(compteur==2)
            {
                return;
            }
        }
        else 
        {
            propositionAcceptee(recu);
            accepte = true;

        }

        // Boucle bloquant l'attente d'un nouveau message
        if(!accepte)
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



