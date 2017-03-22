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


class extendedCanvas : public simpleCanvas {
private:
    ///
    // SFML polygons
    ///
    vector<sf::ConvexShape> polys;
    
    void rasterization(int n,float outx[], float outy[]);
    
    void clip(int in, float inx[], float iny[],float outx[], float outy[],sf::ConvexShape newPoly);

public:

    extendedCanvas(int w, int h);
    
    void drawPoly(int n,const float x[], const float y[]);
    
    void initTransform();
    
    void translation(float x, float y);
    
    void rotation(float degrees);
    
    void scaling(float x, float y);
    
    void shearing(float a);
    
    void setClipWindow(float lly, float ury, float llx, float urx);
    
     void setViewport(int x, int y, int width, int height);
};

#endif /* extendedCanvas_hpp */
