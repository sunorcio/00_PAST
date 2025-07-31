#version 130




uniform mat4 matModl;
uniform mat4 matView;
uniform mat4 matProj;
uniform vec3 instancePos;


in vec3 vertPosition;




void main()
{
	gl_Position = matProj * matView * matModl * vec4(vertPosition*1.0625+instancePos,1.);
}




