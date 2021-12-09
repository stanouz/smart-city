#include <iostream>

#include "Ville.h"
#include "Affichage.h"
#include <thread>

#include <unistd.h>

#include "Reservation.h"

using namespace std;



int main(int argc, char ** argv){
    
    
    Ville v;
    Affichage a(&v);
    a.display();

    return 0;
}
