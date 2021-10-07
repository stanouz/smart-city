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


void Voiture::Boucle(){
    
    Message m(immatriculation, DemandePlace);
    string mess = "Bonjour";
    m.contenuMessage.setDateDebut(Date());
    m.contenuMessage.setPrix(6);
    m.contenuMessage.setTexte(mess);
    m.performatif = DemandePlace;
    sendMessage("P1",m);

    while(true){
        int compteur=0;
       
        while(compteur<=3){
            Message read;
            while(!checkLastUnreadMessage(read))
            {
        
            }
                

            read.display();
            negociation(read.emmeteur);
            cout << "Message " << compteur << endl;
            compteur++;
            usleep(1600000);
        }
        
        usleep(1600000);
    }
}