#include "Affichage.h"

#include <string>

Affichage::Affichage(Ville * v): window(sf::VideoMode(900, 900), "smart parking"){
    ville = v;
    
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    /* Pour ne pas sauvegarder la position des widgets dans imgui.ini
    ImGuiIO io = ImGui::GetIO();
    io.IniFilename = NULL;*/

    tileset.loadFromFile("data/tilemap.png");
    sprite.setTexture(tileset);
}

Affichage::~Affichage(){

}

 
void Affichage::display(){
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());


        displayMainWidget();

        window.clear();
        displayMap();
<<<<<<< HEAD
        displayCars(2,14);
        displayCars(15,14);
        
        
=======


        for(int i=0; i<(int)ville->getTabVoitures().size(); i++){
            Voiture & v = ville->getTabVoitures()[i];
            if(!v.getEstGaree()){
                displayCar(v.getPosX(), v.getPosY(), v.getDirection());
            }
        }

>>>>>>> Stan

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}


void Affichage::displayMap(){
    int mapH = ville->getMap().size();
    int mapW = ville->getMap()[0].size();

    for(int i=0; i<mapW; i++){
        for(int j=0; j<mapH; j++){   
            drawTile(ville->getMap()[j][i], i, j);
        }
    }
}

void Affichage::displayCar(double x, double y, Direction dir){
   
    switch (dir){
        case Droite : 
                drawTile(481, x-0.5, y-0.3); 
                drawTile(482, x+0.5, y-0.3);
                break;
        
        case Gauche : 
                drawTile(454, x-0.5, y+0.3); 
                drawTile(455, x+0.5, y+0.3);
                break;

        case Haut : 
                drawTile(401, x-0.3, y-0.8); 
                drawTile(428, x-0.3, y+0.2);
                break;

        case Bas : 
                drawTile(400, x+0.3, y-0.8); 
                drawTile(427, x+0.3, y+0.2);
                break;
        
        default:
            break;
    }

    
    
}


void Affichage::drawTile(int nTile, double x, double y){
    int winH = window.getSize().y;
    int winW = window.getSize().x;
    int mapH = ville->getMap().size();
    int mapW = ville->getMap()[0].size();
    double tileH = winH/(double)(mapH-1);
    double tileW = winW/(double)(mapW-1);
    double scaleH = tileH / 16.; // tiles are 16x16 px
    double scaleW = tileW / 16.;

<<<<<<< HEAD
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

void Affichage :: displayCars(int i, int j)
{
    int winH = window.getSize().y;
    int winW = window.getSize().x;
    vector<vector<int> > map = ville->getMap();
    int mapH = map.size();
    int mapW = map[0].size();
    double tileH = winH/(double)(mapH-1);
    double tileW = winW/(double)(mapW-1);
    double scaleH = tileH / 16.; // tiles are 16x16 px
    double scaleW = tileW / 16.;
     sf::Texture text;
    text.loadFromFile("data/tilemap.png");
     sf::Sprite sprite;
      sprite.setTexture(text);
int x,y;


         int tab[4]={478,479,451,452};
            //int value1 = 478;
            
            for(int a=0;a<4;a++){

                switch(tab[a]){
                 case 478:
                        x = ((tab[a] - 1) % 27) * 17; // 27 tile par ligne et 
                        y = ((tab[a] - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
                        sprite.setPosition((i-1)*tileH, j*tileW);
                       

                  break;

                  case 479:
                        x = ((tab[a] - 1) % 27) * 17; // 27 tile par ligne et 
                        y = ((tab[a] - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
                        sprite.setPosition((i)*tileH, j*tileW);
                       

                  break;

                  case 451:
                        x = ((tab[a] - 1) % 27) * 17; // 27 tile par ligne et 
                        y = ((tab[a] - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
                        sprite.setPosition((i-1)*tileH, (j-1)*tileW);
                        

                  break;

                  case 452:
                        x = ((tab[a] - 1) % 27) * 17; // 27 tile par ligne et 
                        y = ((tab[a] - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
                        sprite.setPosition((i)*tileH, (j-1)*tileW);
                        

                  break;
                  default:
                    cout<<"erruer"<<endl;


                }  
                sprite.setScale(scaleH, scaleW);
                        sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
                        window.draw(sprite); 

            }
            
            
            
        
    



/*
        int v=478;
        int x,y;
        x = ((v - 1) % 27) * 17; // 27 tile par ligne et 
        y = ((v - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
        
        
                sprite.setPosition(1*tileH, 15.5*tileW);
                sprite.setScale(scaleH, scaleW);
                sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
                window.draw(sprite);
                //*****
        int v1=479;
        int x1,y1;
        x1 = ((v1 - 1) % 27) * 17; // 27 tile par ligne et 
        y1 = ((v1 - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
        
        
                sprite.setPosition(2*tileH, 15.5*tileW);
                sprite.setScale(scaleH, scaleW);
                sprite.setTextureRect(sf::IntRect(x1, y1, 16, 16));
                window.draw(sprite);
    //****
    int x2,y2;
    int v2=451;
        x2 = ((v2 - 1) % 27) * 17; // 27 tile par ligne et 
        y2 = ((v2 - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
        
        
                sprite.setPosition(1*tileH, 14.5*tileW);
                sprite.setScale(scaleH, scaleW);
                sprite.setTextureRect(sf::IntRect(x2, y2, 16, 16));
                window.draw(sprite);
    //******
int x3,y3;
    int v3=452;
        x3 = ((v3 - 1) % 27) * 17; // 27 tile par ligne et 
        y3 = ((v3 - 1) / 27) * 17; // * 17 car tile de 16px +1px d'espace
        
        
                sprite.setPosition(2*tileH, 14.5*tileW);
                sprite.setScale(scaleH, scaleW);
                sprite.setTextureRect(sf::IntRect(x3, y3, 16, 16));
                window.draw(sprite);
                */
}
=======
    double posTileX = ((nTile - 1) % 27) * 17;
    double posTileY = ((nTile - 1) / 27) * 17;
>>>>>>> Stan

    sprite.setPosition(x*tileH, y*tileW);
    sprite.setScale(scaleH, scaleW);
    sprite.setTextureRect(sf::IntRect(posTileX , posTileY, 16, 16));
    window.draw(sprite); 

}


void Affichage::displayMainWidget(){
    // Ouverture de la fenetre
    ImGui::Begin("Les parkings");
    
    // ==============
    // Date et heure
    // ==============
    Date now;
    ImGui::Text("%s", now.DateToString().c_str());

    ImGui::NewLine();

    // ==================
    // Info des parkings
    // ==================
    ImGui::BeginTabBar("Parkings", ImGuiTabBarFlags_None);
    for(int i = 0; i < (int)ville->getTabParkings().size(); i++){
        Parking p = ville->getTabParkings()[i];
        if (ImGui::BeginTabItem(("Parking "+p.getId()).c_str())){
            displayInfoParking(p);
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
    
    

    // Fermeture de la fenetre
    ImGui::End();
}


void Affichage::displayInfoParking(Parking & p){

    ImGui::Indent();

    // ===========================================  
    // Informations sur le remplissage du parking
    // =========================================== 
    if(ImGui::CollapsingHeader("Remplissage du parking")){
        ImGui::Indent();
        // ===========================================  
        // Barre de progression du taux de remplissage
        // =========================================== 
        ImGui::Text("Nombre de voitures :");
        char buf[32];
        sprintf(buf, "%d/%d", p.getNbPlaceOccupe(), p.getNbplace());
        ImGui::ProgressBar((double)p.getNbPlaceOccupe()/p.getNbplace(), ImVec2(0.f, 0.f), buf);

        ImGui::NewLine();

        // ===========================================  
        //  Liste des voitures garées dans le parking
        // =========================================== 
        for(int i=0; i<p.getNbplace(); i++){ 
            if(p.getPlace(i).getIsOccupied()){
                //ImGui::BulletText("%s jusqu'au %s", p.getPlace(i).getOccupant().c_str(), p.getPlace(i).getDateDepart().DateToString().c_str());
                ImGui::BulletText("%i", i);
                ImGui::NewLine();
            }
        }


        ImGui::NewLine();
        ImGui::Unindent();
    }
    
    
    


    // ===========================================  
    //   Affichage de la messagerie du parking
    // =========================================== 
    if(ImGui::CollapsingHeader("Messagerie du parkings")){
        ImGui::Indent();
        // ===========================================  
        //        Liste déroulante des voitures
        // =========================================== 
        ImGui::Text("Selectionner les voitures émmetrices des messages :");

        // remplissage d'un vector avec tte les immat + choix par défaut
        vector<string> choixVoiture;
        choixVoiture.push_back("Toutes les voitures");

        for(int i=0; i<(int)ville->getTabVoitures().size(); i++){
            choixVoiture.push_back(ville->getTabVoitures()[i].getImat());
        }

        // Indice du choix selectionner
        static int indSelected = 0; 
        // Affichage du choix selectionner
        const char* combo_label = choixVoiture[indSelected].c_str();

        // Ouverture de la liste déroulante == ImGui::Combo 
        if (ImGui::BeginCombo("     ", combo_label))
        {
            for (int n = 0; n < (int)choixVoiture.size(); n++)
            {
                const bool is_selected = (indSelected == n);
                if (ImGui::Selectable(choixVoiture[n].c_str(), is_selected))
                    indSelected = n; 
                    if (is_selected){
                        ImGui::SetItemDefaultFocus();
                    }
            }
            ImGui::EndCombo();
            
        }
        
        ImGui::NewLine();  
        // flags du tableau qui définissent le style
        static ImGuiTableFlags table_flags =   ImGuiTableFlags_Borders 
                                        | ImGuiTableFlags_RowBg
                                        | ImGuiTableFlags_BordersH
                                        | ImGuiTableFlags_BordersOuterH
                                        | ImGuiTableFlags_BordersInnerH
                                        | ImGuiTableFlags_BordersV
                                        | ImGuiTableFlags_BordersOuterV
                                        | ImGuiTableFlags_BordersInnerV
                                        | ImGuiTableFlags_BordersOuter
                                        | ImGuiTableFlags_BordersInner
                                        | ImGuiTableFlags_SizingFixedFit
                                        | ImGuiTableFlags_Hideable;

        if(ImGui::CollapsingHeader("Messages reçus")){
            ImGui::Indent();
            // ===========================================  
            //        Tableau des messages recu
            // =========================================== 
                
            // Ouverture du tableau
            ImGui::BeginTable("MessagesRecu", 6, table_flags);

            // En-tête du tableau
            ImGui::TableSetupColumn("#");
            ImGui::TableSetupColumn("Voiture");
            ImGui::TableSetupColumn("Performatif");
            ImGui::TableSetupColumn("Prix");
            ImGui::TableSetupColumn("Durée");
            ImGui::TableSetupColumn("Texte");
            ImGui::TableHeadersRow();

            // Remplissage du tableau
            for (int row = 0; row < (int)p.getBALPrive().size(); row++)
            {
                Message msg = p.getBALPrive()[row];
                    

                // Si choix toute les voitures ou si choix correspond à la voiture
                if(indSelected==0 || choixVoiture[indSelected]==msg.emmeteur){
                    displayMessage(msg, msg.emmeteur, row);
                }
            }
                
            // Fermeture du tableau
            ImGui::EndTable();
            ImGui::Unindent();
            ImGui::NewLine();
        }

            

        if(ImGui::CollapsingHeader("Messages envoyés")){
            ImGui::Indent();
            // ===========================================  
            //        Tableau des messages envoyés
            // =========================================== 

            // Ouverture du tableau
            ImGui::BeginTable("MessagesEnvoye", 6, table_flags);

            // En-tête du tableau
            ImGui::TableSetupColumn("#");
            ImGui::TableSetupColumn("Voiture");
            ImGui::TableSetupColumn("Performatif");
            ImGui::TableSetupColumn("Prix");
            ImGui::TableSetupColumn("Durée");
            ImGui::TableSetupColumn("Texte");
            ImGui::TableHeadersRow();

            // Remplissage du tableau
            for (int row = 0; row < (int)p.getMsgEnvoye().size(); row++)
            {
                Message msg = p.getMsgEnvoye()[row];
                    

                // Si choix toute les voitures ou si choix correspond à la voiture
                if(indSelected==0 || choixVoiture[indSelected]==msg.recepteur){
                    displayMessage(msg, msg.recepteur, row);
                }
            }
                
            // Fermeture du tableau
            ImGui::EndTable();
            ImGui::Unindent();
        }
    } 
}


void Affichage::displayMessage(Message & msg, string & immatVoiture, int row){
    ImGui::TableNextRow();

    // Colonne n°
    ImGui::TableSetColumnIndex(0);
    ImGui::Text("#%i", row);
            
    // Colonne Voiture
    ImGui::TableSetColumnIndex(1);
    ImGui::Text("%s", immatVoiture.c_str());
            
    // Colonne Performatif
    ImGui::TableSetColumnIndex(2);
    ImGui::Text("%s", msg.perfo_to_string().c_str());

    // Colonne prix 
    ImGui::TableSetColumnIndex(3);
    ImGui::Text("%.2f euros", msg.contenuMessage.getPrix());

    // Colonne durée
    ImGui::TableSetColumnIndex(4);
    ImGui::Text("%.2f heures", msg.contenuMessage.getDuree());

    // Colonne texte
    ImGui::TableSetColumnIndex(5);
    ImGui::Text("%s", msg.contenuMessage.getTexte().c_str());
 }

