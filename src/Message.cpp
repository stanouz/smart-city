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


void Message::display() const{
    string strPerfo;
    if(performatif==DemandePlace){
        strPerfo="DemandePlace";
    }
    else{
        strPerfo="Réponse";
    }

    cout << "Emeteur : " << emmeteur << " | Recepteur : " << recepteur << " | Perfo : " << strPerfo;
    contenuMessage.display();
}