#ifndef __POSITION_H__
#define __POSITION_H__


#include "Enums.h"
#include <vector>

using namespace std;

class Position{
public:
    Position();
    Position(double x_, double y_);
    Position(double x_, double y_, Direction dir);

    // Initialise une position aléatoire cohérante avec la map
    Position(vector< vector<int> > & map);
    
    void operator=(const Position &p2);

    // Setters
    void setX(double x_);
    void setY(double y_);
    void setDirection(Direction dir);
    void setPosition(double x_, double y_);
    void setPosition(double x_, double y_, Direction dir);
    void incrementX(double valeur);
    void incrementY(double valeur);


    // Getters
    double getX() const;
    double getY() const;
    Direction getDirection() const;

private:
    double x;
    double y;
    Direction direction;
};


#endif