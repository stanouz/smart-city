#include <unistd.h>
#include <stdlib.h>     
#include <time.h>
#include <thread>
#include <iostream>



#include "Voiture.h"

using namespace std;

const double DUREE_STATIONNEMENT = 0.2;

// Constructeur
Voiture::Voiture(string immat, int x, int y, Direction dir) : position(x, y, dir){
    immatriculation = immat;
    estGaree = false;
}

// Getters

string Voiture::getImat() const{
    return immatriculation;
}

double Voiture::getPosX() const{
    return position.getX();
}

double Voiture::getPosY() const{
    return position.getY();
}

Direction Voiture::getDirection(){
    return position.getDirection();
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
        
        sleep(2);
        // Tant qu'on est pas devant un parking en attend 
        while((((int)getPosY()!=9) || ((int)getPosX()!=6)) &&
              (((int)getPosY()!=24) || ((int)getPosX()!=9))&&
              (((int)getPosY()!=16) || ((int)getPosX()!=18))){
            usleep(100);
        }




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
            for(int i = 0; i<3; i++){
                if(meilleurOffre.getId()!=parkings[i]){
                    Message refut(immatriculation, Refut);
                    sendMessage(refut, immatriculation, parkings[i]);
                }
                else{
                    Message m(immatriculation, Accepter);
                    m.contenuMessage.setDuree(DUREE_STATIONNEMENT);
                    m.contenuMessage.setPrix(meilleurOffre.getPrix());
                    sendMessage(m, immatriculation, meilleurOffre.getId());
                }
            }

            
            Message msg;
            msg = getMessageFrom(immatriculation, meilleurOffre.getId());


            // Position de l'endroit où l'on doit se garer
            position_parking = msg.contenuMessage.getPosition();            
            estGaree = true;

            
            do{
                msg = getMessageFrom(immatriculation, meilleurOffre.getId());
            }
            while(msg.performatif != LibererPlace);

            // Position de l'endroit où l'on doit sortir du parking
            position_parking = msg.contenuMessage.getPosition();   
            estGaree = false;
        }    
    }
}




// Fonctions de déplacement

void Voiture::turnLeft(){
    switch(getDirection()){
        case Gauche: rouler(-2, 0); position.setDirection(Bas); rouler(0, 3); return; break;
        case Droite: rouler(2, 0); position.setDirection(Haut); rouler(0, -3); return; break;
        case Haut: rouler(0, -2); position.setDirection(Gauche); rouler(-3, 0); return; break;
        case Bas: rouler(0, 2); position.setDirection(Droite); rouler(3, 0); return; break;
        default : break;
    }
}

void Voiture::turnRight(){
    switch(getDirection()){
        case Gauche: position.setDirection(Haut); rouler(0, -1); return; break;
        case Droite: position.setDirection(Bas); rouler(0, 1); return; break;
        case Haut: position.setDirection(Droite); rouler(1, 0); return; break;
        case Bas: position.setDirection(Gauche); rouler(-1, 0); return; break;
        default : break;
    }
}

void Voiture::goStraight(){
    switch(getDirection()){
        case Gauche: rouler(-1, 0); break;
        case Droite: rouler(1, 0); break;
        case Haut: rouler(0, -1); break;
        case Bas: rouler(0, 1); break;
        default : break;
    }
}

void Voiture::halfTurn(){
    switch(getDirection()){
        case Droite: rouler(2, 0); position.setDirection(Haut); rouler(0, -2); position.setDirection(Gauche); rouler(-1, 0); return; break;
        case Gauche: rouler(-2, 0); position.setDirection(Bas); rouler(0, 2); position.setDirection(Droite); rouler(1, 0);  return; break;
        case Haut: rouler(0, -2); position.setDirection(Gauche); rouler(-2, 0); position.setDirection(Bas); rouler(0, 1); return; break;
        case Bas: rouler(0, 2); position.setDirection(Droite); rouler(2, 0); position.setDirection(Haut); rouler(0, -1); return; break;
        default : break;
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
            
            // On place la voiture là où le parking 
            // nous dit de nous garer
            position = position_parking;

            while(estGaree){
                usleep(500);
            }

            // On place la voiture là où le parking 
            // nous dit de sortir du parking
            position = position_parking;
            
        } 
    }
}

void Voiture::rouler(int dirX, int dirY){
    // deplacement en diagonale impossible
    if(dirX!=0 && dirY!=0){
        return;
    }
    while(!estGaree){
        double vitesse =0.0001;
        if(dirX!=0){
            int newX = getPosX() + dirX;
            if(dirX > 0){
                while(getPosX() < newX && !estGaree){
                    position.incrementX(vitesse);
                    usleep(60);
                }
                position.setX(newX);
                return;
            }
            else{
                while(getPosX() > newX && !estGaree){
                    position.incrementX(-vitesse);
                    usleep(60);
                }
                position.setX(newX);
                return;
            }
        }

        if(dirY!=0){
            int newY = getPosY() + dirY;
            if(dirY > 0){
                while(getPosY() < newY && !estGaree){
                    position.incrementY(vitesse);
                    usleep(60);
                }
                position.setY(newY);
                return;
            }
            else{
                while(getPosY() > newY && !estGaree){
                    position.incrementY(-vitesse);
                    usleep(60);
                }
                position.setY(newY);
                return;
            }
        }
    }
}


bool isOutOfMap(vector< vector<int> > & map, int x, int y){
   int sizeX = map[0].size();
   int sizeY = map.size();

    if(x >= sizeX || y >= sizeY || x < 0 || y < 0){
        return true;
    }
    return false;
}


bool Voiture::canGoRight(vector< vector<int> > & map){
    int val;

    

    switch (getDirection())
    {
        case Droite:
            if(isOutOfMap(map, getPosX(), getPosY()+1)){
                return false;
            }

            val = map.at(getPosY()+1).at(getPosX());
            if(val==462 || val==435)
                return true;
            break;

        case Gauche:
            if(isOutOfMap(map, getPosX(), getPosY()-1)){
                return false;
            }

            val = map.at(getPosY()-1).at(getPosX());
            if(val==464 || val==437)
                return true;
            break;
        
        case Bas:
            if(isOutOfMap(map, getPosX()-1, getPosY())){
                return false;
            }

            val = map.at(getPosY()).at(getPosX()-1);
            if(val==406 || val==407)
                return true;
            break;

        case Haut:
            if(isOutOfMap(map, getPosX()+1, getPosY())){
                return false;
            }

            val = map.at(getPosY()).at(getPosX()+1);
            if(val==460 || val==461)
                return true;
            break;
        default : break;
    }
    return false;
}

bool Voiture::canGoLeft(vector< vector<int> > & map){
    int val;
    switch (getDirection())
    {
        case Droite:
            if(isOutOfMap(map, getPosX()+2, getPosY()-3)){
                return false;
            }

            val = map.at(getPosY()-3).at(getPosX()+2);
            if(val==464 || val==437)
                return true;
            break;

        case Gauche:
            if(isOutOfMap(map, getPosX()-2, getPosY()+3)){
                return false;
            }

            val = map.at(getPosY()+3).at(getPosX()-2);
            if(val==462 || val==435)
                return true;
            break;
        
        case Haut:
            if(isOutOfMap(map, getPosX()-3, getPosY()-2)){
                return false;
            }

            val = map.at(getPosY()-2).at(getPosX()-3);
            if(val==406 || val==407)
                return true;
            break;

        case Bas:
            if(isOutOfMap(map, getPosX()+3, getPosY()+2)){
                return false;
            }

            val = map.at(getPosY()+2).at(getPosX()+3);
            if(val==460 || val==461)
                return true;
            break;
        default : break;
    }
    return false;
}

bool Voiture::canGoStraight(vector< vector<int> > & map){
    int val;
    switch (getDirection())
    {
        case Droite:
            if(isOutOfMap(map, getPosX()+2, getPosY())){
                return false;
            }

            val = map.at(getPosY()).at(getPosX()+2);
            if(val!=464 && val!=466)
                return true;
            break;

        case Gauche:
            if(isOutOfMap(map, getPosX()-2, getPosY())){
                return false;
            }

            val = map.at(getPosY()).at(getPosX()-2);
            if(val!=438 && val!=462)
                return true;
            break;
        
        case Haut:
            if(isOutOfMap(map, getPosX(), getPosY()-2)){
                return false;
            }

            val = map.at(getPosY()-2).at(getPosX());
            if(val!=439 && val!=407)
                return true;
            break;

        case Bas:
            if(isOutOfMap(map, getPosX(), getPosY()+2)){
                return false;
            }

            val = map.at(getPosY()+2).at(getPosX());
            if(val!=465 && val!=461)
                return true;
            break;
        default : break;
    }
    return false;
}




