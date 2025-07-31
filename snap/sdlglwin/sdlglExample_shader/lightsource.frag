#version 130




out vec4 fragColor;




void main()
{
	float lightCol = 1 - length(gl_PointCoord-vec2(0.5,0.5));
	if(lightCol<0.8){discard;}
	fragColor = vec4(lightCol,lightCol,lightCol,lightCol*0.5);
}





