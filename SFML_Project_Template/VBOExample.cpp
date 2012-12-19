//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
#pragma comment(lib,"glew32.lib") 

  
#include <GL/glew.h>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
  
  
  
  
//////////////////////////////////////////////////////////// 
/// Entry point of application 
//////////////////////////////////////////////////////////// 
int main() 
{ 
    // Create the main window 
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL"); 
  
	// Create a clock for measuring time elapsed     
	sf::Clock Clock; 
     
	sf::Shader shader;
	if(!shader.loadFromFile("..\\SFML_Project_Template\\vertex.glsl","..\\SFML_Project_Template\\frag.glsl")){
	  std::cout << "Error:\n"<<"loading shaders";
	};

	shader.bind();
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error:\n" << glewGetErrorString(err);
 

	}
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
  
    //// Setup a perspective projection & Camera position 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    
	//set up a 3D Perspective View volume
	//gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar 

	//set up a  orthographic projection same size as window
	//this mease the vertex coordinates are in pixel space
	glOrtho(-2,2,-2,2,0,10); // use pixel coordinates

	#define X 0.52573111f
	#define Z 0.85065080f
 
	GLfloat vertices[][3]={ {-X,0.0,Z},{X,0.0,Z},{-X,0.0,-Z},{X,0.0,-Z},
							{0.0, Z,X},{0.0,Z,-X},{0.0,-Z,X},{0.0,-Z,-X},
							{Z,X,0.0},{-Z,X,0.0 },{Z,-X,0.0 },{-Z,-X,0.0}
	}; // coordinates for vertices an icosahedron
 
 
	GLuint triangles[][3]={ {1,4,0}, {4,9,0},   {4,5,9},   {8,5,4},   {1,8,4},{1,10,8},  {10,3,8},   {8,3,5},   {3,2,5},   {3,7,2},{3,10,7},  {10,6,7},   {6,11,7},  {6,0,11},  {6,1,0}, {10,1,6},  {11,0,9},   {2,11,9},   {5,2,9},   {11,2,7}};
// each triplet of integer, represents a triangle, each integer is an index into the vertex array

	bool VBO=true;
	//VBO=false;
	//glEnableClientState(GL_VERTEX_ARRAY); // we want to use vertex arrays for coordinate info

	if(!VBO){
		glEnableClientState(GL_VERTEX_ARRAY); // we want to use vertex arrays for coordinate info

		glVertexPointer(3,GL_FLOAT,0,(GLvoid*)vertices);	// give openGL our array of vertices
	}else{
		unsigned int vertexBO;
		glGenBuffers( 1, &vertexBO );                  // Get A Valid Name
		glBindBuffer( GL_ARRAY_BUFFER, vertexBO );         // Bind The Buffer
		// Load The Data
		glBufferData( GL_ARRAY_BUFFER, 12*3*sizeof(float), vertices, GL_STATIC_DRAW);
			
		//glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );       // Set The Vertex Pointer To The Vertex 
		glEnableVertexAttribArray(0);                                               //ENABLE VERTEX POSITION
	    glVertexAttribPointer(  //describe the format of the data in the buffer
				0,//index of the attribute
				3, //num of values per vertex (num coordinates)
				GL_FLOAT, //type of coord
				GL_FALSE, //should they be normalized?
				0,//stride
				0);    //offset to first attribute in array

		// create index buffer
		unsigned int indexBO;
		glGenBuffers( 1, &indexBO );                  // Get A Valid Name
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBO );         // Bind The Buffer
		// Load The Data
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*20*3, triangles, GL_STATIC_DRAW);

	}
    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
  
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
            
   
        } 
          
		if(!App.isOpen()){
			continue;
		}
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  
        // Apply some transformations 
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
		
		double angle=Clock.getElapsedTime().asMilliseconds();
		glTranslated(0,0,-5); //shift to original position
		glRotated(angle/10, 1, 1, 1); // rotate
		
		
       glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          
	   if(VBO){
			glDrawElements(GL_TRIANGLES, 20*3, GL_UNSIGNED_INT,0);
			
	   }
	   else
			 glDrawElements(GL_TRIANGLES, 20*3, GL_UNSIGNED_INT,triangles);
	
  
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
  
    return EXIT_SUCCESS; 
} 