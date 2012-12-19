#version 120


void main()
{
	
    gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;

	vec4 v=normalize(gl_Vertex);

	gl_FrontColor.rgb=v.xyz;

}