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
    sf::RenderWindow window;
    vector<bool*> showParking;
public:
    Affichage(Ville * v);
    ~Affichage();
    void display();
    void displayMap();
    void displayCars(int i,int j);
    void displayMainWidget();
    void displayInfoParking(Parking & p);
};


#endif