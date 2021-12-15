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
    tab_parkings.push_back(Parking("P1", 10, 7, Vertical));
    tab_parkings.push_back(Parking("P2", 5, 19, Horizontal));
    tab_parkings.push_back(Parking("P3", 17, 19, Vertical));


    for(int i=0; i<(int)tab_parkings.size(); i++){
        fstream f("data/"+tab_parkings[i].getId()+".txt");
        if(!f.good()){
            ofstream file("data/"+tab_parkings[i].getId()+".txt");
            file << "Nombre de voiture venu : " << 0 << endl;
            file << "Total d'argent gagné : " << 0 << endl; 
        }
    }
    

    tab_voitures.push_back(Voiture(randomImmat(), 2,16, Droite));
    tab_voitures.push_back(Voiture(randomImmat(), 17,14, Gauche));
    tab_voitures.push_back(Voiture(randomImmat(), 4, 3, Bas));
    tab_voitures.push_back(Voiture(randomImmat(), 19, 16, Droite));
    tab_voitures.push_back(Voiture(randomImmat(), 3, 24, Gauche));
    tab_voitures.push_back(Voiture(randomImmat(), 26, 24, Haut));
    tab_voitures.push_back(Voiture(randomImmat(), 24, 8, Bas));
    tab_voitures.push_back(Voiture(randomImmat(), 26, 17, Haut));
    
    
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

bool Ville::immatExists(string immat){
    for(int i=0; i<(int)tab_voitures.size(); i++){
        if(tab_voitures[i].getImat()==immat){
            return true;
        }
    }
    return false;
}

string Ville::randomImmat(){
    string immat;
    string letters = "ABCDEFGHIJKLMNOPQRSTUVXYZ";
    string numbers = "0123456789";
    do{
        for(int i=0; i<3; i++){
            int random = rand()%letters.size();
            immat.push_back(letters[random]);
        }
        immat.push_back('-');
        for(int i=0; i<3; i++){
            int random = rand()%numbers.size();
            immat.push_back(numbers[random]);
        }
        immat.push_back('-');
        for(int i=0; i<3; i++){
            int random = rand()%letters.size();
            immat.push_back(letters[random]);
        }
    }
    while(immatExists(immat));

    return immat;
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


