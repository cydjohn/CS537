//
//  Rasterizer.h
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  Yudong Cao
//

#ifndef _RASTERIZER_H
#define _RASTERIZER_H

class simpleCanvas;

///
//
// Simple class that performs rasterization algorithms
//
///

class Rasterizer {

public:
    ///
    // Constructor
    //
    // @param n - number of scanlines
    //
    ///
    Rasterizer (int n);

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
    void drawPolygon(int n, int x[], int y[], simpleCanvas &C);

private:
    ///
    // number of scanlines
    ///
    int n_scanlines;
};


#endif
