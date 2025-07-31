#version 130




uniform mat4 matView;
uniform mat4 matProj;


in vec3 vertPosition;
in vec3 vertColor;


out vec3 vfColor;


uniform vec3 position;




void main()
{
	vfColor = vertColor;
	gl_Position = matProj * matView * vec4(vertPosition.x + position.x,
					vertPosition.y*sqrt(2)/(2.*cos(asin(0.5))) + position.y,
					vertPosition.z + position.z,
					1.);
}




