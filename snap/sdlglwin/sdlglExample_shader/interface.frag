#version 130




uniform sampler2D texInterface;
uniform float selected;


in vec2 vfTexCoord;


out vec4 fragColor;




void main()
{
	fragColor =	selected * texture(texInterface,vec2(0.125*vfTexCoord.x+0.125*gl_PointCoord.x,
										  0.25*vfTexCoord.y+0.25*gl_PointCoord.y));
}




