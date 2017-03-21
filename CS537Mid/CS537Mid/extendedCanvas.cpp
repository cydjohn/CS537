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
    initTransform(); // by default we set the transformation matrix to ID
}

typedef techsoft::matrix<float> Matrix;

Matrix currentTransform;

clipper::Boundary clipWindow,viewWindow;




void extendedCanvas::drawPoly(const float x1[], const float y1[], int n)
{
    
    sf::ConvexShape newPoly = sf::ConvexShape(n); // Create a Polygon
    for (int i = 0; i < n; i++)
    {
        newPoly.setPoint(i, sf::Vector2<float>(x1[i], y1[i])); // Set the vertices, vertex by vertex
    }

    float *inx = new float[n],
    *iny = new float[n];
    
    Matrix m;
    sf::Vector2<float> coord;
    
    for (int i = 0; i < n; i++)
    {
        coord = newPoly.getPoint(i);
        // compute the coordinates of the point after the transformation
        m = Matrix(3, 1, {coord.x, coord.y, 1});
        m = currentTransform * m;
        inx[i] = m[0][0];
        iny[i] = m[1][0];
    }
    
    // set in
//    int in = polys.at(polyID).getPointCount();
    int in = n;
    
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
        float x_normalized = viewWindow.lly + viewWindow.llx * ((m[0][0] - clipWindow.llx) / (clipWindow.urx - clipWindow.llx)) ;
        float y_normalized = viewWindow.lly + viewWindow.llx * ((m[1][0] - clipWindow.lly) / (clipWindow.ury - clipWindow.lly));
        x[i] = round(x_normalized);
        y[i] = round(y_normalized);
    }
    
    // draw
    rast.drawPolygon(n, x, y, *this);

    
     delete[] x, y, outx, outy;
}

void extendedCanvas::initTransform()
{
    const float ID[] = {1, 0, 0,
                        0, 1, 0,
                        0, 0, 1};
    

    
    currentTransform = Matrix(3, 3, ID);
}

void extendedCanvas::translation(float x, float y)
{

    const float TR[] = {1, 0, x,
                        0, 1, y,
                        0, 0, 1};
    
    Matrix translateTransform = Matrix(3, 3, TR);
    
    // CM = T(x, y) * CM
    currentTransform = translateTransform * currentTransform;
}

void extendedCanvas::rotation(float degrees)
{
    float theta = degrees * M_PI / 180;
    const float RO[] = {cos(theta), -sin(theta), 0,
                        sin(theta), cos(theta),  0,
                        0,         0,            1};
    
    Matrix rotateTransform = Matrix(3, 3, RO);
    
    // CM = R(theta) * CM
    currentTransform = rotateTransform * currentTransform;
}


void extendedCanvas::scaling(float x, float y)
{
    const float SC[] = {x, 0, 0,
                        0, y, 0,
                        0, 0, 1};
    
    Matrix scaleTransform = Matrix(3, 3, SC);
    
    // CM = S(x, y) * CM
    currentTransform = scaleTransform * currentTransform;
}


void extendedCanvas::setClipWindow(float bottom, float top, float left, float right)
{
    clipWindow.lly = bottom;
    clipWindow.ury = top;
    clipWindow.llx = left;
    clipWindow.urx = right;
}

void extendedCanvas::setViewport(int x, int y, int width, int height)
{
    viewWindow.lly = x;
    viewWindow.ury = y;
    viewWindow.llx = width;
    viewWindow.urx = height;
}



