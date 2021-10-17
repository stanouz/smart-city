#include <iostream>
#include <thread>
#include <pthread.h>
#include <cstdlib>


#include "Parking.h"
#include "Voiture.h"
#include "time.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


using namespace std;

using namespace sf;
Font font;
Font myfont;
Texture textureImg;
Image image1;

void LoadFont()
{
   if(!font.loadFromFile("res/poppins.ttf"))
    {

        cout<<"erreur chargement"<<endl;
    }
if(!myfont.loadFromFile("res/poppins.ttf"))
    {

        cout<<"erreur chargement"<<endl;
    }

}

int main(int argc, char ** argv){
    



  //cration d'une fenetre de type RenderWindow
   RenderWindow window(VideoMode(1500,1500,32),"mon titre");

    LoadFont();
    Text txt;
    
    txt.setFont(font);
    txt.setString("$$$$$$$");
  

    txt.setCharacterSize(32);
    txt.setFillColor(Color::Blue);
    txt.setPosition(350,40);
    //txt.setScale(10,10);
   
    //txt.move(5,5);
LoadFont(); 
    Text txt1;
      
    txt1.setFont(myfont);
    txt1.setString("hhhhhhhhhhhhh");
    txt1.setCharacterSize(48);
    txt1.setFillColor(Color::Green);
    txt1.setPosition(700,100);

    Texture textureImg;
    if(!textureImg.loadFromFile("res/image.png")){
                cout << "erreur texture" << endl;

    }
    
    
    Sprite imageSprite(textureImg);

    sf::Vector2u size = textureImg.getSize();
    imageSprite.setOrigin(size.x /2, size.y/2);
  
    imageSprite.setPosition(800., 600.);

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
        window.draw(txt1);
        window.draw(imageSprite);
        window.display();


               
    }


    /*
    Parking p("P1");
    Voiture v("AAA-123-AAA");
    
    thread thread_voiture(&Voiture::Boucle, ref(v));
    thread thread_parking(&Parking::Boucle, ref(p));

    thread_voiture.join();
    thread_parking.join();
    */
   


      

       

    return 0;
}
