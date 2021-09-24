#include "Parking.h"

#include <unistd.h>
#include <iostream>

using namespace std;

Parking::Parking(){
    /*
    for(int j=0; j<24; j++){
        grilleTarifaire[0][j]= 5;
        grilleTarifaire[1][j]= 5;
        grilleTarifaire[2][j]= 5;
        grilleTarifaire[3][j]= 5;
        grilleTarifaire[4][j]= 5;
        grilleTarifaire[5][j]= 10;
        grilleTarifaire[6][j]= 10;
    }*/
    
}

Parking::~Parking(){

}

bool Parking::IsCompleted() const{
    return isCompleted;
}

void Parking::sendMessage(){
    Message m;
    string mess = "Bonjour";
    m.contenuMessage.texte = mess;
    BoiteAuxLettres[1].push_back(m);
}

string Parking::checkMessage(){
    int size = BoiteAuxLettres[0].size();
    if(size>0 && (size-1)!=lastRead){
        lastRead ++;
        return BoiteAuxLettres[0][lastRead].contenuMessage.texte+" "+to_string(lastRead);
    }
        
    return "Pas de nouveau message : "+to_string(lastRead)+" messages déjà lu.";
}

void Parking::Boucle(){

    while(true){
        
        cout << checkMessage() << endl;

        usleep(600000);
    }
}
