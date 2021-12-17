#ifndef __MESSAGE__
#define __MESSAGE__

#include <string>
#include "Contenu.h"
#include "Enums.h"

class Message{
public:
    Message();
    Message(string emmeteur_, Performatif perfo);
    Message(string emmeteur_, Performatif perfo, Position p);
    ~Message();
    void display();
    string to_string();
    string perfo_to_string();

    void operator=(Message msg);

    string emmeteur;
    string recepteur;
    Performatif performatif;
    Contenu contenuMessage;
};

#endif