#version 130




uniform sampler2D texCube;
uniform samplerCube texSkybox;
uniform vec3 viewPos;
uniform int modeColor;
uniform int modeLight;
uniform bool skybox;


in vec3 vfColor;
in vec2 vfTexCoord;
in vec3 vfNormal;
in vec3 vfFragPos;
in vec3 vfLightPos;


out vec4 fragColor;




void main()
{
	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	vec3 lightVec = normalize(vfLightPos-vfFragPos);

	switch(modeLight){
		case 0:
			ambient = 1.;
			diffuse = 0.;
			specular = 0.;
		break;
		case 1:
			ambient = 0.375;
			diffuse = (dot(vfNormal,lightVec) + 1.)/2. * 0.625;
			specular = 0.;
		break;
		case 2:
			ambient = 0.250;
			diffuse = (dot(vfNormal,lightVec) + 1.)/2. * 0.250;
			specular = pow(max( dot( normalize(viewPos-vfFragPos), reflect(-lightVec,vfNormal) ), 0. ),16.) * 0.5;
		break;
	}

	switch(modeColor){
		case 0:
			color = vfNormal+1.25/3.;
		break;
		case 1:
			color = vfColor;
		break;
		case 2:
			color = (texture( texCube,vfTexCoord)).xyz;
		break;
		case 3:
			if(skybox){
				color = texture( texSkybox,reflect(vfFragPos-viewPos,vfNormal) ).xyz*0.875;
			}else{
				color = vec3(0.75,0.5,0.75)*0.875;
			}
		break;
	}
	
	fragColor = vec4( color * (specular+diffuse+ambient), 0.5);
}




