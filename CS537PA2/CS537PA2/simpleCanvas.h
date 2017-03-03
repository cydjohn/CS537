//
//  simpleCanvas.h
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  This file should not be modified by students.
//

#ifndef _SIMPLECANVAS_H
#define _SIMPLECANVAS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

///
// Simple canvas class that allows for pixel-by-pixel rendering.
//
///

class simpleCanvas {

private:
    ///
    // height and width of the canvas
    ///
    int width;
    int height;

    sf::Image myImage;
    sf::Color myColor;

public:
    ///
    // Constructor
    //
    // @param w width of canvas
    // @param h height of canvas
    ///
    simpleCanvas(int w, int h);

    ///
    // clears the canvas using the current color
    ///
    void clear();

    ///
    // draw yourself into a given renderWindow
    //
    // @param R - the window in which to draw.
    ///
    void draw (sf::RenderWindow &R);

    ///
    // Sets the current color
    //
    // @param r - The red component of the new color (between 0-1)
    // @param g - The green component of the new color (between 0-1)
    // @param b - The blue component of the new color (between 0-1);
    ///
    void setColor (float r, float g, float b);

    ///
    // writes a pixel using the passed in color.  Does not modify the
    // current color
    //
    // @param x - The x coord of the pixel to be set
    // @param y - The y coord of the pixel to be set
    // @param r - The red component of the new color (between 0-1)
    // @param g - The green component of the new color (between 0-1)
    // @param b - The blue component of the new color (between 0-1)
    ///
    void setPixel (int x, int y, float r, float g, float b);

    ///
    // writes a pixel using the current color
    //
    // @param x - The x coord of the pixel to be set
    // @param y - The y coord of the pixel to be set
    ///
    void setPixel (int x, int y);

};


#endif