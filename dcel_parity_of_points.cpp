#include "cpp_as3_header.hpp"

int main()
{
    vector<class vertex*> vertex_list;    
    ifstream fin;

    fin.open("Domjudge_std_input.txt");
    
    while(!fin.eof())
    {

        double x1, y1;
        fin >> x1 >> y1;
        class vertex *input_vertex = new vertex(x1, y1, int(vertex_list.size()));
        
        vertex_list.push_back(input_vertex);
    }

    fin.close();
    
    vector< class halfedge* > half_edge_list;
    
    vector< class face* > face_list;
    face_list.push_back(new face(0));
    
    for(int i = 0; i<4; i++)
    {	
        class halfedge *temp1;
        
        temp1 = new halfedge(vertex_list[i%4],vertex_list[(i+1)%4],face_list[0], int(half_edge_list.size()));//connecting all the vertices
        half_edge_list.push_back(temp1);
            
        if(i>0)
        {
            half_edge_list[i]->prev_edge = half_edge_list[i-1];//connecting edges 1->0,2->1,3->2
            half_edge_list[i-1]->next_edge = half_edge_list[i];//connecting 0->1, 1->2, 2->3
        }
    }
    
    
    half_edge_list[0]->prev_edge = half_edge_list[3];//connecting edge 0->3
    half_edge_list[3]->next_edge = half_edge_list[0];//connecting edge 3->0
    
    face_list[0]->head = half_edge_list[0];
    face_list[0]->tail = half_edge_list[0]->prev_edge;
    
    //output of the program
    ofstream fout;
    fout.open("sample.txt");
    
    fout << "Before split:" << endl;
    fout << endl;
    
    fout << "Edges:" << endl;
    
    for(int i = 0; i<4; i++ )
    {
        fout << half_edge_list[i]->ind << endl;
    }
    
    fout << "Halfedges:" << endl;
    	
    for(int i = 0; i<4; i++)
    {
        fout << "startVertexIndex=" << half_edge_list[i]->start_vertex->index << " ";
        fout << "endVertexIndex=" << half_edge_list[i]->end_vertex->index << " ";
        fout << "nextEdge=" << half_edge_list[i]->next_edge->ind << " ";
        fout << "previousEdge=" << half_edge_list[i]->prev_edge->ind << " ";
        fout << "faceIndex=" << half_edge_list[i]->incident_face->id << " ";
        fout << "edgeIndex=" << half_edge_list[i]->ind << endl;
    }
    
    fout << "Faces:" << endl;
    fout << "FaceIndex:" << half_edge_list[0]->incident_face->id << " " << endl;
    
    fout << "Edges:";
    
    class halfedge *temp_head1 = face_list[0]->head;
        
    do
    {
        fout << temp_head1->ind << "->";
        temp_head1 = temp_head1->next_edge;
    }
    while(temp_head1!=face_list[0]->tail);
    fout << temp_head1->ind << endl;
    
    //____________________________________________________// 
    cout << "1!!!!" << endl; 
    
    fin.open("split.txt");

    string s1;

    fin >> s1;
       
    while(s1=="Split:")
    {
        int edgeid1;        
        int edgeid2;
        fin >> edgeid1 >> edgeid2;
                
        //First find the common halfedges of the given edges belonging to a single face 
        
        class halfedge *temp_hedge1 = half_edge_list[edgeid1];//select the halfedges with edgeid1
        class halfedge *temp_hedge2 = half_edge_list[edgeid2];//select the halfedges with edgeid2
        
        
        bool k, m;
        if(temp_hedge1->twin)
            k=true;
        else
            k=false;
            
        if(temp_hedge2->twin)
            m=true;
        else
            m=false;
        cout << "2!!!!" << endl;
        
            
        //now we are finding the common halfedges of the face
        
        if((temp_hedge1->incident_face->id) == (temp_hedge2->incident_face->id));//1, 2
        else if(k && (temp_hedge1->twin->incident_face->id) == (temp_hedge2->incident_face->id))//twin1, 2
            temp_hedge1 = temp_hedge1->twin;
        else if(m && (temp_hedge2->twin->incident_face->id) == (temp_hedge1->incident_face->id))//1, twin2
            temp_hedge2 = temp_hedge2->twin;
        else//twin1, twin2
        {
            temp_hedge1 = temp_hedge1->twin;
            temp_hedge2 = temp_hedge2->twin;
        }
	cout << "3!!!!" << endl;
            
        //____________________________________________________//
    
        //Now we will calculate the new vertices, i.e. the mid points of the given edges
        
        class vertex *temp_vert1;
        double a1 = (temp_hedge1->start_vertex->a + temp_hedge1->end_vertex->a)/2;
        double b1 = (temp_hedge1->start_vertex->b + temp_hedge1->end_vertex->b)/2;
        
        temp_vert1 = new vertex(a1, b1, int(vertex_list.size()));//pushing the new vertex to the vertex list and assigning the vertex values and index.
        vertex_list.push_back(temp_vert1);
        //we pass index by passing the size of the vertex_list after pushung the new vertex into it.
        
        class vertex *temp_vert1_initial = temp_hedge1->end_vertex;//store end vertex of halfedge 1     
        
        class vertex *temp_vert2;
    
        double a2 = (temp_hedge2->start_vertex->a + temp_hedge2->end_vertex->a)/2;
        double b2 = (temp_hedge2->start_vertex->b + temp_hedge2->end_vertex->b)/2;
        
        
        temp_vert2 = new vertex(a2, b2, int(vertex_list.size()));//pushing the new vertex to the vertex list and assigning the vertex values and index.
        vertex_list.push_back(temp_vert2);
        //we pass index by passing the size of the vertex_list after pushung the new vertex into it.
        
        class vertex *temp_vert2_initial = temp_hedge2->start_vertex;//store start vertex of halfedge 2

	cout << "4!!!!" << endl;
        
        //____________________________________________________//
        
        //shrinking the edges
        
        temp_hedge1->end_vertex = temp_vert1;
        temp_hedge2->start_vertex = temp_vert2;
        
        if(k)//if twin of 1st halfedge exists
            temp_hedge1->twin->start_vertex = temp_vert1;
        if(m)//if twin of 2nd halfedge exists   
            temp_hedge2->twin->end_vertex = temp_vert2;

	cout << "5!!!!" << endl;
    
        //____________________________________________________//
    
        //link creation i.e. form 3 new edges.
        //create twin of the link for sure.
        //create twins of the other two halfedges if twins of original edges existed.
        
        class halfedge *link =  new halfedge(temp_vert1, temp_vert2, temp_hedge2->incident_face, int(half_edge_list.size()));//make the new linking edge
        half_edge_list.push_back(link);


        class halfedge *temp_hedge1_next = temp_hedge1->next_edge;
        class halfedge *temp_hedge2_prev = temp_hedge2->prev_edge;
        //pointer changes for all the edges 
        link->prev_edge = temp_hedge1;
        link->next_edge = temp_hedge2;
        temp_hedge1->next_edge = link;
        temp_hedge2->prev_edge = link;

	cout << "6!!!!" << endl;
    

        class halfedge *hedge1, *hedge2, *link_twin;
        class face *new_face;
        
        new_face = new face(int(face_list.size()));
        face_list.push_back(new_face);
        
        link_twin = new halfedge(temp_vert2, temp_vert1, new_face, int(half_edge_list.size()-1));//do not add the link twin to the halfedge list
        link_twin->twin = link;
        link->twin = link_twin;
        
        hedge1 = new halfedge(temp_vert1, temp_vert1_initial, new_face, int(half_edge_list.size()));
        half_edge_list.push_back(hedge1);        
        
        hedge2 = new halfedge(temp_vert2_initial, temp_vert2, new_face, int(half_edge_list.size()));
        half_edge_list.push_back(hedge2);
        
        link_twin->next_edge = hedge1;//connecting the link twin to the newly created edges
        hedge1->prev_edge = link_twin;
        link_twin->prev_edge = hedge2;
        hedge2->next_edge = link_twin; 

	cout << "7!!!!" << endl;
        
        
        if(temp_vert1_initial == temp_vert2_initial)//if both the original edges originate from the same vertex
        {
            hedge1->next_edge = hedge2;
            hedge2->prev_edge = hedge1;
        }
        else//if both the initial edges originate from different vertices
        {
            hedge1->next_edge = temp_hedge1_next;
            temp_hedge1_next->prev_edge = hedge1;
            hedge2->prev_edge = temp_hedge2_prev;
            temp_hedge2_prev->next_edge = hedge2;
                    
        }


	cout << "8!!!!" << endl;

        temp_hedge1->incident_face->tail = temp_hedge1;
        temp_hedge1->incident_face->head = link;//change the head pointer of the initial face
        
        new_face->head = link_twin;
        new_face->tail = link_twin->prev_edge;       
        
        //assigning the new face to the newly created edges and the edges in b/w hedge1 and hedge2.
        class halfedge *temp;
        temp = new_face->head;
        do
        {
            temp->incident_face = new_face;
            temp = temp->next_edge;
        }
        while(temp != new_face->head);


	cout << "9!!!!" << endl;
        
        if(k)//if twin for the first halfedge to be split is present
        {
            class halfedge *hedge1_twin = new halfedge(temp_vert1, temp_vert1_initial, temp_hedge1->twin->incident_face, int(half_edge_list.size()-1));
            hedge1_twin->twin = hedge1;
            hedge1->twin = hedge1_twin;
            hedge1_twin->prev_edge = temp_hedge1->twin->prev_edge;
            
            temp_hedge1->twin->prev_edge->next_edge = hedge1_twin;
            hedge1_twin->next_edge = temp_hedge1->twin;
            temp_hedge1->twin->prev_edge = hedge1_twin;
                    
        }
        
        if(m)//if twin for the second halfedge to be split is present
        {
        
            class halfedge *hedge2_twin = new halfedge(temp_vert2, temp_vert2_initial, temp_hedge2->twin->incident_face, int(half_edge_list.size()-1));
            hedge2_twin->twin = hedge2;
            hedge2->twin = hedge2_twin;
            hedge2_twin->prev_edge = temp_hedge2->twin;
            hedge2_twin->next_edge = temp_hedge2->twin->next_edge;
            temp_hedge2->twin->next_edge->prev_edge = hedge2_twin;
            temp_hedge2->twin->next_edge = hedge2_twin;
                        
        }


	cout << "10!!!!" << endl;

        //printing the splits
        fout << endl;
        fout << "____________________________________________________________________________________________________________" << endl;
        fout << "After Split:" << endl;
        
        fout << endl;
        fout << "Edges:" << endl;
        
        for(int i = 0; i<int(half_edge_list.size()); i++ )
        {
            fout << i << endl;
        }

	cout << "11!!!!" << endl;
        
        
        fout << "Halfedges:" << endl;
        
        for(int i = 0; i<int(half_edge_list.size()); i++)
        {
            fout << "startVertexIndex=" << half_edge_list[i]->start_vertex->index << " ";	
            fout << "endVertexIndex=" << half_edge_list[i]->end_vertex->index << " ";			
            fout << "nextEdge=" << half_edge_list[i]->next_edge->ind << " ";	
            fout << "previousEdge=" << half_edge_list[i]->prev_edge->ind << " ";	
            fout << "faceIndex=" << half_edge_list[i]->incident_face->id << " ";	
            fout << "edgeIndex=" << half_edge_list[i]->ind << endl;
        
            if(half_edge_list[i]->twin)
            {
                fout << "startVertexIndex=" << half_edge_list[i]->twin->start_vertex->index << " ";	
                fout << "endVertexIndex=" << half_edge_list[i]->twin->end_vertex->index << " ";			
                fout << "nextEdge=" << half_edge_list[i]->twin->next_edge->ind << " ";	
                fout << "previousEdge=" << half_edge_list[i]->twin->prev_edge->ind << " ";
                fout << "faceIndex=" << half_edge_list[i]->twin->incident_face->id << " ";	
                fout << "edgeIndex=" << half_edge_list[i]->twin->ind << endl;	
            }
        
        }
        fout << "Faces:" << endl;
        
        for(int i = 0; i<int(face_list.size()); i++)
        {        
            fout << "FaceIndex:" << face_list[i]->id << " ";	
            fout << "Edges:";
            class halfedge *temp_head = face_list[i]->head;
        
            do
            {
                fout << temp_head->ind << "->";
            
                temp_head = temp_head->next_edge;
            
            }
            while(temp_head!=face_list[i]->tail);
            fout << temp_head->ind << "\n";
        }
        
        fin >> s1;  
    }

    //Assignment 3 start
    for(int i = 0; i<int(face_list.size()); i++)//calculate the centroid of all the faces, then check the parity of the centroid wrt to each halfedge of the face (for each face)
    {   
        face_list[i]->calculate_centroid();
        class halfedge *temp = face_list[i]->head;
        do
        {
            temp->parity_check_centroid();
            temp = temp->next_edge;
        }
        while(temp != face_list[i]->head);
    }
   
    vector <class vertex*> input_points;//store all the given points to be placed in the faces of the geometric figure
    vector <class face*> face_of_ip_pt;//stores the face to which the input point belongs to. The 0th position will have the face corresponding to the first input point
         
    while(!fin.eof())
    {
        int given_id;
	    double x, y;
        fin >> given_id >> x >> y;
        class vertex *input_vertex = new vertex(x, y, given_id);//given_id starts from 1 but it is stored in the vector at the 0th position i.e. given_id+1
            
        input_points.push_back(input_vertex);
        fin >> s1;
    }
    fin.close();

    for(int i = 0; i<int(input_points.size()); i++)
    {
        for(int j = 0; j<int(face_list.size()); j++)
        {
            double q = input_points[i]->a;
            double r = input_points[i]->b;
            double point_parity;
            bool correct_face = true;

            class halfedge *temp = face_list[j]->head;

            do
            {
                double a_ = temp->eqn_halfedge->a;
                double b_ = temp->eqn_halfedge->b;
                double c_ = temp->eqn_halfedge->c;

                if(((a_*q) + (b_*r) - (c_)) > 0)//a_*c + b_*d - c_ > 0
                    point_parity = 1;

                else if(((a_*q) + (b_*r) - (c_)) == 0)//a_*c + b_*d - c_ = 0
                    point_parity = 0;    

                else //a_*c + b_*d - c_ < 0
                    point_parity = -1;

                if(point_parity != temp->parity_centroid)
                    correct_face = false;       
                
                temp = temp->next_edge;

            }

            while(temp != face_list[j]->head);

            if(correct_face)
            {
                face_of_ip_pt.push_back(face_list[j]);
            }
        }
    }

    fout << "Input_points' outputs" << endl;
    for(int i = 0; i<int(face_of_ip_pt.size()); i++)
    {
        fout << "Id: " << input_points[i]->index << " " ;
        fout << face_of_ip_pt[i]->id << endl;
    }

    return 0;
      
}

/*void printk(struct face sq);*/
