#version 130




uniform mat4 matView;
uniform mat4 matProj;


in vec3 vertPosition;


out vec3 vfPosition;




void main()
{
	float zoom = 1. / matProj[1][1];
	vec4 position = matProj * matView * vec4(vertPosition *0.09375 * zoom,1.);

	vfPosition = vertPosition;
	gl_Position = vec4(	
					 position.x + 0.75,
					 position.y + 0.75,
					 position.z,
					 position.w
					);
}




