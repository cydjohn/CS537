//
//  Rasterizer.cpp
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  Yudong Cao

#include "Rasterizer.h"
#include "simpleCanvas.h"
#include <float.h>
#include <math.h>

using namespace std;

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n - number of scanlines
//
///

Rasterizer::Rasterizer(int n) : n_scanlines(n)
{
}

/// Quick sort globalEdgeTable based on yMin
void quick_sort(vector<Rasterizer::Bucket> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        Rasterizer::Bucket x = s.at(l);
        while (i < j)
        {
            while(i < j && s.at(j).yMin >= x.yMin)
                j--;
            if(i < j)
                s.at(i++) = s.at(j);
            
            while(i < j && s.at(i).yMin < x.yMin)
                i++;
            if(i < j)
                s.at(j--) = s.at(i);
        }
        s.at(i) = x;
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}

///
// Draw a filled polygon in the simpleCanvas C.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls
// to C.setPixel()
///
void Rasterizer::drawPolygon(int n, int x[], int y[], simpleCanvas &C)
{
    // YOUR IMPLEMENTATION GOES HERE
    int xMax = *max_element(x, x + n); // define the right bound of the polygon
    
    
    /*
     Initializing All of the Edges
     */
    
    // we allocate an Array that will contain all the Buckets of the polygon
    vector<Bucket> globalEdgeTable;
    

    Bucket tempBucket;
    
    // explanation for the use of modulo :
    // If the first and the last bucket have a infinite value for 1/m, no bucket would be stored
    // For that reason, we try to create a bucket with the edge AB where A(x0,y0) and B(xn,yn)
    // We thereby use modulo n so as not be out of bounds, as n has a value > the last index at
    // the end of the loop.
    for (int i = 0; i < n; i++) {
        // let's initialize the current bucket
        tempBucket.yMin = min(y[i % n], y[(i + 1) % n]);
        tempBucket.yMax = max(y[i % n], y[(i + 1) % n]);
        tempBucket.xVal = (float)(tempBucket.yMin == y[i % n] ? x[i % n] : x[(i + 1) % n]);
        tempBucket.inv_m = tempBucket.yMax - tempBucket.yMin != 0 ?
        (float)(x[i % n] - x[(i + 1) % n]) / (float)(y[i % n] - y[(i + 1) % n]) : FLT_MAX;
        // we don't need to store horizontal lines. As we have the
        if (tempBucket.inv_m != FLT_MAX)
            globalEdgeTable.push_back(tempBucket);
    }
    
    // here is the number of buckets we truly keep after having removed the horizontal edges
    n = int(globalEdgeTable.size());
    
    
    /*
     Initializing the Global Edge Table
     */
    //    Sort AEL on x; within groups of same x, sort on 1/m
    quick_sort(globalEdgeTable, 0, n-1);
    
    
    /*
     Initializing parity
     */
    
    
    enum {
        EVEN, ODD
    };
    
    int parity;
    
    
    /*
     Initializing the Scan-Line
     */
    
    int scanLine = globalEdgeTable.at(0).yMin;
    
    
    /*
     Initializing the Active Edge Table
     */
    
    vector<Bucket> activeEdgeTable;
    
    int maxLine = globalEdgeTable.at(n - 1).yMax;
    
    
    for (int line = scanLine; line <= maxLine; line++) {
        parity = EVEN;
        // for each scanLine, we want to retrieve every bucket whose yMin = scanLine
        int i = 0;
        while (i < n) {
            tempBucket = globalEdgeTable.at(i);
            if (tempBucket.yMin == line) {
                // Remove any edges from the global edge table for which the minimum y value
                // is equal to the scan-line and place them in the active edge table
                activeEdgeTable.push_back(tempBucket);
                globalEdgeTable.erase(globalEdgeTable.begin() + i);
                n--;
            }
            else {
                i++;
            }
        }
        
        int nbActiveEdges = int(activeEdgeTable.size());
        int currentEdge = 0;
        
        if (line < maxLine) {
            i = 0;
            
            // Remove any edges from the active edge table for which
            // the maximum y value is equal to the scan_line.
            while (i < nbActiveEdges) {
                tempBucket = activeEdgeTable.at(i);
                if (tempBucket.yMax == line) {
                    activeEdgeTable.erase(activeEdgeTable.begin() + i);
                    nbActiveEdges--;
                }
                else {
                    i++;
                }
            }
        }
        
        // Reorder the edges in the active edge table according to
        // increasing x value. This is done in case edges have crossed
        for (int i = 0; i < nbActiveEdges - 1; i++) {
            for (int j = i + 1; j < nbActiveEdges; j++) {
                if (activeEdgeTable.at(j).xVal < activeEdgeTable.at(i).xVal) {
                    tempBucket = activeEdgeTable.at(j);
                    activeEdgeTable.at(j) = activeEdgeTable.at(i);
                    activeEdgeTable.at(i) = tempBucket;
                }
            }
        }
        
        /*
         Filling the Polygon
         */
        
        for (int scanX = 0; scanX <= xMax && currentEdge < nbActiveEdges; scanX++) {
            if (scanX == round(activeEdgeTable.at(currentEdge).xVal)) {
                // We change parity
                if (currentEdge + 1 < nbActiveEdges && scanX != round(activeEdgeTable.at(currentEdge + 1).xVal)) {
                    parity = (parity == EVEN) ? ODD : EVEN;
                }
                
                // Try every edges. Even when multiple buckets have
                // the same xVal, which is why we use a while loop
                while (currentEdge < nbActiveEdges && scanX == round(activeEdgeTable.at(currentEdge).xVal)) {
                    // Update the x value for for each edge in the active 
                    // edge table using the formula x1 = x0 + 1/m
                    Bucket b = activeEdgeTable.at(currentEdge);
                    Bucket bUpdated = { b.yMin, b.yMax, b.xVal + b.inv_m, b.inv_m };
                    activeEdgeTable.at(currentEdge) = bUpdated;
                    // We need to draw the last pixel of the bucket
                    C.setPixel(scanX, line);
                    currentEdge++;
                }
            }
            // Draw all pixels from the x value of odd to the x value of even parity edge pairs
            if (parity == ODD) {
                C.setPixel(scanX, line);
            }
        }
    }
}
