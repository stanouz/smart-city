#include <unistd.h>
#include <stdlib.h>     
#include <time.h>
#include <thread>
#include <iostream>



#include "Voiture.h"

using namespace std;

const double DUREE_STATIONNEMENT = 0.1;

Voiture::Voiture(string immat, int x, int y, Direction dir){
    immatriculation = immat;
    posX = x;
    posY = y;
    direction = dir;
}


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



void Voiture::negociation(string id_destinataire, double prixPopositionPrecedente)
{
    Message m_new(immatriculation, DemandePlace);

    m_new.contenuMessage.setDuree(DUREE_STATIONNEMENT);
    m_new.contenuMessage.setTexte("Je vous fais une autre proposition");
    

    // => valeur entre 1.050 et 2.000
    double coefAugmentation = (rand()%950 + 1050.)/1000.; 
   
    // nouveauPrix > prixPropositionPrecedente
    double nouveauPrix = prixPopositionPrecedente*coefAugmentation; 
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
            negociation(recu.emmeteur, recu.contenuMessage.getPrix());
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


void Voiture::turnLeft(){
    
}

void Voiture::turnRight(){
    int newX, newY;
    double vitesse =0.0001;

    if(direction==Droite){
        direction=Bas;
        newY = posY +1;
        while(posY < newY){
            posY += vitesse;
            usleep(60);
        }
        posY = newY;
        return;
    }
    if(direction==Gauche){
        direction=Haut;
        newY = posY - 1;
        while(posY > newY){
            posY -= vitesse;
            usleep(60);
        }
        posY = newY;
        return;
    }

    if(direction==Haut){
        direction=Droite;
        newX = posX +1;
        while(posX < newY){
            posX += vitesse;
            usleep(60);
        }
        posX = newX;
        return;
    }
    if(direction==Bas){
        direction=Gauche;
        newX = posX -1;
        while(posX > newY){
            posX -= vitesse;
            usleep(60);
        }
        posX = newX;
        return;
    }
}

void Voiture::goStraight(){
    double vitesse =0.0001;

    int newX, newY;


    // Implementer un DeltaTime à la place du sleep()

    if(direction==Gauche){
        newX = posX-1;
        while(posX > newX){
            posX-= vitesse;
            usleep(60);
        }
        posX = newX;
    }
    else if(direction==Droite){
        newX = posX+1;
        while(posX < newX){
            posX+= vitesse;
            usleep(60);
        }
        posX = newX;
    }
    else if(direction==Bas){
        newY = posY+1;
        while(posY < newY){
            posY+= vitesse;
            usleep(60);
        }
        posY = newY;
    }
    else if(direction==Haut){
        newY = posY-1;
        while(posY > newY){
            posY-= vitesse;
            usleep(60);
        }
        posY = newY;
    }
}

void Voiture::halfTurn(){
    switch(direction)
    {
        case Droite: direction = Gauche; posY -= 2; posX+=2; break;
        case Gauche: direction = Droite; posY += 2; posX-=2; break;
        case Haut: direction = Bas; posX -= 2; posY-=2; break;
        case Bas: direction = Haut; posX += 2; posY+=2;break;
    }
}

void Voiture::Avancer(vector< vector<int> > & map){
    
    vector<bool> deplacementPossible;
    deplacementPossible.push_back(canGoStraight(map));
    deplacementPossible.push_back(canGoRight(map));
    deplacementPossible.push_back(canGoLeft(map));

    // On verifie qu'il y ai bien un true
    bool hasTrue = false;

    for(int i=0; i<3; i++){
        if(deplacementPossible[i])
            hasTrue= true;
    }

    // ==========================================
    // A FAIRE : 
    // Améliorer le système de choix aléatoire 
    // pour pas avoir à faire plusieur rand()
    // ==========================================

    // Si pas de deplacement possible alors demi-tour
    
    if(!hasTrue){
        halfTurn(); 
        return;
    }

    srand(time(NULL));
        
    int random;
    do{
        random = rand()%3;
    }
    while(!deplacementPossible[random]);

    if(random==0)
        goStraight();
    
    
    else if(random==1)
        turnRight();
    
    
    // Fonctions pas encore faites
    /*
    if(random==2)
        turnLeft();*/
        
    
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






void Voiture::Boucle(){
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
        sendMessage(m, immatriculation, meilleurOffre.getId());
        cout << "ACCEPTE "+immatriculation+" pour "+ meilleurOffre.getId() << endl;
    }
    else 
        cout << "REFU " +immatriculation+" pour "+ meilleurOffre.getId() << endl;
    
    
}
    