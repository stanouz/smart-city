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
    BoiteAuxLettres[id_destinataire].push_back(m);
}

void Voiture::negociation(string id_destinataire)
{
    Message m(immatriculation, DemandePlace);
    string non = "Non, -10%";
    string oui = "Oui";
    float alea = rand() % 100;
    if(alea<=80)
    {
        m.contenuMessage.setTexte(non); 
    }
    else m.contenuMessage.setTexte(oui);

    sendMessage(id_destinataire,m);
}

Message &Voiture::checkLastUnreadMessage() const
{
    return BoiteAuxLettres[immatriculation][lastRead];
}


void Voiture::Boucle(){
    
    Message m(immatriculation, DemandePlace);
    string mess = "Bonjour";
    m.contenuMessage.setDateDebut(Date());
    m.contenuMessage.setPrix(6);
    m.contenuMessage.setTexte(mess);
    m.performatif = DemandePlace;
    sendMessage("P1",m);

    while(true){
        int size = BoiteAuxLettres[immatriculation].size();
        int compteur=0;
       
        if(size>0 && (size-1)!=lastRead){
            
            while(compteur<=3){
                while(size-1==lastRead)
                {
            
                }
                Message read = checkLastUnreadMessage();
                negociation(read.emmeteur);
                cout << "Message " << compteur << endl;
                compteur++;
                usleep(1600000);
            }
        }
        
        usleep(1600000);
    }
}