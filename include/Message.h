#ifndef __MESSAGE__
#define __MESSAGE__

#include <string>
#include "Contenu.h"

enum Performatif{DemandePlace, Reponse, Refut, Accepter};

class Message{
public:
    Message();
    Message(string emmeteur_, Performatif perfo);
    ~Message();
    void display();
    string to_string();

    string emmeteur;
    string recepteur;
    Performatif performatif;
    Contenu contenuMessage;
};

#endif