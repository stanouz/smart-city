#include <iostream>

#include "Ville.h"
#include "Affichage.h"

using namespace std;


int main(int argc, char ** argv){
    
    Ville v;
    Affichage affichage(&v);

    thread thread_affichage(&Affichage::display, ref(affichage));
    v.lancerThread();
    

    thread_affichage.join();
    

    return 0;
}
