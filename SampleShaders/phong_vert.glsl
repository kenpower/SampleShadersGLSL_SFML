#version 120

//calculate diffuse lighting
//assume a white light
//don't care about distance

uniform vec3 LightSourcePosition;
uniform vec3 EyePosition;

varying vec3 normal, half, lightDir;
varying vec4 vcsPosition;

void main()
{
	gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*gl_Vertex;
	gl_FrontColor =  gl_Color;

	normal = normalize(gl_NormalMatrix * gl_Normal);

	//calc position in VCS
	vcsPosition=gl_ModelViewMatrix * gl_Vertex;

	lightDir = normalize(vec3(LightSourcePosition)-vec3(vcsPosition));
	
		

 
	vec3 eyeDir = normalize(vec3(EyePosition)-vec3(vcsPosition));

	half=normalize(lightDir+eyeDir);

}