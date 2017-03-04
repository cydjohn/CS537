//
//  Rasterizer.cpp
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include "Rasterizer.h"
#include "simpleCanvas.h"

using namespace std;

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n - number of scanlines
//
///

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

///
// Draw a filled polygon in the simpleCanvas C.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls
// to C.setPixel()
///

void Rasterizer::drawPolygon(int n, int x[], int y[], simpleCanvas &C)
{
    // YOUR IMPLEMENTATION GOES HERE
    
    
}
