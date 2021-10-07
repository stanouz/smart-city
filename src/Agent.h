#ifndef __AGENT__
#define __AGENT__

#include "Message.h"

#include <vector>
#include <map>
#include <queue>
#include <thread>

using namespace std;

class Agent{
public:
    Agent();
    ~Agent();
protected:
    inline static map<string, queue<Message> > BoiteAuxLettres;
    vector<Message> BoiteAuxLettresPrivé;
    int lastRead;
};

#endif