//
//  fillTest.cpp
//
//  created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#include <SFML/Graphics.hpp>
#include "simpleCanvas.h"
#include "Rasterizer.h"

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

    // ########### TEAPOT START ###########
    // BASE
    x[0] = 760;  y[0] = 40;
    x[1] = 600;  y[1] = 40;
    x[2] = 620;  y[2] = 60;
    x[3] = 740;  y[3] = 60;
    R.drawPolygon( 4, x, y, T );

    // RIGHT BOTTOM TRIANGLE
    x[0] = 800;  y[0] = 120;
    x[1] = 740;  y[1] = 60;
    x[2] = 620;  y[2] = 60;
    T.setColor( 0.90, 0.0, 0.0 );
    R.drawPolygon( 3, x, y, T );

    // SPOUT
    x[0] = 620;  y[0] = 60;
    x[1] = 560;  y[1] = 100;
    x[2] = 500;  y[2] = 180;
    T.setColor( 0.80, 0.0, 0.0 );
    R.drawPolygon( 3, x, y, T );

    x[0] = 620;  y[0] = 60;
    x[1] = 500;  y[1] = 180;
    x[2] = 460;  y[2] = 200;
    x[3] = 520;  y[3] = 200;
    x[4] = 580;  y[4] = 160;
    T.setColor( 0.7, 0.0, 0.0 );
    R.drawPolygon( 5, x, y, T );

    x[0] = 620;  y[0] = 60;
    x[1] = 580;  y[1] = 160;
    x[2] = 620;  y[2] = 240;
    x[3] = 740;  y[3] = 240;
    x[4] = 800;  y[4] = 120;
    T.setColor( 0.6, 0.0, 0.0 );
    R.drawPolygon( 5, x, y, T );

    x[0] = 800;  y[0] = 120;
    x[1] = 840;  y[1] = 160;
    x[2] = 855;  y[2] = 200;
    x[3] = 720;  y[3] = 220;
    x[4] = 720;  y[4] = 200;
    x[5] = 830;  y[5] = 190;
    x[6] = 825;  y[6] = 165;
    x[7] = 780;  y[7] = 120;
    T.setColor( 0.5, 0.0, 0.0 );
    R.drawPolygon( 8, x, y, T );

    x[0] = 690;  y[0] = 240;
    x[1] = 710;  y[1] = 260;
    x[2] = 650;  y[2] = 260;
    x[3] = 670;  y[3] = 240;
    T.setColor( 0.4, 0.0, 0.0 );
    R.drawPolygon( 4, x, y, T );

    // ######## TRIANGLE #######
    x[0] = 460;  y[0] = 220;
    x[1] = 490;  y[1] = 280;
    x[2] = 420;  y[2] = 280;
    T.setColor( 0.0, 1.0, 0.0 );
    R.drawPolygon( 3, x, y, T );

    // ########## QUAD ##########
    x[0] = 380;  y[0] = 280;
    x[1] = 320;  y[1] = 320;
    x[2] = 360;  y[2] = 380;
    x[3] = 420;  y[3] = 340;
    T.setColor( 0.0, 0.8, 0.8 );
    R.drawPolygon( 4, x, y, T );

    // ############ STAR #############
    // RIGHT SIDE
    x[0] = 230;  y[0] = 389;
    x[1] = 260;  y[1] = 369;
    x[2] = 254;  y[2] = 402;
    x[3] = 278;  y[3] = 425;
    x[4] = 245;  y[4] = 430;
    x[5] = 230;  y[5] = 460;
    x[6] = 230;  y[6] = 410;
    

//    x[6] = 216;  y[6] = 430;
//    x[7] = 183;  y[7] = 425;
//    x[8] = 207;  y[8] = 402;
//    x[9] = 201;  y[9] = 369;
//    x[10] = 230;  y[10] = 389;

    T.setColor( 0.8, 0.8, 0.0 );
    R.drawPolygon( 7, x, y, T );

    // LEFT SIDE
    x[0] = 230;  y[0] = 460;
    x[1] = 216;  y[1] = 430;
    x[2] = 183;  y[2] = 425;
    x[3] = 207;  y[3] = 402;
    x[4] = 201;  y[4] = 369;
    x[5] = 230;  y[5] = 389;
    x[6] = 230;  y[6] = 410;
    T.setColor( 0.7, 0.7, 0.0 );
    R.drawPolygon( 7, x, y, T );

    // ########## BORDERS ###############
    // SQUARE BOTTOM LEFT
    x[0] = 0;    y[0] = 0;
    x[1] = 0;    y[1] = 20;
    x[2] = 20;   y[2] = 20;
    x[3] = 20;   y[3] = 0;
    T.setColor( 0.0, 0.0, 1.0 );
    R.drawPolygon( 4, x, y, T );

    x[0] = 0;    y[0] = 10;
    x[1] = 10;   y[1] = 10;
    x[2] = 10;   y[2] = 580;
    x[3] = 0;    y[3] = 580;
    T.setColor( 0.0, 0.1, 0.9 );
    R.drawPolygon( 4, x, y, T );

    x[0] = 0;    y[0] = 580;
    x[1] = 0;    y[1] = 600;
    x[2] = 20;   y[2] = 600;
    x[3] = 20;   y[3] = 580;
    T.setColor( 0.0, 0.2, 0.8 );
    R.drawPolygon( 4, x, y, T );

    //  TRIANGLE TOP:TOP
    x[0] = 10;   y[0] = 590;
    x[1] = 10;   y[1] = 600;
    x[2] = 880;  y[2] = 600;
    T.setColor( 0.0, 0.3, 0.7 );
    R.drawPolygon( 3, x, y, T );

    //  TRIANGLE TOP:BOTTOM
    x[0] = 10;   y[0] = 590;
    x[1] = 880;  y[1] = 590;
    x[2] = 880;  y[2] = 600;
    T.setColor( 0.0, 0.4, 0.6 );
    R.drawPolygon( 3, x, y, T );

    // SQUARE TOP RIGHT
    x[0] = 900;  y[0] = 600;
    x[1] = 900;  y[1] = 580;
    x[2] = 880;  y[2] = 580;
    x[3] = 880;  y[3] = 600;
    T.setColor( 0.1, 0.4, 0.5 );
    R.drawPolygon( 4, x, y, T );

    //  TRIANGLE RIGHT:RIGHT
    x[0] = 890;  y[0] = 580;
    x[1] = 900;  y[1] = 580;
    x[2] = 890;  y[2] = 20;
    T.setColor( 0.2, 0.4, 0.4 );
    R.drawPolygon( 3, x, y, T );

    //  TRIANGLE RIGHT:LEFT
    x[0] = 900;  y[0] = 580;
    x[1] = 900;  y[1] = 20;
    x[2] = 890;  y[2] = 20;
    T.setColor( 0.3, 0.4, 0.3 );
    R.drawPolygon( 3, x, y, T );

    // SQUARE BOTTOM RIGHT
    x[0] = 900;  y[0] = 0;
    x[1] = 900;  y[1] = 20;
    x[2] = 880;  y[2] = 20;
    x[3] = 880;  y[3] = 0;
    T.setColor( 0.4, 0.4, 0.2 );
    R.drawPolygon( 4, x, y, T );

    // QUAD BOTTOM
    x[0] = 20;   y[0] = 0;
    x[1] = 20;   y[1] = 10;
    x[2] = 880;  y[2] = 10;
    x[3] = 880;  y[3] = 0;
    T.setColor( 0.4, 0.5, 0.1 );
    R.drawPolygon( 4, x, y, T );

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
