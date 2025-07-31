#version 130




uniform mat4 matView;
uniform mat4 matProj;

uniform vec3 displacement;


in vec3 vertPosition;
in vec3 vertColor;


out vec3 vfColor;




void main()
{
	vfColor = vertColor;
	gl_Position = matProj * matView * vec4(vertPosition+displacement,1.);
}




