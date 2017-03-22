//
//  extendedCanvas.hpp
//  CS537Mid
//
//  Created by yudong cao on 3/17/17.
//  Copyright © 2017 Yudong Cao. All rights reserved.
//

#ifndef extendedCanvas_hpp
#define extendedCanvas_hpp


#include <vector>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "simpleCanvas.h"

#include "cmatrix"

using namespace std;

//typedef techsoft::matrix<float> Matrix;

class extendedCanvas : public simpleCanvas {
private:
    ///
    // SFML polygons
    ///
    vector<sf::ConvexShape> polys;
    
    void rasterization(int n,float outx[], float outy[]);

public:

    extendedCanvas(int w, int h);
    
    void drawPoly(int n,const float x[], const float y[]);
    
    void initTransform();
    
    void translation(float x, float y);
    
    void rotation(float degrees);
    
    void scaling(float x, float y);
    
    void shearing(float a);
    
    void setClipWindow(float bottom, float top, float left, float right);
};

#endif /* extendedCanvas_hpp */
