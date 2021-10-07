#include <iostream>
#include <thread>
#include <pthread.h>


#include "Parking.h"
#include "Voiture.h"
#include "time.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace std;


int main(int argc, char ** argv){
    
    Parking p("P1");
    Voiture v("AAA-123-AAA");
    
    thread thread_voiture(&Voiture::Boucle, ref(v));
    thread thread_parking(&Parking::Boucle, ref(p));

    thread_voiture.join();
    thread_parking.join();
    


    return 0;
}
