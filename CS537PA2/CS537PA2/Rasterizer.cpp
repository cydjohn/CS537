//
//  Rasterizer.cpp
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include "Rasterizer.h"
#include "simpleCanvas.h"

using namespace std;

struct Bucket {
    int yMax;
    int x;
    int dy;
    int dx;
    int sum;
    int yMin;
} bucket;



/// Quick sort globalEdgeTable based on yMin
void quickSortET(vector<Bucket> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        Bucket x = s.at(l);
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
        quickSortET(s, l, i - 1);
        quickSortET(s, i + 1, r);
    }
}

void sortActiveList(vector<Bucket> &activeEdgeTable) {
    Bucket temp;
    for (int i = 0; i < activeEdgeTable.size(); i++) {
        for (int j = i + 1; j < activeEdgeTable.size(); j++) {
            if (activeEdgeTable.at(j).x < activeEdgeTable.at(i).x) {
                temp = activeEdgeTable.at(j);
                activeEdgeTable.at(j) = activeEdgeTable.at(i);
                activeEdgeTable.at(i) = temp;
            }
        }
    }
}



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

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}


//follow the instruction of https://hackernoon.com/computer-graphics-scan-line-polygon-fill-algorithm-3cb47283df6#.ov2fykf5z

//createEdges(n, x[], y[]) {
//    instantiate a new edge table
//    loop through x[] & y[] pairs {
//        if the edge's slope is NOT undefined (verticle) {
//            create bucket with edge
//            add bucket to edge table
//            }
//}
//}
vector<Bucket> createEdges(int n,int x[],int y[]) {
    vector<Bucket> edgeTable;
    for (int i = 0; i< n; i++) {
        if (x[i]-x[(i+1)%n] != 0) {
            Bucket tempBucket;
            tempBucket.dx = x[i]-x[(i+1)%n];
            tempBucket.dy = y[i]-y[(i+1)%n];
            tempBucket.sum = 0;
            tempBucket.yMax = y[i+1]<y[i]?y[i]:y[(i+1)%n];
            tempBucket.yMin = y[i+1]<y[i]?y[(i+1)%n]:y[i];
            tempBucket.x = y[i+1]<y[i]?x[i]:x[(i+1)%n];
            edgeTable.push_back(tempBucket);
        }
    }
    return edgeTable;
}




vector<Bucket> processEdgeTable(vector<Bucket> edgeTable,simpleCanvas &C,int xMAX) {
    
    
    vector<Bucket> activeTable;
    Bucket currentBucket = edgeTable.at(0);
    int currentScanLine = edgeTable.at(0).yMin;
    //        // Remove edges from the active list if y == ymax
    //        if (active list is NOT empty) {
    //            for (iterate through all buckets in the active list) {
    //                if (current bucket's ymax == current scanline) {
    //                    remove bucket from active list
    //                    remove bucket from edge table
    //                    }
    //                    }
    //                    }
    for (int i = 0; i < edgeTable.size(); i ++) {
        
        
        if (activeTable.size() != 0) {
            for (int j = 0; j< activeTable.size(); j++) {
                if (currentBucket.yMax == currentScanLine) {
                    activeTable.erase(activeTable.begin() + j);
                    edgeTable.erase(edgeTable.begin()+j);
                }
            }
        }
        
        
        
        //    // Add edge from edge table to active list if y == ymin
        //    for (iterate through the bucket in the edge table) {
        //        if (bucket's ymin == scanline) {
        //            add bucket to active list
        //            }
        //            }
        
        for (int i = 0; i<edgeTable.size(); i++) {
            if (edgeTable.at(i).yMin == currentScanLine) {
                activeTable.push_back(edgeTable.at(i));
            }
        }
        
        //     Sort active list by x position and slope
        sortActiveList(activeTable);
        
        
        //    // Fill the polygon pixel
        //    for (iterate through the active list) {
        //        for (from vertex1.x to vertex2.x of the bucket) {
        //            setPixelColor()
        //        }
        //    }
        int currentEdge = 0;
        int parity = 0;
        int maxLine = edgeTable.at(edgeTable.size() - 1).yMax;
        
        
        for (int line = currentScanLine; line <= maxLine; line++) {
        for (int i = 0; i<xMAX; i++) {
            //        if (i == int(activeTable.at(currentEdge).x)) {
                        if (currentEdge + 1 < activeTable.size() && i != int(activeTable.at(currentEdge+1).x)) {
                            if (parity == 1) {
                                parity = 0;
                            }
                            else{
                                parity = 1;
                            }
                        }
                    while (currentEdge < activeTable.size() ){//&& i == int(activeTable.at(currentEdge).x)) {
                            Bucket temp = activeTable.at(currentEdge);
                            if (temp.dy != 0) {
                                temp.x = temp.x + temp.dx/temp.dy;
                            }
                            activeTable.at(currentEdge) = temp;
                            C.setPixel(i, line);
                            currentEdge ++;
                        }
            //        }
                    if (parity == 0) {
                        C.setPixel(i, line);
                    }
            //
            
            
        }
        }
        
        
        //    // Increment X variables of buckets based on the slope
        //    for (all buckets in the active list) {
        //        if (bucketsdX != 0) {
        //            bucket's sum += bucket's dX
        //            while (bucket's sum >= bucket's dY) {
        //                increment or decrement bucket's X depending on sign of bucket's slope
        //                edge's sum -= dY
        //            }
        //        }
        //    }
        
    }
    
    
    
    return edgeTable;
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
    int xMax = *max_element(x, x + n);
    vector<Bucket> ET = createEdges(n, x, y);
    
    quickSortET(ET, 0, int(ET.size()-1));
    
    processEdgeTable(ET, C,xMax);
    
}
