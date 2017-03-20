//
//  clipper.h
//
//  Created by Srinivas Sridharan on 2/17/2017.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//  
//  Contributor:  Yudong Cao
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "simpleCanvas.h"

///
// Simple class that performs clipping
//
///

class clipper {
public:

    ///
    // Constructor
    ///
    clipper ();

    ///
    // clipPolygon
    //
    // Clip the polygon with vertex count in and vertices inx/iny
    // against the rectangular clipping region specified by lower-left corner
    // (llx,lly) and upper-right corner (urx,ury). The resulting vertices are
    // placed in outx/outy.
    //
    // The routine should return the vertex count of the polygon
    // resulting from the clipping.
    //
    // @param in the number of vertices in the polygon to be clipped
    // @param inx - x coords of vertices of polygon to be clipped.
    // @param iny - y coords of vertices of polygon to be clipped.
    // @param outx - x coords of vertices of polygon resulting after clipping.
    // @param outy - y coords of vertices of polygon resulting after clipping.
    // @param llx - x coord of lower left of clipping rectangle.
    // @param lly - y coord of lower left of clipping rectangle.
    // @param urx - x coord of upper right of clipping rectangle.
    // @param ury - y coord of upper right of clipping rectangle.
    //
    // @return number of vertices in the polygon resulting after clipping
    //
    ///

    int clipPolygon(int in, const float inx[], const float iny[],
                    float outx[], float outy[],
		    float llx, float lly, float urx, float ury);

    struct Vertices {
        float x;
        float y;
    };
    
    struct Boundary {
        float llx;
        float lly;
        float urx;
        float ury;
    };
};

#endif
