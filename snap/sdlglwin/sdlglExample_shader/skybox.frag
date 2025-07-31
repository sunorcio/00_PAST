#version 130




uniform samplerCube texSkybox;


in vec3 vfTexVec;


out vec4 fragColor;




void main()
{
	fragColor = texture(texSkybox,vfTexVec);
}




