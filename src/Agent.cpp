#include "Agent.h"

Agent::Agent(){

}

Agent::~Agent(){
    
}

mutex Agent::m;
condition_variable Agent::cv;
map<string, vector<Message> > Agent::BoiteAuxLettres;

void Agent::sendMessage(Message & msg, string emmeteur, string recepteur){
    unique_lock<mutex> l(m);
    msg.recepteur = recepteur;
    msg.emmeteur = emmeteur;
    BoiteAuxLettres[recepteur].push_back(msg);
    messagesEnvoye.push_back(msg);
    cv.notify_all();
}


Message Agent::getMessage(string recepteur){
    unique_lock<mutex> l(m);

    while(BoiteAuxLettres[recepteur].empty()){
        cv.wait(l);
    }
    Message msg = BoiteAuxLettres[recepteur][0];
    BoiteAuxLettresPrive.push_back(msg);
    BoiteAuxLettres[recepteur].erase(BoiteAuxLettres[recepteur].begin());

    
    return msg;
}


Message Agent::getMessageFrom(string recepteur, string emmeteur){
    unique_lock<mutex> l(m);
    Message msg;

    bool waitMsgFrom = true;
    int i;
    
    while(waitMsgFrom)
    {
        i=0;
        int size = BoiteAuxLettres[recepteur].size();
        while(i<size && waitMsgFrom){
            msg = BoiteAuxLettres[recepteur][i];
            if(msg.emmeteur==emmeteur){
                waitMsgFrom=false;
            }
            else{
                i++;
            }
        }
        if(waitMsgFrom){
            cv.wait(l);
        }
    }

    BoiteAuxLettresPrive.push_back(msg);
    BoiteAuxLettres[recepteur].erase(BoiteAuxLettres[recepteur].begin()+i);
    return msg;
}   


vector<Message> Agent::getBALPrive(){
    return BoiteAuxLettresPrive;
}


vector<Message> Agent::getMsgEnvoye(){
    return messagesEnvoye;
}