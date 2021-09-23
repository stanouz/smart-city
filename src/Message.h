#ifndef __MESSAGE__
#define __MESSAGE__

#include <string>
#include "Contenu.h"

class Message{
public:
    Message();
    ~Message();

    string emmeteur;
    string recepteur;
    Contenu contenuMessage;
};

#endif