//
//  clipper.cpp
//
//  Created by Srinivas Sridharan on 2/17/2017.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  Yudong Cao
//

#include "clipper.h"

///
// Simple class that performs clipping
//
///

///
// Constructor
///

clipper::clipper ()
{
}



bool inside(clipper::Vertices vertices, clipper::Boundary boundary) {
    if (boundary.lly == boundary.ury) {
        //horizontal
        if (boundary.llx<boundary.urx) {
            return vertices.y >= boundary.lly;
        }
        if (boundary.llx>boundary.urx) {
            return vertices.y <= boundary.lly;
        }
        // vertical
    } else {
        if (boundary.ury > boundary.lly) {
            return vertices.x <= boundary.llx;
        }
        if (boundary.ury < boundary.lly) {
            return vertices.x >= boundary.llx;
        }
    }
    return false;
}

void output(clipper::Vertices point,int &length,clipper::Vertices vector[]) {
    vector[length].x = point.x;
    vector[length].y = point.y;
    length++;
}

void intersect(clipper::Vertices spoint,clipper::Vertices epoint,clipper::Boundary boundary,clipper::Vertices &newpoint) {
    if (boundary.llx == boundary.urx) {
        newpoint.x = boundary.llx;
        newpoint.y = spoint.y +(boundary.llx - spoint.x) * (epoint.y - spoint.y) / (epoint.x - spoint.x);
    }
    else {
        newpoint.y = boundary.lly;
        newpoint.x = spoint.x +(boundary.lly - spoint.y) * (epoint.x - spoint.x) / (epoint.y - spoint.y);
    }
}

void SHPC(clipper::Vertices inVertices[],clipper::Vertices outVertices[],int inLength,int &outLength, clipper::Boundary clipboundary) {
    
    outLength = 0;
    
    clipper::Vertices p = inVertices[inLength - 1 ];
    
    
    clipper::Vertices i = p;
    for (int j=0; j<inLength; j++) {
        clipper::Vertices v = inVertices[j];
        if( inside( v, clipboundary ) ) {       // Cases 1 & 4
            if ( inside( p, clipboundary )) {   // Case 1
                output( v ,outLength,outVertices);
            }
            else { // Case 4
                intersect( p, v, clipboundary, i);
                output(i,outLength,outVertices);
                output(v,outLength,outVertices);
            }
        }
        else { // Cases 2 & 3
            if( inside ( p, clipboundary ) ) {  // Case 2
                intersect( p, v, clipboundary, i);
                output(i,outLength,outVertices);
            }  // Case 3 has no output
        }
        p = v;
    } // for
    
}

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

int clipper::clipPolygon(int in, const float inx[], const float iny[],
                         float outx[], float outy[],
                         float llx, float lly, float urx, float ury)
{
    // YOUR IMPLEMENTATION GOES HERE
    int outLength1 = 0, outLength2 = 0, outLength3 = 0, outLength4 = 0;
    
    Vertices *out2, *out3, *out4;
    Vertices inVertices[in];
    Vertices outVertices[in];
    for (int i = 0; i<in; i++) {
        inVertices[i].x = inx[i];
        inVertices[i].y = iny[i];
    }
    
    Boundary clipBoundaryLeft = {llx, ury, llx, lly};
    Boundary clipBoundaryBottom = {llx,lly,urx,lly};
    Boundary clipBoundaryRight = {urx,lly,urx,ury};
    Boundary clipBoundaryTop = {urx,ury,llx,ury};
    
    SHPC(inVertices, outVertices, in, outLength1, clipBoundaryLeft);
    
    out2 = new Vertices[outLength1];
    SHPC(outVertices, out2, outLength1, outLength2, clipBoundaryBottom);
    
    out3 = new Vertices[outLength2];
    SHPC(out2, out3, outLength2, outLength3, clipBoundaryRight);
    
    out4 = new Vertices[outLength3];
    SHPC(out3, out4, outLength3, outLength4, clipBoundaryTop);
    
    for (int i = 0; i<outLength1; i++) {
        outx[i] = out4[i].x;
        outy[i] = out4[i].y;
    }
    
    outLength1 = outLength4;
    
//    free(out2);
//    free(out3);
//    free(out4);
    
    return outLength1;  // should return number of vertices in clipped poly.
    
}
