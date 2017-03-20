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
#include "Rasterizer.h"
#include "clipper.h"
#include "cmatrix"


extendedCanvas::extendedCanvas(int w, int h) : simpleCanvas(w,h)
{
}

typedef techsoft::matrix<float> Matrix;

clipper::Boundary clipWindow;


void draw(sf::ConvexShape poly)
{

    int n = poly.getPointCount();
    
    // set inx[] and iny[] and apply transformation
    float *inx = new float[n],
    *iny = new float[n];
    
    Matrix m;
    sf::Vector2<float> coord;
    
    for (int i = 0; i < n; i++)
    {
        coord = sf::Vector2<float>(poly.getPoint(i));
        // compute the coordinates of the point after the transformation
        m = Matrix(3, 1, {coord.x, coord.y, 1});
        m = currentTransform * m;
        inx[i] = m[0][0];
        iny[i] = m[1][0];
    }
    
    // set in
    int in = poly.getPointCount();
    
    // set outx[] and outy[]
    float *outx = new float[in],
    *outy = new float[in];
    
    clipper clip;
    // clip
    n = clip.clipPolygon(in, inx, iny, outx, outy, clipWindow.llx, clipWindow.lly, clipWindow.urx, clipWindow.ury);
    
    delete[] inx, iny; // dynamic allocation
    
    // object that contain the drawPolygon
    Rasterizer rast = Rasterizer(n);
    
    int *x = new int[n],
    *y = new int[n];
    
    /*
     VXmin = x;
     VXmax = width;
     VYmin = y;
     VYmax = height;*/
    for (int i = 0; i < n; i++)
    {
        m = Matrix(3, 1, {outx[i], outy[i], 1});
        // let's normalize !
        float x_normalized = ((m[0][0] - clipWindow[2]) / (clipWindow[3] - clipWindow[2])) * viewWindow[2] + viewWindow[0],
        y_normalized = ((m[1][0] - clipWindow[0]) / (clipWindow[1] - clipWindow[0])) * viewWindow[3] + viewWindow[1];
        x[i] = round(x_normalized);
        y[i] = round(y_normalized);
    }
    
    // draw
    rast.drawPolygon(n, x, y, *this);
    //drawOutline(n, x, y);
    
    delete[] x, y, outx, outy;
}
