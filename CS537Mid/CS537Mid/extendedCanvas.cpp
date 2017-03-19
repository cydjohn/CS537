//
//  extendedCanvas.cpp
//  CS537Mid
//
//  Created by yudong cao on 3/17/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#include <SFML/Config.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "extendedCanvas.hpp"


extendedCanvas::extendedCanvas(int w, int h) : simpleCanvas(w,h)
{
}

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
