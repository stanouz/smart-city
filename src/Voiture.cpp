#include <unistd.h>
#include <stdlib.h>     
#include <time.h>
#include <thread>
#include <iostream>



#include "Voiture.h"

using namespace std;

const double DUREE_STATIONNEMENT = 0.2;

// Constructeur
Voiture::Voiture(string immat, int x, int y, Direction dir){
    immatriculation = immat;
    posX = x;
    posY = y;
    direction = dir;
    estGaree = false;
}

// Getters

string Voiture::getImat() const{
    return immatriculation;
}

double Voiture::getPosX() const{
    return posX;
}

double Voiture::getPosY() const{
    return posY;
}

Direction Voiture::getDirection(){
    return direction;
}

bool Voiture::getEstGaree(){
    return estGaree;
}


// Fonctions de négociation

void Voiture::negociation(string id_destinataire, double prixPopositionPrecedente, Date & dateDebut, double duree)
{
    Message m_new(immatriculation, DemandePlace);

    m_new.contenuMessage.setDate(dateDebut);
    m_new.contenuMessage.setDuree(duree);
    m_new.contenuMessage.setTexte("Je vous fais une autre proposition");
    

    // => valeur entre 1.050 et 2.000
    double coefAugmentation = (rand()%950 + 1050.)/1000.; 
   
    // nouveauPrix > prixPropositionPrecedente
    double nouveauPrix = prixPopositionPrecedente*coefAugmentation; 
    m_new.contenuMessage.setPrix(nouveauPrix);

    sendMessage(m_new, immatriculation, id_destinataire);
}

void Voiture::premierMessage(string id_destinataire, Date & dateDebut, double duree)
{
    Message m(immatriculation, DemandePlace);
    string mess = "Premier message de voiture";
    m.contenuMessage.setDate(dateDebut); 
    m.contenuMessage.setDuree(duree);
    
    float prix = (rand()%6)+1;
    m.contenuMessage.setPrix(prix);
    m.contenuMessage.setTexte(mess);
    m.recepteur = id_destinataire;

    sendMessage(m, immatriculation, id_destinataire);
}

void Voiture::processusNegocition(string id_parking, vector<PropositionAccepte> & prop)
{
    // Date actuelle et duree constant pour l'instant
    Date dateDebut; 
    double dureeStationnement = (rand()%1000)/100.  + 0.2;

    dureeStationnement = DUREE_STATIONNEMENT;

    premierMessage(id_parking, dateDebut, dureeStationnement);
    
    Message recu; 
    int compteur=0;
    bool propositionAccepte = false;


    
    while(compteur<3 && !propositionAccepte){
        
        //boucle d'attente d'un nouveau message
        recu = getMessageFrom(immatriculation, id_parking);
        //recu.display();
        
        if(recu.performatif==Accepter)
        {
            propositionAccepte = true;
            PropositionAccepte p(recu.contenuMessage.getPrix(), recu.emmeteur);
            prop.push_back(p);
        }
        else if(recu.performatif == Reponse)
        {
            // On recupère le prix de la proposition précédente que le
            // parking renvoie dans le contenu du message
            negociation(recu.emmeteur, recu.contenuMessage.getPrix(), dateDebut, dureeStationnement);
        } 
        else if(recu.performatif==Refut)
        {
            return;
        }
        
        
        
        compteur++;  
    }
}

PropositionAccepte Voiture::compareProposition(vector<PropositionAccepte> & prop){
    if(prop.size()>0){
        double prixMin = prop[0].getPrix();
        int indMin=0;
    
        for(int i=0; i<(int)prop.size(); i++){
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
    sleep(2);
    while(true){
        int random = rand()%30;
        sleep(random);


        string parkings[3] = {"P1", "P2", "P3"};
        vector<thread> negociations;
        vector<PropositionAccepte> propositions;
        int size = 3;

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
            m.contenuMessage.setPrix(meilleurOffre.getPrix());

            agenda.AddReservation(Reservation(Date(), DUREE_STATIONNEMENT, meilleurOffre.getId()));

            sendMessage(m, immatriculation, meilleurOffre.getId());
            
            estGaree = true;

            Message msg;
            do{
                msg = getMessageFrom(immatriculation, meilleurOffre.getId());
            }
            while(msg.performatif != LibererPlace);

            estGaree = false;
        }    
    }
}
    


// Fonctions de déplacement

void Voiture::turnLeft(){
    switch(direction){
        case Gauche: rouler(-2, 0);direction=Bas; rouler(0, 3); return; break;
        case Droite: rouler(2, 0); direction=Haut; rouler(0, -3); return; break;
        case Haut: rouler(0, -2); direction=Gauche; rouler(-3, 0); return; break;
        case Bas: rouler(0, 2); direction=Droite; rouler(3, 0); return; break;
    }
}

void Voiture::turnRight(){
    switch(direction){
        case Gauche: direction=Haut; rouler(0, -1); return; break;
        case Droite: direction=Bas; rouler(0, 1); return; break;
        case Haut: direction=Droite; rouler(1, 0); return; break;
        case Bas: direction=Gauche; rouler(-1, 0); return; break;
    }
}

void Voiture::goStraight(){
    switch(direction){
        case Gauche: rouler(-1, 0); break;
        case Droite: rouler(1, 0); break;
        case Haut: rouler(0, -1); break;
        case Bas: rouler(0, 1); break;
    }
}

void Voiture::halfTurn(){
    switch(direction){
        case Droite: rouler(2, 0); direction = Haut; rouler(0, -2); direction=Gauche; rouler(-1, 0); return; break;
        case Gauche: rouler(-2, 0); direction = Bas; rouler(0, 2); direction=Droite; rouler(1, 0);  return; break;
        case Haut: rouler(0, -2); direction = Gauche; rouler(-2, 0); direction=Bas; rouler(0, 1); return; break;
        case Bas: rouler(0, 2); direction = Droite; rouler(2, 0); direction=Haut; rouler(0, -1); return; break;
    }
}

void Voiture::Avancer(vector< vector<int> > & map){

    while(true){
        if(!estGaree){
            vector<int> deplacementPossible;
            if(canGoStraight(map)){
                deplacementPossible.push_back(0);
            }

            if(canGoRight(map)){
                deplacementPossible.push_back(1);
            }

            if(canGoLeft(map)){
                deplacementPossible.push_back(2);
            }

            
            // Si pas de deplacement possible alors demi-tour
            if(deplacementPossible.size()==0){
                halfTurn(); 
            }
            else{                
                int random = rand()%deplacementPossible.size();

                if(deplacementPossible[random]==0){
                    goStraight();
                } 
                else if(deplacementPossible[random]==1){
                    turnRight();
                }
                else if(deplacementPossible[random]==2){
                    turnLeft();
                }
            }
        }
        else{
            sleep(1);
        } 
    }
}

void Voiture::rouler(int dirX, int dirY){
    // deplacement en diagonale impossible
    if(dirX!=0 && dirY!=0){
        return;
    }

    double vitesse =0.0001;
    if(dirX!=0){
        int newX = posX + dirX;
        if(dirX > 0){
            while(posX < newX){
                posX += vitesse;
                usleep(60);
            }
            posX = newX;
            return;
        }
        else{
            while(posX > newX){
                posX -= vitesse;
                usleep(60);
            }
            posX = newX;
            return;
        }
    }

    if(dirY!=0){
        int newY = posY + dirY;
        if(dirY > 0){
            while(posY < newY){
                posY += vitesse;
                usleep(60);
            }
            posY = newY;
            return;
        }
        else{
            while(posY > newY){
                posY -= vitesse;
                usleep(60);
            }
            posY = newY;
            return;
        }
    }

}

bool Voiture::canGoRight(vector< vector<int> > & map){
    int val;
    switch (direction)
    {
        case Droite:
            val = map[posY+1][posX];
            if(val==462 || val==435)
                return true;
            break;

        case Gauche:
            val = map[posY-1][posX];
            if(val==464 || val==437)
                return true;
            break;
        
        case Bas:
            val = map[posY][posX-1];
            if(val==406 || val==407)
                return true;
            break;

        case Haut:
            val = map[posY][posX+1];
            if(val==460 || val==461)
                return true;
            break;
    }
    return false;
}

bool Voiture::canGoLeft(vector< vector<int> > & map){
    int val;
    switch (direction)
    {
        case Droite:
            val = map[posY-3][posX+2];
            if(val==464 || val==437)
                return true;
            break;

        case Gauche:
            val = map[posY+3][posX-2];
            if(val==462 || val==435)
                return true;
            break;
        
        case Haut:
            val = map[posY-2][posX-3];
            if(val==406 || val==407)
                return true;
            break;

        case Bas:
            val = map[posY+2][posX+3];
            if(val==460 || val==461)
                return true;
            break;
    }
    return false;
}

bool Voiture::canGoStraight(vector< vector<int> > & map){
    int val;
    switch (direction)
    {
        case Droite:
            val = map[posY][posX+2];
            if(val!=464 && val!=466)
                return true;
            break;

        case Gauche:
            val = map[posY][posX-2];
            if(val!=438 && val!=462)
                return true;
            break;
        
        case Haut:
            val = map[posY-2][posX];
            if(val!=439 && val!=407)
                return true;
            break;

        case Bas:
            val = map[posY+2][posX];
            if(val!=465 && val!=461)
                return true;
            break;
    }
    return false;
}




