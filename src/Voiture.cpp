#include <unistd.h>
#include <stdlib.h>     
#include <time.h>
#include <thread>
#include <iostream>



#include "Voiture.h"

using namespace std;

const double DUREE_STATIONNEMENT = 0.1;

Voiture::Voiture(){
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

void Voiture::processusNegocition(string id_parking, vector<PropositionAccepte> & prop)
{
    premierMessage(id_parking);
    
    Message recu; 
    int compteur=0;
    bool propositionAccepte = false;
    
    while(compteur<3 && !propositionAccepte){
        
        //boucle d'attente d'un nouveau message
        recu = getMessageFrom(immatriculation, id_parking);
        recu.display();
        
        if(recu.performatif==Accepter)
        {
            propositionAccepte = true;
            PropositionAccepte p(recu.contenuMessage.getPrix(), recu.emmeteur);
            prop.push_back(p);
            cout << "Parking a accepter ma proposition" << endl;
        }
        else if(recu.performatif == Reponse)
        {
            cout << "Le parking negocie encore" << endl;

            // On recupère le prix de la proposition précédente que le
            // parking renvoie dans le contenu du message
            negociation(recu.emmeteur, recu.contenuMessage.getPrix());
        } 
        else if(recu.performatif==Refut)
        {
            cout<<"Le parking refuse la proposition et stop la negociation"<<endl;
            return;
        }
        
        
        
        compteur++;  
    }
}



PropositionAccepte Voiture::compareProposition(vector<PropositionAccepte> & prop){
    if(prop.size()>0){
        double prixMin = prop[0].getPrix();
        int indMin=0;
    
        for(int i=0; i<prop.size(); i++){
            if(prop[i].getPrix()<prixMin){
                indMin=i;
                prixMin = prop[i].getPrix();
            }
        }
        return prop[indMin];
    }
    

    return PropositionAccepte(-1, "P#");
}




void Voiture::Boucle(){
    string parkings[3] = {"P1", "P2", "P3"};
    vector<thread> negociations;
    vector<PropositionAccepte> propositions;
    int size = 1;
    for(int i=0; i<size; i++){
        negociations.push_back(thread(&Voiture::processusNegocition, ref(*this),parkings[i], ref(propositions)));
    }
    for(int i=0; i<size; i++){
        negociations[i].join();
    }

    PropositionAccepte meilleurOffre = compareProposition(propositions);

    if(meilleurOffre.getPrix()!=-1 && meilleurOffre.getId()!="P#"){
        Message m(immatriculation, Accepter);
        m.contenuMessage.setDuree(DUREE_STATIONNEMENT);
        sendMessage(m, immatriculation, meilleurOffre.getId());
        cout << "ACCEPTE" << endl;
    }
    else 
        cout << "REFU" << endl;
    
    
}
    
/*

Voir si les threads ne se bloque pas en attente de message

*/