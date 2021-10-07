#ifndef __MESSAGE__
#define __MESSAGE__

#include <string>
#include "Contenu.h"

enum Performatif{DemandePlace, Reponse, Refut};

class Message{
public:
    Message();
    Message(string emmeteur_, Performatif perfo);
    ~Message();
    void display() const;

    string emmeteur;
    string recepteur;
    Performatif performatif;
    Contenu contenuMessage;
};

#endif