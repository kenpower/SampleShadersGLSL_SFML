#version 120

//calculate diffuse lighting
//assume a white light
//don't care about distance

uniform vec3 LightSourcePosition;

void main()
{
	gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;

	

	vec3 normal, lightDir;
	vec4 diffuse;
	float NdotL;
		
	/* first transform the normal into eye space and normalize the result */
	//http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
	//good expalnation of why we transform the normal into eye space
	normal = normalize(gl_NormalMatrix * gl_Normal);
		

	lightDir = normalize(vec3(LightSourcePosition)-vec3(gl_Vertex));
		
	/* compute the cos of the angle between the normal and lights direction. 
	Since these two are normalized the cosine is the dot product. We also 
	need to clamp the result to the [0,1] range. we dont allow negative light values! */
	
	NdotL = max(dot(normal, lightDir), 0.0);
		

		
	gl_FrontColor =  NdotL * gl_Color;

}