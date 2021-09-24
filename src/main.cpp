#include <iostream>
#include <thread>
#include "Parking.h"
#include "time.h"


using namespace std;

void BoucleVoiture(Voiture & v){
    v.Boucle();
}

void BoucleParking(Parking & p){
    p.Boucle();
}


int main(int argc, char ** argv){

    Parking p;
    Voiture v;

    thread thread_voiture(BoucleVoiture, ref(v));
    thread thread_parking(BoucleParking, ref(p));
    
    cout << "ok" << endl;
    thread_voiture.join();
    thread_parking.join();

    return 0;
}