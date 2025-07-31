#version 130




out vec4 fragColor;


uniform vec3 fontCol;




void main()
{
	fragColor = vec4(fontCol,1.);
}




