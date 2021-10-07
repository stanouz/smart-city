#include "Voiture.h"
#include <unistd.h>

#include <iostream>

using namespace std;

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

void Voiture::negociation(string id_destinataire)
{
    Message m(immatriculation, DemandePlace);
    m = BoiteAuxLettresPrivé.back();
    float prix_parking = m.contenuMessage.getPrix();

    Message m_new(immatriculation, DemandePlace);
    m_new.contenuMessage.setPrix(prix_parking-0.1*prix_parking);
    m.contenuMessage.setTexte("Je vous fais une autre proposition");
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
    m.contenuMessage.setDateDebut(Date());
    m.contenuMessage.setPrix(3);
    m.contenuMessage.setTexte(mess);
    m.recepteur = id_destinataire;
    sendMessage(id_destinataire, m);
}

void Voiture::processusNegocitionVoiture(Message & recu)
{
    int compteur=0;
    bool propositionAccepte = false;
    while(compteur<3 && !propositionAccepte){
        Message read;

        //boucle d'attente d'un nouveau message
        while(!checkLastUnreadMessage(read))
        {
            
        }
        if(read.performatif==Reponse)
        {
            if(read.contenuMessage.getTexte()=="Proposition acceptée")
            {
                propositionAccepte = true;
                cout << "Parking a accepter ma proposition" << endl;
            }
            else if(read.contenuMessage.getTexte()=="Proposition refusée")
            {
                read.display();
                cout << "Le parking a refusé ma proposition" << endl;
                negociation(read.emmeteur);
            } 
        
            compteur++;
            usleep(1600000);
        }
        
    }
}

void Voiture::Boucle(){
    
    premierMessage("P1");
    Message recu;
    while(true)
    {
        processusNegocitionVoiture(recu);
        usleep(1600000);
    }
}
    