#include "Voiture.h"
#include <unistd.h>
#include <stdlib.h>     
#include <time.h>

#include <iostream>

using namespace std;

const double DUREE_STATIONNEMENT = 0.1;

Voiture::Voiture(){
}

Voiture::Voiture(Voiture & v): Agent(){
    immatriculation = v.immatriculation;
}

Voiture::Voiture(string immat){
    immatriculation = immat;
}

Voiture::~Voiture(){

}

string Voiture::getImat() const{
    return immatriculation;
}

void Voiture::sendMessage(string id_destinataire, Message m){
    m.recepteur = id_destinataire;
    BoiteAuxLettres[id_destinataire].push(m);
}

void Voiture::negociation(string id_destinataire, int compteur)
{
    Message m_voiture = BoiteAuxLettres[id_destinataire].back();
    Message m_parking = BoiteAuxLettres[immatriculation].back();
    
    float prix_parking = m_parking.contenuMessage.getPrix();
    float prix_voiture = m_voiture.contenuMessage.getPrix();


    Message m_new(immatriculation, DemandePlace);

    m_new.contenuMessage.setDuree(DUREE_STATIONNEMENT);
    m_new.contenuMessage.setPrix(prix_parking-0.1*prix_parking);
    m_new.contenuMessage.setTexte("Je vous fais une autre proposition");
   

    if(compteur==0)
    {
        m_new.contenuMessage.setPrix(prix_voiture+0.5*prix_voiture);
    }
    else if(compteur==1)
    {
        m_new.contenuMessage.setPrix(prix_parking);
    }
    

    sendMessage(id_destinataire,m_new);
}

bool Voiture::checkLastUnreadMessage(Message & m) 
{
    if(!BoiteAuxLettres[immatriculation].empty()){
        m = BoiteAuxLettres[immatriculation].front();
        BoiteAuxLettresPrivé.push_back(m);
        BoiteAuxLettres[immatriculation].pop();
        return true;
    }
    return false;
}

void Voiture::premierMessage(string id_destinataire)
{
    Message m(immatriculation, DemandePlace);
    string mess = "Premier message de voiture";
    m.contenuMessage.setDuree(DUREE_STATIONNEMENT);
    m.contenuMessage.setPrix(3);
    m.contenuMessage.setTexte(mess);
    m.recepteur = id_destinataire;

    m.contenuMessage.setPrix(1);
    sendMessage(id_destinataire, m);
}

void Voiture::processusNegocition()
{
    Message recu;

    // Si pas de message recu on quitte la fonction
    if(!checkLastUnreadMessage(recu)){
        return;
    }
    else{
        // On verifie que le messagge est une réponse
        if(recu.performatif!=Reponse){
            return;
        }
    }
    
    int compteur=0;
    bool propositionAccepte = false;
    while(compteur<3 && !propositionAccepte){
        if(recu.contenuMessage.getTexte()=="Proposition acceptée")
        {
            //recu.display();
            propositionAccepte = true;
            cout << "Parking a accepter ma proposition" << endl;
        }
        else if(recu.contenuMessage.getTexte()=="Proposition refusée")
        {
            //recu.display();
            cout << "Le parking a refusé ma proposition" << endl;
            negociation(recu.emmeteur, compteur);
        } 
        
        //boucle d'attente d'un nouveau message
        while(!checkLastUnreadMessage(recu)){
        }
        compteur++;  
    }
}

void Voiture::Boucle(){
    
    premierMessage("P1");
   
    while(true)
    {
        processusNegocition();
    }
}
    