# Dynamic-DCEL-in-cpp
Used Object Oriented Programming and concept of Pointers to build dynamic DCEL which splits a square shape initially into different shapes as per given input points to represent a 3-D shape and outputs the position of different set of input points in it. Can be used in 3-D Game Development.


My program accepts inputs of splits of the form:
* Split: 2 3
* Split: 1 4

* Id: 1 2 5
* Id: 2 3 6

All my halfedges, vertices and faces are stored in separate vectors.

My program outputs halfedges in a clockwise order. 
It outputs halfedges once before the split and every time after a split has been implemented in the geometric figure, i.e. :
* Before split :

* After split :



The equation of line that I have used is : (y-y1)/(x-x1) = (y2-y1)/(x2-x1)
So, 
	a = y1-y2;
        b = x2-x1;       
        c = (x2-x1)*y1 - (y2-y1)*x1;

So, if the parity of the point w.r.t the halfedge is the same as that of the centroid, and the same is true for all the halfedges of a particular face, then the given input point is inside that face.


All the points with their ids and their corresponding faces are printed at the end.


