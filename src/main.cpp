#include <iostream>
#include <thread>
#include <pthread.h>


#include "Parking.h"
#include "Voiture.h"
#include "time.h"


using namespace std;


int main(int argc, char ** argv){
    /*
    Parking p("P1");
    Voiture v("AAA-123-AAA");
    
    thread thread_voiture(&Voiture::Boucle, ref(v));
    thread thread_parking(&Parking::Boucle, ref(p));

    thread_voiture.join();
    thread_parking.join();
    */
    
    Date d1;
    Date d2(d1, 768);

    cout << d2 << endl;
    


    return 0;
}
