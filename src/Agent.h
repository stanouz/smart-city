#ifndef __AGENT__
#define __AGENT__

#include "Message.h"

#include <vector>
using namespace std;

class Agent{
public:
    Agent();
    ~Agent();
    inline static vector<Message> BoiteAuxLettres[2];
};
#endif