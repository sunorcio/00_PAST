#version 130




in vec3 vfPosition;


out vec4 fragColor;




void main()
{
	fragColor = vec4(vfPosition,1.);
}




