#version 130




in vec3 vertPosition;
in vec3 vertColor;


out vec3 vfColor;


uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProj;
uniform vec3 position;




void main(){

/* 	vfColor = vertColor; */
	vfColor = pow(vec3(vertPosition.x+position.x,
					(vertPosition.y+position.y)*sqrt(2)/(2.*cos(asin(0.5))),
					vertPosition.z+position.z)/16,
					vec3(1,1,1));


	gl_Position = matProj * matView * matModel *
				vec4(vertPosition.x+position.x,
					(vertPosition.y+position.y)*sqrt(2)/(2.*cos(asin(0.5))),
					vertPosition.z+position.z,
					1.);
}




