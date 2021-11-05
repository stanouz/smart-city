#include <iostream>

#include "Ville.h"
#include "Affichage.h"

using namespace std;


int main(int argc, char ** argv){
    Affichage affichage;
    Ville v;
   
    thread thread_affichage(&Affichage::display, ref(affichage));
    v.lancerThread();
    

    thread_affichage.join();
    

    return 0;
}
