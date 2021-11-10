#include "Affichage.h"


Affichage::Affichage(Ville * v){
    ville = v;
}

Affichage::~Affichage(){

}

 
void Affichage::display(){
    sf::RenderWindow window(sf::VideoMode(700, 700), "smart parking");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                
                ImGui::SFML::Shutdown();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

       

        ImGui::Begin("Messagerie");
        vector<Message> tabMsg = ville->getTabParkings()[0].getBALPrive();
        for(int i=0; i<(int)tabMsg.size(); i++){
            ImGui::BulletText(tabMsg[i].to_string().c_str());
        }
        
        ImGui::End();

        window.clear();
     
        displayMap(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
       
}


void Affichage::displayMap(sf::RenderWindow & window){
    int winH = window.getSize().y;
    int winW = window.getSize().x;

    vector<vector<int> > map = ville->getMap();

    int mapH = map.size();
    int mapW = map[0].size();
    double tileH = winH/(double)(mapH-1);
    double tileW = winW/(double)(mapW-1);
  
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


bool Affichage::clickParking(sf::RenderWindow & window, int & idParking){
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
                idParking = i+1;
                return true;
            }
        }
    }
    return false;
}
