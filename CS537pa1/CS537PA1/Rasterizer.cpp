//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Yudong_Cao
//

#include "Rasterizer.h"
#include "simpleCanvas.h"


///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
//
///

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

///
// Draw a line from (x0,y0) to (x1, y1) on the simpleCanvas C.
//
// Implementation should be using the
//
// You are to add the implementation here using only calls
// to C.setPixel()
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
// @param C  The canvas on which to apply the draw command.
///

void Rasterizer::drawLine (int x0, int y0, int x1, int y1, simpleCanvas &C)
{
    // YOUR IMPLEMENTATION GOES HERE
    bool slope = (std::abs(y1 - y0) > std::abs(x1 - x0));
    if (slope) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x1<x0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dE, dNE, x, y, d;
    
    int dy = abs(y1 - y0);
    int dx = x1 - x0;
    dE = 2 * dy;
    dNE = 2 * ( dy-dx );
    d = dE-dx;  /* 2*dy – dx */
    
    int ystep = (y0 < y1) ? 1 : -1;
    
    for( x = x0, y = y0; x <= x1; ++x ) {
        if (slope) {
            C.setPixel(y, x);
        }
        else {
            C.setPixel( x, y );
        }
        
        if( d <= 0 ) { /* choose E */
            d += dE;
        } else {
            /* choose NE */
            y+=ystep;
            d += dNE;
        }
    }
    
}
