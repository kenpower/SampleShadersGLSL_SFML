#version 120

uniform sampler2D tex;

//get texture
void main()
{
	vec4 c=texture2D(tex,gl_TexCoord[0].st);
	gl_FragColor=gl_Color*c;
}