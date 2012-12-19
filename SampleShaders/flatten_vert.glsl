#version 120


void main()
{
	vec4 v=gl_Vertex;
	v.z=0;

    gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*v;

}