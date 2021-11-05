#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include "Ville.h"


using namespace std;

class Affichage{
    Ville * ville;
public:
    Affichage(Ville * v);
    ~Affichage();
    void display();
    void displayMap(sf::RenderWindow & window);
    bool clickParking(sf::RenderWindow & window);
};


#endif