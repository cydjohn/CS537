//
//  extendedCanvas.cpp
//
//  Created by Srinivas Sridharan on 2/17/2017.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//  
//  This file should not be modified by students.
//

#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "extendedCanvas.h"

///
// This is a special subclass of simpleCanvas with functionality
// for testing out the clipping assignment.
//
// Note, this class should only be used for the clipping assignment
// and only for testing purposes!!!
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///

extendedCanvas::extendedCanvas(int w, int h) : simpleCanvas(w,h)
{
}

///
// prints a poly outline -- for cliptest assignment
///

void extendedCanvas::printLoop (int n, const float x[], const float y[] )
{
    sf::ConvexShape P;
    P.setPointCount( n );
    P.setOutlineColor( myColor );
    P.setOutlineThickness( 1 );

    for( int i=0; i < n; i++ )
        P.setPoint( i, sf::Vector2f(x[i], height - y[i]) );

    // print it as a polygon whose body is transparent
    P.setFillColor( sf::Color::Transparent );
    polys.push_back (P);
}

///
// draws a filled poly -- for cliptest assignment
///

void extendedCanvas::printPoly (int n, const float x[], const float y[] )
{
    sf::ConvexShape P;
    P.setPointCount( n );
    P.setFillColor( myColor );
    P.setOutlineColor( myColor );
    P.setOutlineThickness( 1 );

    for (int i=0; i < n; i++)
        P.setPoint( i, sf::Vector2f(x[i], height - y[i]) );

    polys.push_back (P);
}



///
// draw yourself into a given renderWindow
//
// @param R - the window in which to draw.
///

void extendedCanvas::draw (sf::RenderWindow &R)
{
    // draw as usual
    simpleCanvas::draw (R);

    // draw your polys
    vector<sf::ConvexShape>::iterator it;
    for (it = polys.begin(); it != polys.end(); it++) {
        R.draw ((*it));
    }
}
