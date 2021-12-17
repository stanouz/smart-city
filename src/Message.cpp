#include "Message.h"
#include <iostream>

Message::Message(){

}

Message::Message(string emmeteur_, Performatif perfo){
    emmeteur = emmeteur_;
    performatif = perfo;
    
}

Message::~Message(){
    
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
        default : break;
    }
    return " ";
}

string Message::to_string(){
    return "Emeteur : " + emmeteur + " | Recepteur : " + recepteur + " | Perfo : " + perfo_to_string()+ " | " +contenuMessage.to_string();
}