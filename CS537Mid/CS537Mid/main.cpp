//
//  main.cpp
//  CS537Mid
//
//  Created by yudong cao on 3/15/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "extendedCanvas.hpp"

float controlNumber = 6;

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
            
//            shearing
        case sf::Keyboard::H: controlNumber = 5; break;
            
//            viewport
        case sf::Keyboard::V: controlNumber = 6; break;
            
//        initial state
        case sf::Keyboard::I: controlNumber = 0; break;
    }
    return false;
}

void drawOnCanvas(extendedCanvas &C) {
    
    C.setColor( 0.0f, 0.0f, 0.0f );
    C.clear();

    
    C.initTransform();
    
    C.setClipWindow( 0, 0,500, 500 );
    C.setViewport(0, 0, 500, 500);
    
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
        C.setClipWindow( 0,0,300, 300 );
        
        drawTriangle(C);
        drawSquare(C);
        drawStar(C);
        
    }
    else if (controlNumber == 5) {
        C.shearing(0.75);
        drawSquare(C);
        drawStar(C);
        drawTriangle(C);
    }
    else if (controlNumber == 6) {
        C.setClipWindow( 100,100,300, 300 );
        C.setViewport(100, 100, 400, 400);
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
    sf::RenderWindow App(sf::VideoMode(500, 500), "Midterm Project");
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


// draw a star
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
    C.drawPoly(10, x, y );
}

//draw a triangle
void drawTriangle(extendedCanvas &C) {
    C.setColor(1, 0, 0);
    float x[3];
    float y[3];
    x[0] = 5; y[0] = 80;
    x[1] = 85; y[1] = 80;
    x[2] = 45; y[2] = 149;
    C.drawPoly(3, x, y);
}


// draw a square
void drawSquare(extendedCanvas &C) {
    C.setColor(0, 0, 1);
    float x[4];
    float y[4];
    x[0] = 105; y[0] = 175;
    x[1] = 155; y[1] = 175;
    x[2] = 155; y[2] = 225;
    x[3] = 105; y[3] = 225;
    C.drawPoly(4, x, y);
}
