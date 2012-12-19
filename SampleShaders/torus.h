#include "SFML/OpenGL.hpp" 
#include <cmath>

#define U_STEPS 30 // resolution of the mesh
#define V_STEPS 50  // resolution of the mesh

GLint torusNumQuads=U_STEPS*V_STEPS*4;
GLfloat torusVertices[U_STEPS][V_STEPS][3];
GLfloat torusNormals[U_STEPS][V_STEPS][3];
GLuint torusTriangles[U_STEPS*V_STEPS][3];
GLuint torusQuads[U_STEPS*V_STEPS][4];
 

GLuint points[U_STEPS*V_STEPS];

void createTorus(){
	// generate array of points for the torus
 
    const double PI=3.141;
    const double  TWO_PI=PI*2.0, QUARTER_PI=PI/4.0, HALF_PI=PI/2.0;
 
    double R=1.0, r=0.2;
     
    int U,V;
     
    double u,v ;
 
    int t=0;
    int V1,U1;
 
 
    for(U=0; U< U_STEPS;U++){
        for(V=0; V< V_STEPS;V++){
            u=TWO_PI*(double)U/(double)U_STEPS;
            v=TWO_PI*(double)V/(double)V_STEPS;
 
            // compute vertices of a torus
            torusVertices[U][V][0]=(GLfloat)((R+r*cos(u))*cos(v));
            torusVertices[U][V][1]=(GLfloat)(r*sin(u));
            torusVertices[U][V][2]=(GLfloat)((R+r*cos(u))*sin(v));
 
 
            // compute normal for each vertex
            torusNormals[U][V][0]=torusVertices[U][V][0]-(GLfloat)(R*cos(v));
            torusNormals[U][V][1]=torusVertices[U][V][1]-0;
            torusNormals[U][V][2]=torusVertices[U][V][2]-(GLfloat)(R*sin(v));
         
             
            // create a mesh, the quads array contains indices to the vertices array
            // each group of 4 indices specifies a quad.
            V1=(V+1)%V_STEPS;
            U1=(U+1)%U_STEPS;
 
            torusQuads[t][0]=V + U*V_STEPS;
            torusQuads[t][3]=V1 + U*V_STEPS;
            torusQuads[t][2]=V1 + U1*V_STEPS;
            torusQuads[t][1]=V + U1*V_STEPS;
             
            t++;
             
        }
    }

}

