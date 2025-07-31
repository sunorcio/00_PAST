#version 130




in vec2 vertPosition;



uniform mat4 matProj;
uniform float charOffset; 




void main()
{
	float zoom = 1. / matProj[1][1];
	gl_Position = matProj * vec4(
							 (vertPosition.x*0.09375 - matProj[1][1]/matProj[0][0]+0.109375 + 0.109375*charOffset) * zoom,
							 (vertPosition.y*0.09375 + 0.875) * zoom,
							 -1., 1.
							);
}




