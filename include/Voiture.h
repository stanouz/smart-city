#ifndef __VOITURE__
#define __VOITURE__

#include <string>



#include "Agent.h"
#include "PropositionAccepte.h"
#include "Enums.h"
#include "Position.h"


using namespace std;


class Voiture:public Agent{
public:
    Voiture(string immat, int x, int y, Direction dir);

    // Getters
    string getImat() const;
    double getPosX() const;
    double getPosY() const;
    Direction getDirection();
    bool getEstGaree();

    // Negociation
    void Boucle();
    void negociation(string id_destinataire, double prixPopositionPrecedente, Date & dateDebut, double duree);
    void premierMessage(string id_destinataire, Date & dateDebut, double duree);
    void processusNegocition(string id_parking, vector<PropositionAccepte> & prop);
    PropositionAccepte compareProposition(vector<PropositionAccepte> & prop);



    // Deplacement
    void Avancer(vector< vector<int> > & map);
    void rouler(int dirX, int dirY);
    void halfTurn();
    void turnLeft();
    void turnRight();
    void goStraight();

    // Test de possibilit√© de direction
    bool canGoRight(vector< vector<int> > & map);
    bool canGoLeft(vector< vector<int> > & map);
    bool canGoStraight(vector< vector<int> > & map);
    

private:
    string immatriculation;
    bool estGaree;

    Position position;
    Position position_parking;
};

#endif