#ifndef __AGENT__
#define __AGENT__

#include "Message.h"

#include <vector>
#include <map>
#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Agent{
public: 
    Agent();
    ~Agent();
    void sendMessage(Message & m, string emmeteur, string recepteur);
    Message getMessage(string recepteur);
    Message getMessageFrom(string recepteur, string emmeteur);

    vector<Message> getBALPrive();
    vector<Message> getMsgEnvoye();


protected:
    static mutex m;
    static condition_variable cv;
    static map<string, vector<Message> > BoiteAuxLettres;
    vector<Message> BoiteAuxLettresPrive;
    vector<Message> messagesEnvoye;
};

#endif