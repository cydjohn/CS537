//
//  main.cpp
//  CS537Mid
//
//  Created by yudong cao on 3/15/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "extendedCanvas.hpp"

float controlNumber = 0;

void drawStar(extendedCanvas &C);
void drawSquare(extendedCanvas &C);
void drawTriangle(extendedCanvas &C);

///
// Callback for key presses.  Returns a flag indicating if the app should
// close as a result of this key press.
//
// SFML, in its infinite wisdom, doesn't actually give you the key that
// was pressed; instead, you get an sf::Keyboard::Key enumerated type
// value representing the key, with A == 0 and Z == 25.
///
bool keyTyped(enum sf::Keyboard::Key key)
{
    switch( key ) {
        case sf::Keyboard::Q:  return true; // quit
        
//            rotation
        case sf::Keyboard::R: controlNumber = 1; break;
            
//            transform
        case sf::Keyboard::T: controlNumber = 2; break;
        
//            scale
        case sf::Keyboard::S: controlNumber = 3; break;
            
//            clip
        case sf::Keyboard::C: controlNumber = 4; break;
            
//        initial state
        case sf::Keyboard::I: controlNumber = 0; break;
    }
    return false;
}

void drawOnCanvas(extendedCanvas &C) {
    
    C.setColor( 0.0f, 0.0f, 0.0f );
    C.clear();

    
    C.initTransform();
    
    C.setClipWindow( 0, 500,0, 500 );
    C.setViewport( 0,0, 500, 500 );
    
    if (controlNumber == 1) {
        C.rotation( -20 );
        drawSquare(C);
        drawStar(C);
        drawTriangle(C);
    }
    else if (controlNumber == 2) {
        
        C.translation(280, 170);
        drawSquare(C);
        
        C.translation(-200, 30);
        drawStar(C);
        
        C.translation(100, -300);
        drawTriangle(C);
    }
    else if (controlNumber == 3) {
        C.scaling(0.5, 1);
        drawSquare(C);
        drawStar(C);
        drawTriangle(C);
    }
    else if (controlNumber == 4) {
        C.setClipWindow( 30, 200,30, 200 );
        drawSquare(C);
        drawStar(C);
        drawTriangle(C);
    }
    else {
        drawSquare(C);
        drawStar(C);
        drawTriangle(C);
    }
}


int main( int argc, char *argv[] )
{

    extendedCanvas C(500, 500);

    // create and run the app
    sf::RenderWindow App(sf::VideoMode(500, 500), "CG Midterm");
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

        drawOnCanvas(C);
        
        // Draw your canvas to your window
        C.draw( App );

        App.display();
    }

    return 0;

}

void drawStar(extendedCanvas &C) {
    C.setColor(1, 1, 0);
    float x[10];
    float y[10];
    x[0] = 130; y[0] = 160;
    x[1] = 145; y[1] = 130;
    x[2] = 178; y[2] = 125;
    x[3] = 154; y[3] = 102;
    x[4] = 160; y[4] = 69;
    x[5] = 130; y[5] = 89;
    x[6] = 101; y[6] = 69;
    x[7] = 107; y[7] = 102;
    x[8] = 83; y[8] = 125;
    x[9] = 116; y[9] = 130;
    C.drawPoly( x, y, 10 );
}

void drawSquare(extendedCanvas &C) {
    C.setColor(1, 0, 0);
    float x[4];
    float y[4];
    x[0] = 5; y[0] = 75;
    x[1] = 55; y[1] = 75;
    x[2] = 55; y[2] = 125;
    x[3] = 5; y[3] = 125;
    C.drawPoly(x, y, 4);
}

void drawTriangle(extendedCanvas &C) {
    C.setColor(0, 0, 1);
    float x[3];
    float y[3];
    x[0] = 10; y[0] = 180;
    x[1] = 150; y[1] = 180;
    x[2] = 80; y[2] = 301;
    C.drawPoly(x, y, 3);
}
