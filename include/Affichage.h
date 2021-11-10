#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include "imgui.h" // necessary for ImGui::*, imgui-SFML.h doesn't include imgui.h

#include "imgui-SFML.h" // for ImGui::SFML::* functions and SFML-specific overloads

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


#include "Ville.h"


class Affichage{
    Ville * ville;
public:
    Affichage(Ville * v);
    ~Affichage();
    void display();
    void displayMap(sf::RenderWindow & window);
    bool clickParking(sf::RenderWindow & window, int & idParking);
};


#endif