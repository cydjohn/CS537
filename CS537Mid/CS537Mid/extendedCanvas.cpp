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
#include <iostream>

#include "extendedCanvas.hpp"
#include "Rasterizer.h"
#include "clipper.h"
#include "cmatrix"


extendedCanvas::extendedCanvas(int w, int h) : simpleCanvas(w,h)
{
    initTransform();
}

typedef techsoft::matrix<float> Matrix;


// tempMatix is for doing the polygon change
// use polygon matrix times this matrix
Matrix tempMatrix;

clipper::Boundary clipWindow,viewWindow;



// do the clip
// change the x,y in polygon before doing the clip
void extendedCanvas::tdPipeline(int in,sf::ConvexShape newPoly){
    float *inx = new float[14];
    float *iny = new float[14];
    
    float *outx = new float[14];
    float *outy = new float[14];
    Matrix m;
    sf::Vector2<float> coord;
    
    
    
    
    // Normalization
    for (int i = 0; i < in; i++)
    {
        coord = newPoly.getPoint(i);
        m = Matrix(3, 1, {coord.x, coord.y, 1});
//        m = tempMatrix * m;
        
        float xV = (viewWindow.urx - viewWindow.llx)/(clipWindow.urx-clipWindow.llx) * m[0][0] + (clipWindow.urx*viewWindow.llx - clipWindow.llx*viewWindow.urx)/(clipWindow.urx - clipWindow.llx);
        
//        std::cout<<(clipWindow.urx*viewWindow.llx - clipWindow.llx*clipWindow.urx)/(clipWindow.urx - clipWindow.llx)<<endl;
        
        float yV = (viewWindow.ury - viewWindow.lly)/(clipWindow.ury-clipWindow.lly) * m[1][0] + (clipWindow.ury*viewWindow.lly - clipWindow.lly*viewWindow.ury)/(clipWindow.ury - clipWindow.lly);
        
        
        //        std::cout<<(clipWindow.ury*viewWindow.lly - clipWindow.lly*clipWindow.ury)/(clipWindow.ury - clipWindow.lly)<<std::endl;
        
        inx[i] = xV;
        iny[i] = yV;
        
    }
    
    
    
    
    clipper clip;
    // clip
    in = clip.clipPolygon(in, inx, iny, outx, outy, clipWindow.llx, clipWindow.lly, clipWindow.urx, clipWindow.ury);
    int *x = new int[in];
    int *y = new int[in];
    
    
    
//    Viewing Transform
    for (int i = 0; i < in; i++)
    {
        m = Matrix(3, 1, {outx[i], outy[i], 1});
        m = tempMatrix * m;
        x[i] = m[0][0];
        y[i] = m[1][0];
    }
    
    
//    Rasterization
    if (in > 0) {
        Rasterizer rasterizer = Rasterizer(in);
        rasterizer.drawPolygon(in, x,y, *this);
    }
    
    free(x);
    free(y);
    
    free(outx);
    free(outy);
    free(inx);
    free(iny);
    
}




// 2D pipline
void extendedCanvas::drawPoly(int n,const float x[], const float y[])
{
    
    sf::ConvexShape newPoly = sf::ConvexShape(n); // Create a Polygon
    for (int i = 0; i < n; i++)
    {
        newPoly.setPoint(i, sf::Vector2<float>(x[i], y[i])); // Set the vertices, vertex by vertex
    }

    
    
    //2D pipeline
    tdPipeline(n, newPoly);
    

}


// initialize the tempMatix
void extendedCanvas::initTransform()
{
    const float initMatrix[] = {1, 0, 0,
                                0, 1, 0,
                                0, 0, 1};
    
    tempMatrix = Matrix(3, 3, initMatrix);
}

// position translation
void extendedCanvas::translation(float x, float y)
{
    const float translateTransformMatrix[] = {1, 0, x,
                                            0, 1, y,
                                            0, 0, 1};
    
    Matrix translateTransform = Matrix(3, 3, translateTransformMatrix);
    
    tempMatrix = translateTransform * tempMatrix;
}


//rostation
void extendedCanvas::rotation(float degrees)
{
    float theta = degrees * M_PI / 180;
//    const float rotateTransformMatrix[] = {cos(theta), -sin(theta), 0,
//                                            sin(theta), cos(theta),  0,
//                                            0,         0,            1};
    
    const float rotateTransformMatrix[] = {cos(theta), -sin(theta), 250*(1-cos(theta))+250*sin(theta),
        sin(theta), cos(theta),  250*(1-cos(theta))-250*sin(theta),
        0,         0,            1};
    
    Matrix rotateTransform = Matrix(3, 3, rotateTransformMatrix);
    

    tempMatrix = rotateTransform * tempMatrix;
}

//scaling
void extendedCanvas::scaling(float x, float y)
{
    const float scaleTransformMatrix[] = {x, 0, 0,
                                        0, y, 0,
                                        0, 0, 1};
    
    Matrix scaleTransform = Matrix(3, 3, scaleTransformMatrix);
    
    tempMatrix = scaleTransform * tempMatrix;
}

// shearing
void extendedCanvas::shearing(float a) {
    const float shearingTransformMatrix[] = {1, a, 0,
                                            0,1,0,
                                            0,0,1};
    Matrix shearingTransform = Matrix(3,3,shearingTransformMatrix);
    tempMatrix = shearingTransform * tempMatrix;
}

//set clip window size
void extendedCanvas::setClipWindow(float llx, float lly, float ury, float urx)
{
    clipWindow.lly = lly;
    clipWindow.ury = ury;
    clipWindow.llx = llx;
    clipWindow.urx = urx;
}

// set viewprot size
void extendedCanvas::setViewport(int x, int y, int width, int height)
{
    viewWindow.llx = x;
    viewWindow.lly = y;
    viewWindow.urx = width;
    viewWindow.ury = height;

}



