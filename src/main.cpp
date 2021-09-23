#include <iostream>
#include "Parking.h"

using namespace std;

int main(int argc, char ** argv){

    Parking p;
    cout << p.checkMessage() << endl;
    Voiture v;
    v.sendMessage();
    cout << p.checkMessage() << endl;
    

    return 0;
}