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
    Voiture v1("AAA-123-AAA");
    Voiture v2("BBB-123-BBB");
    Voiture v3("CCC-123-CCC");
    Voiture v4("DDD-123-DDD");
    Voiture v5("EEE-123-EEE");
    Voiture v6("FFF-123-FFF");
    Voiture v7("GGG-123-GGG");
    Voiture v8("HHH-123-HHH");
    
    thread thread_voiture1(&Voiture::Boucle, ref(v1));
    thread thread_voiture2(&Voiture::Boucle, ref(v2));
    thread thread_voiture3(&Voiture::Boucle, ref(v3));
    thread thread_voiture4(&Voiture::Boucle, ref(v4));
    thread thread_voiture5(&Voiture::Boucle, ref(v5));
    thread thread_voiture6(&Voiture::Boucle, ref(v6));
    thread thread_voiture7(&Voiture::Boucle, ref(v7));
    thread thread_voiture8(&Voiture::Boucle, ref(v8));
    thread thread_parking(&Parking::Boucle, ref(p));
    //thread thread_heure(displayHeure);

    thread_voiture1.join();
    thread_voiture2.join();
    thread_voiture3.join();
    thread_voiture4.join();
    thread_voiture5.join();
    thread_voiture6.join();
    thread_voiture7.join();
    thread_voiture8.join();

    thread_parking.join();
    //thread_heure.join();
    



    return 0;
}
