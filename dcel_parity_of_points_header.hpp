#include<bits/stdc++.h>
using namespace std;

class face;
class eqn;
class halfedge;


class vertex
{
    public:
        double a, b;//vertex coordinates
        int index;
   //struct halfedge *incident_edge;
        vertex(double x, double y, int id)
        {
            a=x;
            b=y;
            index=id;
        }

};


class eqn
{
    public:
        double a, b, c;//ax+by = c -> equation of line

        eqn(double x1, double y1, double x2, double y2)//taking the equation of line in slope form: (y-y1)/(x-x1) = (y2-y1)/(x2-x1)
        {
            a = y1-y2;
            b = x2-x1;       
            c = (x2-x1)*y1 - (y2-y1)*x1;
	    
        }    
};


class halfedge
{
	public:
        class vertex *start_vertex;
        class vertex *end_vertex;
        class halfedge *twin;
        class face *incident_face;
        class halfedge *prev_edge;
        class halfedge *next_edge;
        class eqn *eqn_halfedge;
        int ind;//the index of the halfedge would be the index of its start_vertex
        int parity_centroid;

        //declaring the functions and constructors

        halfedge(class vertex *start_vertexp, class vertex *end_vertexp,class face *incident_facep, int indp);
        int parity_check_centroid();
        
};

//we add a half edge to the face struct because each half edge belongs to a face
class face
{
    public:
        int id;
        class halfedge *tail;//tail
        class halfedge *head;//head
        
        double cx1, cy1;//coordinates of the centroid of the face
        
        face(int idp)
        {
            tail = NULL;
            head = NULL;
            id = idp;
        } 

        void calculate_centroid();       
};


halfedge::halfedge(class vertex *start_vertexp, class vertex *end_vertexp,class face *incident_facep, int indp)
{
    start_vertex=start_vertexp;
    end_vertex=end_vertexp;
    incident_face=incident_facep;
    twin=NULL;
    ind = indp; 
    eqn_halfedge = new eqn(start_vertex->a, start_vertex->b, end_vertex->a, end_vertex->b); 
                
}

int halfedge::parity_check_centroid()//we are checking the parity of the centroid of the face of the halfedge wrt the halfedge
{
    double cx = incident_face->cx1;
    double cy = incident_face->cy1;

    if(((eqn_halfedge->a*cx) + (eqn_halfedge->b*cy) - (eqn_halfedge->c)) > 0)//a*cx + b*cy - c > 0
        parity_centroid = 1;

    else if(((eqn_halfedge->a*cx) + (eqn_halfedge->b*cy) - (eqn_halfedge->c)) == 0)//a*cx + b*cy - c = 0
        parity_centroid = 0;    

    else //a*cx + b*cy - c < 0
        parity_centroid = -1;  
    
    
    return parity_centroid;      
}   

void face::calculate_centroid()
{
    class halfedge *temp = head;
    double c_x1 = 0;
    double c_y1 = 0;
    int count = 0;
    
    do 
    {
        class vertex *m = temp->end_vertex;        
        c_x1 = (c_x1+m->a);
        c_y1 = (c_y1+m->b);

        temp = temp->next_edge;
        count++;
    }
    while(temp != head);

    cx1 = c_x1/count;//coordinates of the centroid of the face
    cy1 = c_y1/count;

    
}
