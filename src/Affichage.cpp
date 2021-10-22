#include "Affichage.h"

#include <fstream>
#include <sstream>



vector<int> TxtLineToInt(std::string data)
{

    vector<int> vect;
    stringstream ss(data);

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



Affichage::Affichage(){
    ifstream my_file("data/map.txt");
    if(!my_file){
        exit(1);
    }

    string ligne;
    while(getline(my_file, ligne)){
        map.push_back(TxtLineToInt(ligne));
    }
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
        window.clear();
        displayMap(window);
        window.display();
    }
}


void Affichage::displayMap(sf::RenderWindow & window){
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