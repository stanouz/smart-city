#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>


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


void Fenetre(){
    //cration d'une fenetre de type RenderWindow
    RenderWindow window(VideoMode(500,500,32),"mon titre");

    
    LoadFont();
    Text txt; 
    txt.setFont(font);
    
    txt.setCharacterSize(20);
    txt.setFillColor(Color::Blue);
    txt.setPosition(50,50);
            
    while(window.isOpen())
    {
        Event event ;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
            Date now;
            txt.setString(now.DateToString());
            window.clear(Color::Black);
            window.draw(txt);
                
            window.display();
            usleep(100000);
        }
    }
}


void displayHeure(){
    while(true){
        Date now;
        cout << "======= " << now << endl;
        usleep(1000000);
    }
}

int main(int argc, char ** argv){
    
    
    Parking p("P1");
    Voiture v("AAA-123-AAA");
    
    thread thread_voiture(&Voiture::Boucle, ref(v));
    thread thread_parking(&Parking::Boucle, ref(p));
    //thread thread_heure(displayHeure);

    thread_voiture.join();
    thread_parking.join();
    



    return 0;
}
