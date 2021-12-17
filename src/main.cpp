#include "Ville.h"
#include "Affichage.h"


int main(int argc, char ** argv){
    Ville v;
    
    Affichage a(&v);
    a.display();

    return 0;
}
