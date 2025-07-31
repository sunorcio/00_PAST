#version 130




in vec2 vertPosition;
in vec2 vertTexCoord;


out vec2 vfTexCoord;



void main()
{
	vfTexCoord = vertTexCoord;
	gl_Position = vec4(vertPosition.x,vertPosition.y,-1.,1.);
}




