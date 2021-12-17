#include "Message.h"
#include <iostream>

Message::Message(){

}

Message::Message(string emmeteur_, Performatif perfo){
    emmeteur = emmeteur_;
    performatif = perfo;
}

Message::Message(string emmeteur_, Performatif perfo, Position p): contenuMessage(p){
    emmeteur = emmeteur_;
    performatif = perfo;
}

Message::~Message(){
    
}

void Message::operator=(Message msg){
    emmeteur = msg.emmeteur;
    recepteur = msg.recepteur;
    contenuMessage = msg.contenuMessage;
    performatif = msg.performatif;
}


void Message::display(){
    cout << to_string() << endl;
}

string Message::perfo_to_string(){
    switch(performatif){
        case 0 : return "Demande de place";
        case 1 : return "Réponse";
        case 2 : return "Refut";
        case 3 : return "Accepté";
        case 4 : return "LibérerPlace";
        default : break;
    }
    return " ";
}

string Message::to_string(){
    return "Emeteur : " + emmeteur + " | Recepteur : " + recepteur + " | Perfo : " + perfo_to_string()+ " | " +contenuMessage.to_string();
}