#include "Parking.h"

Parking::Parking(){

    
    for(int j=0; j<24; j++){
        grilleTarifaire[0][j]= 5;
        grilleTarifaire[1][j]= 5;
        grilleTarifaire[2][j]= 5;
        grilleTarifaire[3][j]= 5;
        grilleTarifaire[4][j]= 5;
        grilleTarifaire[5][j]= 10;
        grilleTarifaire[6][j]= 10;
    }
    
}

Parking::~Parking(){

}
