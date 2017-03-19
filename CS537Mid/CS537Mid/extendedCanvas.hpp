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

using namespace std;

class extendedCanvas : public simpleCanvas {
private:
    ///
    // SFML polygons
    ///
    vector<sf::ConvexShape> polys;
public:

    extendedCanvas(int w, int h);
    
    void draw (sf::RenderWindow &R);
    
    void printLoop (int n, const float x[], const float y[] );
    
    void printPoly (int n, const float x[], const float y[] );

};

#endif /* extendedCanvas_hpp */
