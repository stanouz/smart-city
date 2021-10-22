#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>

#include <fstream>
#include <vector>
#include <sstream>


#include "Parking.h"
#include "Voiture.h"
#include "time.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


using namespace std;


void DrawMap(sf::RenderWindow & window, vector<vector<int> > & map){
    int winH = window.getSize().y;
    int winW = window.getSize().x;

    int mapH = map.size();
    int mapW = map[0].size();
    double tileH = winH/(double)mapH;
    double tileW = winW/(double)mapW;
  
    sf::Texture text;
    text.loadFromFile("data/tilemap.png");

    double scaleH = tileH / 16.; // tiles are 16x16 px
    double scaleW = tileW / 16.;

    sf::Sprite sprite;
    sprite.setTexture(text);
    int x, y;

    for(int i=0; i<mapW; i++){
        for(int j=0; j<mapH; j++){   
            int value = map[j][i];
            x = ((value - 1) % 27) * 17; // 27 tile par ligne et 
            y = ((value - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace

            sprite.setPosition(i*tileH, j*tileW);
            sprite.setScale(scaleH, scaleW);
            sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
            window.draw(sprite);
        }
    }
        
}


std::vector<int> TxtLineToInt(std::string data)
{

    std::vector<int> vect;
    std::stringstream ss(data);

    // Tant qu'on lit dans la std::string on continu
    for (int i; ss >> i;)
    {
        // On stock dans le std::vector les entiers
        vect.push_back(i);
        // Si le caractère est un espace on passe
        if (ss.peek() == ' ')
            ss.ignore();
    }
    return vect;
}




vector<vector<int> > fileToTab(){
    ifstream my_file("data/map.txt");
    if(!my_file){
        exit(1);
    }

    vector<vector<int> > tab;
    string ligne;
    while(getline(my_file, ligne)){
        tab.push_back(TxtLineToInt(ligne));
    }
   
    
    return tab;
}


void Affichage(){
    
    vector<vector<int> > map= fileToTab();

    sf::RenderWindow window(sf::VideoMode(500, 500), "Test App SFML");

    while (window.isOpen()) {
        sf::Event event;
        
        // handle events
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                default:
                    break;
                    
            }
        }
        DrawMap(window, map);
        window.display();
    }
}



int main(int argc, char ** argv){
    
    thread thread_affichage(Affichage);
    
    Parking p("P1");
    Voiture v1("AAA-123-AAA");
    Voiture v2("BBB-123-BBB");
    Voiture v3("CCC-123-CCC");
    Voiture v4("DDD-123-DDD");
    Voiture v5("EEE-123-EEE");
    Voiture v6("FFF-123-FFF");
    Voiture v7("GGG-123-GGG");
    Voiture v8("HHH-123-HHH");
    
    thread thread_voiture1(&Voiture::Boucle, ref(v1));
    thread thread_voiture2(&Voiture::Boucle, ref(v2));
    thread thread_voiture3(&Voiture::Boucle, ref(v3));
    thread thread_voiture4(&Voiture::Boucle, ref(v4));
    thread thread_voiture5(&Voiture::Boucle, ref(v5));
    thread thread_voiture6(&Voiture::Boucle, ref(v6));
    thread thread_voiture7(&Voiture::Boucle, ref(v7));
    thread thread_voiture8(&Voiture::Boucle, ref(v8));
    thread thread_parking(&Parking::Boucle, ref(p));

    thread_affichage.join();

    thread_voiture1.join();
    thread_voiture2.join();
    thread_voiture3.join();
    thread_voiture4.join();
    thread_voiture5.join();
    thread_voiture6.join();
    thread_voiture7.join();
    thread_voiture8.join();

    thread_parking.join();

    



    return 0;
}
