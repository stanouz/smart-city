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

void Parking::processusNegocitation(Message & recu){
    int compteur =0;
    bool propositionAccepte=false;
    Message toSend(ID, Reponse);
    while(compteur<3 && !propositionAccepte){
        // Boucle bloquant l'attente d'un nouveau message
        while(!GetLastUnreadMsg(recu) && compteur!=0){}

        cout << "===== COMPTEUR " << compteur << "=======" << endl;
        recu.display();
        float prixDemande = recu.contenuMessage.getPrix();
        
        if(prixDemande >= prix*0.9){
            toSend.contenuMessage.setTexte("Proposition acceptée");
            propositionAccepte=true;
        }
        else{
            toSend.contenuMessage.setTexte("Proposition refusée");
        }
                    
        sendMessage(recu.emmeteur, toSend);
        
        compteur++;
    }
    cout << "Négociation terminée !" << endl;
}


void Parking::Boucle(){

    while(true){
        Message recu;

        if(GetLastUnreadMsg(recu)){
            
            if(recu.performatif==DemandePlace){
                cout << "Debut négociation" << endl;
                processusNegocitation(recu);
            }

        }
        

        usleep(600000);
    }
}



