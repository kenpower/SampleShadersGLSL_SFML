#version 120

//calculate diffuse lighting
//assume a white light
//don't care about distance



varying vec3 normal, half, lightDir;


void main()
{

	vec4 diffuse;
	float NdotL;

		

	vec3 nlightDir = normalize(lightDir);
	vec3 nnormal=normalize(normal);
		
	/* compute the cos of the angle between the normal and lights direction. 
	Since these two are normalized the cosine is the dot product. We also 
	need to clamp the result to the [0,1] range. we dont allow negative light values! */
	
	NdotL = max(dot(nnormal, nlightDir), 0.0);
		

 
	//calculate specular reflection
	//blinn-phong


	vec3 nhalf=normalize(half);
	
	float HdotN=max(dot(nhalf, nnormal), 0.0);
	
	float spec=pow(HdotN,20);
		
	
	gl_FragColor= min((spec+NdotL),1) * gl_Color;
	//gl_FragColor= gl_Color;
	

}