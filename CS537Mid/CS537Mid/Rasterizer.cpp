//
//  Rasterizer.cpp
//
//  Created by Srinivas Sridharan on 2/10/17.
//  Copyright 2017 Stevens Institute of Technology. All rights reserved.
//
//  Contributor:  Yudong Cao
//

#include "Rasterizer.h"
#include "simpleCanvas.h"

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

Rasterizer::Rasterizer (int n) : n_scanlines (n)
{
}

struct Bucket {
    int yMax;
    float x;
    int dy;
    int dx;
    int sum;
    int yMin;
};



/// Quick sort edgeTable based on yMin
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
    Bucket tempBucket;
    for (int i = 0; i < n; i++) {
        tempBucket.yMin = min(y[i], y[(i + 1) % n]);
        tempBucket.yMax = max(y[i], y[(i + 1) % n]);
        tempBucket.x = (float)(tempBucket.yMin == y[i] ? x[i] : x[(i + 1) % n]);
        tempBucket.dx = x[i]-x[(i+1)%n];
        tempBucket.dy = y[i]-y[(i+1)%n];
        tempBucket.sum = 0;
        if (tempBucket.dy != 0)
            edgeTable.push_back(tempBucket);
    }
    return edgeTable;
}



vector<Bucket> processEdgeTable(vector<Bucket> edgeTable,simpleCanvas &C) {
    
    int currentScanLine = edgeTable.at(0).yMin;
    
    vector<Bucket> activeTable;

    int maxLine = edgeTable.at(edgeTable.size() - 1).yMax;
    int xMax ;
    
    
    for (int i = currentScanLine; i < maxLine; i++) {
        //    // Add edge from edge table to active list if y == ymin
        //    for (iterate through the bucket in the edge table) {
        //        if (bucket's ymin == scanline) {
        //            add bucket to active list
        //            }
        //            }
        
        for (int j = 0; j<edgeTable.size();j++ ) {
            xMax = xMax>edgeTable.at(j).x?xMax:edgeTable.at(j).x;
            if (edgeTable.at(j).yMin == i) {
                activeTable.push_back(edgeTable.at(j));
                edgeTable.erase(edgeTable.begin() + j);
                j--;
            }
        }
        
        
        //        // Remove edges from the active list if y == ymax
        //        if (active list is NOT empty) {
        //            for (iterate through all buckets in the active list) {
        //                if (current bucket's ymax == current scanline) {
        //                    remove bucket from active list
        //                    remove bucket from edge table
        //                    }
        //                    }
        //                    }
        for (int j = 0; j< activeTable.size(); j++) {
            if (activeTable.at(j).yMax == i) {
                activeTable.erase(activeTable.begin() + j);
                j--;
            }
        }

//     Sort active list by x position
        sortActiveList(activeTable);
        
        
//     Fill the polygon pixel

        
        int currentEdge = 0;
        for (int scanX = 0; scanX <= xMax && currentEdge < activeTable.size(); scanX++) {
            if (scanX == int(activeTable.at(currentEdge).x + 0.5)) {
                if (currentEdge + 1 < activeTable.size() && scanX != int(activeTable.at(currentEdge + 1).x + 0.5)) {
                    for (int i = currentEdge+1; i < activeTable.size(); i++) {
                        activeTable.at(i).sum+=1;
                    }
                }
                
                while (currentEdge < activeTable.size() && scanX == int(activeTable.at(currentEdge).x + 0.5)) {
                    
                    Bucket b = activeTable.at(currentEdge);
                    //                  If the edge's slope is vertical
                    if (b.dy != 0) {
                        b.x = b.x + float(b.dx)/float(b.dy);
                    }
                    else {
                        //vertical slope
                        b.x = 1000000.0;
                    }
                    activeTable.at(currentEdge) = b;
                    C.setPixel(scanX, i);
                    currentEdge++;
                }
            }
            if ((currentEdge<activeTable.size()&&activeTable.at(currentEdge).sum)) {
                C.setPixel(scanX, i);
            }
            
        }
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
    vector<Bucket> ET = createEdges(n, x, y);
    
    quickSortET(ET, 0, int(ET.size()-1));
    
    processEdgeTable(ET, C);
}
