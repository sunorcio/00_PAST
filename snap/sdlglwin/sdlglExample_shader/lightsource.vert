#version 130




uniform mat4 matModl;
uniform mat4 matView;
uniform mat4 matProj;
uniform vec3 lightPos;




void main()
{
	gl_Position = (matProj * matView * matModl * vec4(lightPos,1.)).xyzw;
	//gl_PointSize = 100.;
}




