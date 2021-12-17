#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h
#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>

using namespace std;

#include "Ville.h"


class Affichage{
    Ville * ville;
    vector<bool*> showParking;

    sf::RenderWindow window;
    sf::Sprite sprite;
    sf::Texture tileset;
public:
    Affichage(Ville * v);
    ~Affichage();
    void display();
    void displayMap();
    void displayMainWidget();
    void displayInfoParking(Parking & p);
    void displayCar(double x, double y, Direction dir);
    void displayMessage(Message & msg, string & immatVoiture, int row);
    void drawTile(int nTile, double x, double y);
};


#endif