#include "Position.h"


Position::Position(){
    x = 0.;
    y = 0.;
    direction = Aucune;
}


Position::Position(double x_, double y_){
    x = x_;
    y = y_;
    direction = Aucune;
}


Position::Position(double x_, double y_, Direction dir){
    x = x_;
    y = y_;
    direction = dir;
}
    
void Position::operator=(const Position &p2){
    x = p2.x;
    y = p2.y;
    direction = p2.direction;
}

    // Setters
void Position::setX(double x_){
    x = x_;
}
void Position::setY(double y_){
    y = y_;
}

void Position::setDirection(Direction dir){
    direction = dir;
}

void Position::setPosition(double x_, double y_){
    setX(x_);
    setY(y_);
}

void Position::setPosition(double x_, double y_, Direction dir){
    setPosition(x_, y_);
    direction = dir;
}

void Position::incrementX(double valeur){
    x += valeur;    
}

void Position::incrementY(double valeur){
    y += valeur;
}

    
// Getters
double Position::getX() const{
    return x;
}

double Position::getY() const{
    return y;
}

Direction Position::getDirection() const{
    return direction;
}
