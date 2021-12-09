#include <iostream>

#include "Ville.h"
#include "Affichage.h"
#include <thread>

#include <unistd.h>

#include "Reservation.h"

using namespace std;



int main(int argc, char ** argv){
    
    Date inf;
    Date middle(inf, 12.);
    Date sup(middle, 12.);

    cout << inf.DateToString() << endl;
    cout << middle.DateToString() << endl;
    cout << sup.DateToString() << endl;

    if(middle.isBetween(inf, sup))
        cout << "YES" << endl;

    else
        cout << "NO" << endl;


    if(inf <= middle && sup >= middle)
<<<<<<< HEAD
        cout << "YES " << endl;
=======
        cout << "YES" << endl;
>>>>>>> Stan
    else 
        cout << "NO" << endl;



    /*
    Ville v;
    Affichage a(&v);
<<<<<<< HEAD
    a.display();
*/
=======
    a.display();*/

>>>>>>> Stan
    return 0;
}
