#version 120

//use the vertex colour as provided by OpenGL 

void main()
{
	
    gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;

	gl_FrontColor=gl_Color;

	gl_TexCoord[0]=gl_MultiTexCoord0;

}