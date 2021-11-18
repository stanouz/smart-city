#include "Ville.h"

#include <fstream>
#include <sstream>

#include <unistd.h>



using namespace std;

vector<int> TxtLineToInt(string data)
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


Ville::Ville(){
    tab_parkings.push_back(Parking("P1"));
    
    tab_parkings.push_back(Parking("P2"));
    tab_parkings.push_back(Parking("P3"));
    

    tab_voitures.push_back(Voiture("AAA-123-AAA", 2,16, Droite));
    tab_voitures.push_back(Voiture("BBB-123-BBB", 17,14, Gauche));
    /*
    tab_voitures.push_back(Voiture("CCC-123-CCC"));
    tab_voitures.push_back(Voiture("DDD-123-DDD"));
    tab_voitures.push_back(Voiture("EEE-123-EEE"));
    tab_voitures.push_back(Voiture("FFF-123-FFF"));
    tab_voitures.push_back(Voiture("GGG-123-GGG"));
    tab_voitures.push_back(Voiture("HHH-123-HHH"));*/
    
    ifstream my_file("data/map.txt");
    
    if(!my_file){
        exit(1);
    }

    string ligne;
    while(getline(my_file, ligne)){
        map.push_back(TxtLineToInt(ligne));
    }

    // Thread negociation des parkings
    for(int i=0; i<(int)tab_parkings.size();i++){
        tabThreads.push_back(thread(&Parking::Boucle, ref(tab_parkings[i])));
    }

    // Thread negociation des voitures
    for(int i=0; i<(int)tab_voitures.size();i++){
        tabThreads.push_back(thread(&Voiture::Boucle, ref(tab_voitures[i])));
    }

    // Thread mouvement des voitures
    for(int i=0; i<(int)tab_voitures.size();i++){
        tabThreads.push_back(thread(&Voiture::Avancer, ref(tab_voitures[i]), ref(map)));
    }
}



Ville::~Ville(){
    for(int i=0; i<(int)tabThreads.size(); i++){
        tabThreads[i].join();
    }
}

void Ville::lancerThread(){
    vector<thread> tabThreads;
    
    

    for(int i=0; i<(int)tabThreads.size(); i++){
        tabThreads[i].join();
    }
}


vector<Parking> & Ville::getTabParkings(){
    return tab_parkings;
}


vector<Voiture> & Ville::getTabVoitures(){
    return tab_voitures;
}

vector<vector<int> > & Ville::getMap(){
    return map;
}


