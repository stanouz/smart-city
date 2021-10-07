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
    string non = "Non, -10%";
    string oui = "Oui";
    float alea = rand() % 100;
    m.performatif = DemandePlace;
    if(alea<=80)
    {
        m.contenuMessage.setTexte(non); 
    }
    else m.contenuMessage.setTexte(oui);

    sendMessage(id_destinataire,m);
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
    m.contenuMessage.setPrix(6);
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
            if(read.contenuMessage.getTexte()=="Ok")
            {
                propositionAccepte = true;
                cout << "Parking a accepter ma proposition" << endl;
            }
            else if(read.contenuMessage.getTexte()=="Non")
            {
                cout << "Le parking a refusé ma proposition" << endl;
                read.display();
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
    