#include <iostream>

#include "Ville.h"
#include "Affichage.h"
#include <thread>

using namespace std;



int main(int argc, char ** argv){
    
    Ville v;
    
    
    Affichage a(&v);
    a.display();

    

    return 0;
}
