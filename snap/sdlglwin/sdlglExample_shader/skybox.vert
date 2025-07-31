#version 130





uniform mat4 matView;
uniform mat4 matProj;


in vec3 vertPosition;


out vec3 vfTexVec;




void main()
{
	float aspectRatio = matProj[1][1]/matProj[0][0];
	float orthoDiagonal = sqrt(aspectRatio*aspectRatio+1);
	float zoom = 1. / matProj[1][1];

	mat4 skyView = matView;
	skyView[3][0] = 0.;
	skyView[3][1] = 0.;
	skyView[3][2] = 0.;

	gl_Position = (matProj * skyView * vec4(vertPosition*2.* orthoDiagonal * zoom, 1.)).xyww;
	vfTexVec = vertPosition;
}




