#include "Agent.h"

Agent::Agent(){

}

Agent::~Agent(){
    
}


void Agent::sendMessage(Message & msg, string emmeteur, string recepteur){
    unique_lock<mutex> l(m);
    msg.recepteur = recepteur;
    msg.emmeteur = emmeteur;
    BoiteAuxLettres[recepteur].push_back(msg);

    cv.notify_all();
}


Message Agent::getMessage(string recepteur){
    unique_lock<mutex> l(m);

    while(BoiteAuxLettres[recepteur].empty()){
        cout << recepteur << " bloquer" << endl;
        cv.wait(l);
    }
    cout << recepteur << " libre" << endl;
    Message msg = BoiteAuxLettres[recepteur][0];
    BoiteAuxLettresPrivé.push_back(msg);
    BoiteAuxLettres[recepteur].erase(BoiteAuxLettres[recepteur].begin());

    
    return msg;
}


Message Agent::getMessageFrom(string recepteur, string emmeteur){
    unique_lock<mutex> l(m);
    Message msg;

    bool waitMsgFrom = true;
    int i=0;
    while(waitMsgFrom)
    {
        
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
    BoiteAuxLettresPrivé.push_back(msg);
    BoiteAuxLettres[recepteur].erase(BoiteAuxLettres[recepteur].begin()+i);
    return msg;
}   
