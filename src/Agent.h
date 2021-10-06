#ifndef __AGENT__
#define __AGENT__

#include "Message.h"

#include <vector>
#include <map>
#include <thread>

using namespace std;

class Agent{
public:
    Agent();
    ~Agent();
protected:
    inline static map<string, vector<Message> > BoiteAuxLettres;
    int lastRead;
};

#endif