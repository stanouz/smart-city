#include <iostream>
#include "Date.h"
#include "Voiture.h"

using namespace std;

int main(int argc, char ** argv){
    Date d1;
    Date d2;
    Date d3;

    d1.setDate(3, 9, 2021);
    d3.setDate(13, 9, 2021);

    cout << d2.isBetween(d1, d3) << endl;
    cout << d2.isBetween(d2, d3) << endl;
    cout << d2.isBetween(d3, d1) << endl;
    cout << d3.isBetween(d1, d2) << endl;
    
    Voiture voiture;

    return 0;
}