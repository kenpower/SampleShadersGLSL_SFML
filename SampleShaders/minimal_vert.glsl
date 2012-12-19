#version 120

//layout(location = 0) in vec4 position;
void main()
{
    gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;

}