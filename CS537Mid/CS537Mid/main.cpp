//
//  main.cpp
//  CS537Mid
//
//  Created by yudong cao on 3/15/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "extendedCanvas.hpp"



int main( int argc, char *argv[] )
{

    // define your canvas
    extendedCanvas C(300, 300);

    // load all of your polygons
    float x[12];
    float y[12];

//    // triangle
//    C.setColor ( 0.7f, 0.7f, 0.7f );
//    x[0] = 25.0f; y[0] = 125.0f;
//    x[1] = 75.0f; y[1] = 125.0f;
//    x[2] = 50.0f; y[2] = 175.0f;
//    C.printPoly( 3,x, y );
//
//    // square
//    x[0] = 125.0f; y[0] = 125.0f;
//    x[1] = 175.0f; y[1] = 125.0f;
//    x[2] = 175.0f; y[2] = 175.0f;
//    x[3] = 125.0f; y[3] = 175.0f;
//    C.printPoly( 4,x, y );
//
//    // octagon
//    x[0] = 25.0f; y[0] = 25.0f;
//    x[1] = 35.0f; y[1] = 15.0f;
//    x[2] = 55.0f; y[2] = 15.0f;
//    x[3] = 75.0f; y[3] = 25.0f;
//    x[4] = 75.0f; y[4] = 55.0f;
//    x[5] = 55.0f; y[5] = 75.0f;
//    x[6] = 35.0f; y[6] = 75.0f;
//    x[7] = 25.0f; y[7] = 55.0f;
//    C.printPoly( 8,x, y );

//    // star
//    x[0] = 150.0f; y[0] = 90.0f;
//    x[1] = 140.0f; y[1] = 65.0f;
//    x[2] = 110.0f; y[2] = 65.0f;
//    x[3] = 140.0f; y[3] = 40.0f;
//    x[4] = 110.0f; y[4] = 10.0f;
//    x[5] = 150.0f; y[5] = 25.0f;
//    x[6] = 190.0f; y[6] = 10.0f;
//    x[7] = 160.0f; y[7] = 40.0f;
//    x[8] = 190.0f; y[8] = 65.0f;
//    x[9] = 160.0f; y[9] = 65.0f;
//    C.printPoly( 10,x, y );
    
    C.setColor(1, 1, 0);
    x[0] = 30; y[0] = 160;
    x[0] = 45; y[0] = 130;
    x[0] = 78; y[0] = 125;
    x[0] = 54; y[0] = 102;
    x[0] = 60; y[0] = 69;
    x[0] = 30; y[0] = 89;
    x[0] = 1; y[0] = 69;
    x[0] = 7; y[0] = 102;
    x[0] = 0; y[0] = 125;
    x[0] = 16; y[0] = 130;
    C.printPoly(10, x, y);




    // create and run the app
    sf::RenderWindow App(sf::VideoMode(300, 300), "CG Midterm");
    while( App.isOpen() )
    {
        // Process events
        sf::Event Event;
        while( App.pollEvent(Event) )
        {
            // Close window : exit
            if( Event.type == sf::Event::Closed )
                App.close();

//            // Keypress
//            if( Event.type == sf::Event::KeyPressed )
//                if( keyTyped(Event.key.code) )
//                    App.close();
//
//            // Mouse click
//            if( Event.type == sf::Event::MouseButtonPressed )
//                displayNumber++;
        }

        // Clear screen
        App.clear();

        // draw on your canvas
//        doDraw(C);

        // Draw your canvas to your window
        C.draw( App );

        App.display();
    }

    return 0;

}
