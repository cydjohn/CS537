//
//  test.cpp
//  CS537PA2
//
//  Created by yudong cao on 2/19/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "simpleCanvas.h"
#include "Rasterizer.h"

bool keyTyped(enum sf::Keyboard::Key key)
{
    switch( key ) {
        case sf::Keyboard::Q:  return true;                     // quit
    }
    
    return false;
}

///
//
// main program for polygon fill assignment
//
///

int main (int argc, char *argv[])
{
    simpleCanvas T( 901, 601 );
    Rasterizer R( 601 );
    T.setColor( 0.0, 0.0, 0.0 );
    T.clear();
    T.setColor( 1.0, 0.0, 0.0 );
    
    int x[10];
    int y[10];
    
  
    
    // ############ STAR #############

    x[0] = 230;  y[0] = 389;
    x[1] = 260;  y[1] = 369;
    x[2] = 254;  y[2] = 402;
    x[3] = 278;  y[3] = 425;
    x[4] = 245;  y[4] = 430;
    x[5] = 230;  y[5] = 460;
    x[6] = 230;  y[6] = 410;
    
    
    x[6] = 216;  y[6] = 430;
    x[7] = 183;  y[7] = 425;
    x[8] = 207;  y[8] = 402;
    x[9] = 201;  y[9] = 369;

    
    T.setColor( 0.8, 0.8, 0.0 );
    R.drawPolygon( 10, x, y, T );
    
       
    sf::RenderWindow App( sf::VideoMode(901, 601), "Poly Fill Test" );
    while( App.isOpen() )
    {
        // Process events
        sf::Event Event;
        while( App.pollEvent(Event) )
        {
            // Close window : exit
            if( Event.type == sf::Event::Closed )
                App.close();
            
            // Keypress
            if( Event.type == sf::Event::KeyPressed )
                if( keyTyped(Event.key.code) )
                    App.close();
        }
        
        // Clear screen
        App.clear();
        
        // Draw your canvas
        T.draw( App );
        
        App.display();
    }
    
    return 0;
    
}
