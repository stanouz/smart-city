#include <iostream>
#include "Place.h"

using namespace std;

int main(int argc, char ** argv){
    Date d1, d2;
    d2.setDate(23, 9, 2021);

    Voiture v;

    Reservation r;    
    Reservation r1(d1, d2, v);

    Place p;

    return 0;
}