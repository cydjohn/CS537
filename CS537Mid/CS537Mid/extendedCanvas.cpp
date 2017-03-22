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

void clip(int in, float inx[], float iny[],
          float outx[], float outy[],sf::ConvexShape newPoly){
    Matrix m;
    sf::Vector2<float> coord;
    
    for (int i = 0; i < in; i++)
    {
        coord = newPoly.getPoint(i);
        // compute the coordinates of the point after the transformation
        m = Matrix(3, 1, {coord.x, coord.y, 1});
        m = currentTransform * m;
        inx[i] = m[0][0];
        iny[i] = m[1][0];
    }
    
    clipper clip;
    // clip
    in = clip.clipPolygon(in, inx, iny, outx, outy, clipWindow.llx, clipWindow.lly, clipWindow.urx, clipWindow.ury);
}

void extendedCanvas::rasterization(int n,float outx[], float outy[]){
    Matrix m;
    // object that contain the drawPolygon
    Rasterizer rasterizer = Rasterizer(n);
    
    int *x = new int[n],
    *y = new int[n];
    
    for (int i = 0; i < n; i++)
    {
        m = Matrix(3, 1, {outx[i], outy[i], 1});
        // normalize !
        
//        spoint.x +(boundary.lly - spoint.y) * (epoint.x - spoint.x) / (epoint.y - spoint.y);
        float x_normalized = 500 * ((m[0][0] - clipWindow.llx) / (clipWindow.urx - clipWindow.llx)) ;
        
        
//        spoint.y +(boundary.llx - spoint.x) * (epoint.y - spoint.y) / (epoint.x - spoint.x);
        float y_normalized = 500 * ((m[1][0] - clipWindow.lly) / (clipWindow.ury - clipWindow.lly));
        x[i] = int(x_normalized + 0.5);
        y[i] = int(y_normalized + 0.5);
    }
    
    // draw
    rasterizer.drawPolygon(n, x, y, *this);
}


void extendedCanvas::drawPoly(int n,const float x[], const float y[])
{
    
    sf::ConvexShape newPoly = sf::ConvexShape(n); // Create a Polygon
    for (int i = 0; i < n; i++)
    {
        newPoly.setPoint(i, sf::Vector2<float>(x[i], y[i])); // Set the vertices, vertex by vertex
    }

    float *inx = new float[n];
    float *iny = new float[n];

    float *outx = new float[n];
    float *outy = new float[n];

    
    clip(n, inx, iny, outx, outy, newPoly);

    rasterization(n, outx, outy);
    
     delete[] outx, outy,inx, iny;;
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
    
    currentTransform = translateTransform * currentTransform;
}

void extendedCanvas::rotation(float degrees)
{
    float theta = degrees * M_PI / 180;
    const float RO[] = {cos(theta), -sin(theta), 0,
                        sin(theta), cos(theta),  0,
                        0,         0,            1};
    
    Matrix rotateTransform = Matrix(3, 3, RO);
    

    currentTransform = rotateTransform * currentTransform;
}


void extendedCanvas::scaling(float x, float y)
{
    const float SC[] = {x, 0, 0,
                        0, y, 0,
                        0, 0, 1};
    
    Matrix scaleTransform = Matrix(3, 3, SC);
    
    currentTransform = scaleTransform * currentTransform;
}

void extendedCanvas::shearing(float a) {
    const float SH[] = {1, a, 0,
                        0,1,0,
        0,0,1};
    Matrix shearingTransform = Matrix(3,3,SH);
    currentTransform = shearingTransform * currentTransform;
}

void extendedCanvas::setClipWindow(float bottom, float top, float left, float right)
{
    clipWindow.lly = bottom;
    clipWindow.ury = top;
    clipWindow.llx = left;
    clipWindow.urx = right;
}





