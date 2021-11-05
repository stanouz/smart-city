#include "Ville.h"



Ville::Ville(){
    tab_parkings.push_back(Parking("P1"));
    tab_parkings.push_back(Parking("P2"));
    tab_parkings.push_back(Parking("P3"));


    tab_voitures.push_back(Voiture("AAA-123-AAA"));
    tab_voitures.push_back(Voiture("BBB-123-BBB"));
    tab_voitures.push_back(Voiture("CCC-123-CCC"));
    tab_voitures.push_back(Voiture("DDD-123-DDD"));
    tab_voitures.push_back(Voiture("EEE-123-EEE"));
    tab_voitures.push_back(Voiture("FFF-123-FFF"));
    tab_voitures.push_back(Voiture("GGG-123-GGG"));
    tab_voitures.push_back(Voiture("HHH-123-HHH"));
}

Ville::~Ville(){

}


void Ville::lancerThread(){
    vector<thread> tabThreads;

    for(int i=0; i<(int)tab_parkings.size();i++){
        tabThreads.push_back(thread(&Parking::Boucle, ref(tab_parkings[i])));
    }

    for(int i=0; i<(int)tab_voitures.size();i++){
        tabThreads.push_back(thread(&Voiture::Boucle, ref(tab_voitures[i])));
    }

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