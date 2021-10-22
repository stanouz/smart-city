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



void Voiture::negociation(string id_destinataire, double prixPopositionPrecedente)
{
    Message m_new(immatriculation, DemandePlace);

    m_new.contenuMessage.setDuree(DUREE_STATIONNEMENT);
    m_new.contenuMessage.setTexte("Je vous fais une autre proposition");
   
    double coefAugmentation = (rand()%950 + 1050.)/1000.; // => valeur entre 1.050 et 2.000

    double nouveauPrix = prixPopositionPrecedente*coefAugmentation; // nouveauPrix > prixPropositionPrecedente
    
    // On garde que 2 chiffres après la virgule
    int tmp = nouveauPrix*100;
    nouveauPrix = tmp/100.;


    m_new.contenuMessage.setPrix(nouveauPrix);
    

    sendMessage(m_new, immatriculation, id_destinataire);
}


void Voiture::premierMessage(string id_destinataire)
{
    Message m(immatriculation, DemandePlace);
    string mess = "Premier message de voiture";
    m.contenuMessage.setDuree(DUREE_STATIONNEMENT);
    
    float prix = (rand()%6)+1;
    m.contenuMessage.setPrix(prix);
    m.contenuMessage.setTexte(mess);
    m.recepteur = id_destinataire;

    sendMessage(m, immatriculation, id_destinataire);
}

void Voiture::processusNegocition()
{
    Message recu = getMessage(immatriculation);

    srand (time(NULL));
    
    int compteur=0;
    bool propositionAccepte = false;
    
    while(compteur<3 && !propositionAccepte){
        if(recu.contenuMessage.getTexte()=="Proposition acceptée")
        {
            recu.display();
            propositionAccepte = true;
            cout << "Parking a accepter ma proposition" << endl;
        }
        else if(recu.contenuMessage.getTexte()=="Proposition refusée")
        {
            recu.display();
            cout << "Le parking a refusé ma proposition" << endl;

            // On recupère le prix de la proposition précédente que le
            // parking renvoie dans le contenu du message
            negociation(recu.emmeteur, recu.contenuMessage.getPrix());
        } 
        
        //boucle d'attente d'un nouveau message
        if(!propositionAccepte)
            recu = getMessageFrom(immatriculation, recu.emmeteur);
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
    