#include "Parking.h"

Parking::Parking(){
    for(int j=0; j<24; j++){
        grilleTarifaire[0][j]= 5;
        grilleTarifaire[1][j]= 5;
        grilleTarifaire[2][j]= 5;
        grilleTarifaire[3][j]= 5;
        grilleTarifaire[4][j]= 5;
        grilleTarifaire[5][j]= 10;
        grilleTarifaire[6][j]= 10;
    }
    
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
    if(BoiteAuxLettres[0].size()>0)
        return BoiteAuxLettres[0][0].contenuMessage.texte;
    
    return "Rien";
}
