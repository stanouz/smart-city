#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>


using namespace std;

class Affichage{
    vector<vector<int> > map;
public:
    Affichage();
    ~Affichage();
    void display();
    void displayMap(sf::RenderWindow & window);
};


#endif