#include "Affichage.h"

#include <string>

Affichage::Affichage(Ville * v): window(sf::VideoMode(700, 700), "smart parking"){
    ville = v;

    for(int i=0; i<(int)ville->getTabParkings().size(); i++)
        showParking.push_back(new bool(true));
}

Affichage::~Affichage(){

}

 
void Affichage::display(){
    
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                //clickParking();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();


        displayMainWidget();

        window.clear();
        displayMap();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}


void Affichage::displayMap(){
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



void Affichage::displayMainWidget(){
    // Ouverture de la fenetre
    ImGui::Begin("Les parkings");

    static bool opt_reorderable = true;
    static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;
    
    if (ImGui::CollapsingHeader("Choix des parkings")){
        //Add Checkbox for each parkings
        for(int i=0; i<(int)ville->getTabParkings().size(); i++){
            Parking p = ville->getTabParkings()[i];
            
            ImGui::Checkbox(p.getId().c_str(), showParking[i]);
        }
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Info des parkings")){
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;

        if (ImGui::BeginTabBar("Parkings", tab_bar_flags)){
            for(int i = 0; i < (int)ville->getTabParkings().size(); i++){
                Parking p = ville->getTabParkings()[i];
                if (ImGui::BeginTabItem(("Parking "+p.getId()).c_str(), showParking[i] , ImGuiTabItemFlags_None)){
                    

                    displayInfoParking(p);

                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    }

    // Fermeture de la fenetre
    ImGui::End();
}


void Affichage::displayInfoParking(Parking & p){

    // ===========================================  
    // Barre de progression du taux de remplissage
    // =========================================== 
    ImGui::Text("Nombre de voitures :");
    char buf[32];
    sprintf(buf, "%d/%d", p.getNbPlaceOccupe(), p.getNbplace());
    ImGui::ProgressBar((double)p.getNbPlaceOccupe()/p.getNbplace(), ImVec2(0.f, 0.f), buf);
    
    


    // Saut de ligne
    ImGui::NewLine();


    
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
                
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    
    // Saut de ligne
    ImGui::NewLine();


    // ===========================================  
    //          Tableau des messages
    // =========================================== 
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

    // Ouverture du tableau
    ImGui::BeginTable("Messagerie", 6, table_flags);

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
            ImGui::TableNextRow();

            // Colonne n°
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("#%i", row);
            
            // Colonne Voiture
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", msg.emmeteur.c_str());
            
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
    }
    
    // Fermeture du tableau
    ImGui::EndTable();
        
}

