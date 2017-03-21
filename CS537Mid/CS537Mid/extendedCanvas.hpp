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
    


public:

    extendedCanvas(int w, int h);
    
    void drawPoly(const float x1[], const float y1[], int n);
    
    void initTransform();
    
    void translation(float x, float y);
    
    void rotation(float degrees);
    
    void scaling(float x, float y);
    
    void setClipWindow(float bottom, float top, float left, float right);
    
    void setViewport(int x, int y, int width, int height);

};

#endif /* extendedCanvas_hpp */
