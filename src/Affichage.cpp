#include "Affichage.h"


#include <iostream>
#include <vector>

using namespace std;


Affichage::Affichage(Ville * v){
    ville = v;
}

Affichage::~Affichage(){

}

void Affichage::display(){
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            clickParking(window);
        }

        window.clear();
        displayMap(window);
        window.display();
    }
}


void Affichage::displayMap(sf::RenderWindow & window){
    int winH = window.getSize().y;
    int winW = window.getSize().x;

    vector<vector<int> > map = ville->getMap();

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


bool Affichage::clickParking(sf::RenderWindow & window){
    vector<vector<int> > map = ville->getMap();
    vector<int> tab_x;
    vector<int> tab_y;

    for(int i=0; i<(int)map.size(); i++){
        for(int j=0; j<(int)map[0].size(); j++){
            if(map[i][j]==443){
                tab_x.push_back(j);
                tab_y.push_back(i);
            }
        }
    }
    int winH = window.getSize().y;
    int winW = window.getSize().x;
    int mapH = map.size();
    int mapW = map[0].size();
    double tileH = winH/(double)mapH;
    double tileW = winW/(double)mapW;


    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    for(int i=0; i<(int)tab_x.size(); i++){
        if(localPosition.x > tab_x[i]*tileH && localPosition.x < (tab_x[i]+1)*tileH){
            if(localPosition.y > tab_y[i]*tileW && localPosition.y < (tab_y[i]+1)*tileW){
                cout << "CLICK" << endl;
                return true;
            }
        }
    }
    return false;
}