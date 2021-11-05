#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>



#include "Parking.h"
#include "Voiture.h"
#include "time.h"



#include "Affichage.h"

using namespace std;



int main(int argc, char ** argv){


    Affichage affichage;
    //AffichageMessage affichagemessage;

    
    thread thread_affichage(&Affichage::display, ref(affichage));

   //thread thread_affichagemessage(&AffichageMessage::display, ref(affichagemessage));
/*
    
    Parking p("P1");
    Voiture v1("AAA-123-AAA");
    Voiture v2("BBB-123-BBB");
    Voiture v3("CCC-123-CCC");
    Voiture v4("DDD-123-DDD");
    Voiture v5("EEE-123-EEE");
    Voiture v6("FFF-123-FFF");
    Voiture v7("GGG-123-GGG");
    Voiture v8("HHH-123-HHH");
    
    thread thread_voiture1(&Voiture::Boucle, ref(v1));
    thread thread_voiture2(&Voiture::Boucle, ref(v2));
    thread thread_voiture3(&Voiture::Boucle, ref(v3));
    thread thread_voiture4(&Voiture::Boucle, ref(v4));
    thread thread_voiture5(&Voiture::Boucle, ref(v5));
    thread thread_voiture6(&Voiture::Boucle, ref(v6));
    thread thread_voiture7(&Voiture::Boucle, ref(v7));
    thread thread_voiture8(&Voiture::Boucle, ref(v8));
    thread thread_parking(&Parking::Boucle, ref(p));
    */
    thread_affichage.join();

    //thread_affichagemessage.join();
/*    
    thread_voiture1.join();
    thread_voiture2.join();
    thread_voiture3.join();
    thread_voiture4.join();
    thread_voiture5.join();
    thread_voiture6.join();
    thread_voiture7.join();
    thread_voiture8.join();

    thread_parking.join();
    

*/
    return 0;
}
