#version 130




uniform mat4 matModl;
uniform mat4 matView;
uniform mat4 matProj;
uniform vec3 lightPos;
uniform vec3 instancePos;


in vec3 vertPosition;
in vec3 vertColor;
in vec2 vertTexCoord;
in vec3 vertNormal;


out vec3 vfColor;
out vec2 vfTexCoord;
out vec3 vfNormal;
out vec3 vfFragPos;
out vec3 vfLightPos;




void main()
{
	vfColor = vertColor;
	vfTexCoord = vertTexCoord;
	vfNormal = (matModl * vec4(vertNormal,0.)).xyz;
	vfFragPos = (matModl * vec4(vertPosition+instancePos,1.)).xyz;
	vfLightPos = (matModl * vec4(lightPos,1.)).xyz;

	gl_Position = matProj * matView * matModl * vec4(vertPosition+instancePos,1.);
}




