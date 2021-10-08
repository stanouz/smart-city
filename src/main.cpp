#include <iostream>
#include <thread>
#include <pthread.h>


#include "Parking.h"
#include "Voiture.h"
#include "time.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


using namespace std;

using namespace sf;
Font font;

void LoadFont()
{
    if(!font.loadFromFile("res/poppins.ttf"))
    {

        cout<<"erreur chargement"<<endl;
    }
}
int main(int argc, char ** argv){
    /*
    if(argc>0){
        
        if(argv[1]==string("1")){
            
            //cration d'une fenetre de type RenderWindow
            RenderWindow window(VideoMode(1500,1500,32),"mon titre");


            LoadFont();
            Text txt; 
            txt.setFont(font);
            txt.setString("Gestion intelligente de parkings dans un centre urbain");
            txt.setCharacterSize(36);
            txt.setFillColor(Color::Blue);
            
            //txt.setScale(10,10);
            txt.setPosition(350,400);
            //txt.move(5,5);
            
            while(window.isOpen())
            {
                Event event ;
                while (window.pollEvent(event))
                {
                    //Si on clique sur la croix
                    if(event.type == Event::Closed)
                    {
                        //On ferme la fenetre
                        window.close();
                    }
                }
                window.clear(Color::Black);
                window.draw(txt);
                
                window.display();
            }
        }
    }
    */


 
    Parking p("P1");
    Voiture v("AAA-123-AAA");
    
    thread thread_voiture(&Voiture::Boucle, ref(v));
    thread thread_parking(&Parking::Boucle, ref(p));

    thread_voiture.join();
    thread_parking.join();
    


    return 0;
}
