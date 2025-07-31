#include "render.h"




#include "mesh.h"
#include "mutil.h"




static float vertexVoxel[] = {
	-0.500,-0.500, 0.502,	0.250, 0.250, 0.750,	/* 0.375, 0.250, 0.000,  */
	 0.500,-0.500, 0.502,	0.250, 0.250, 0.750,	/* 0.375, 0.250, 0.000,  */
	 0.500, 0.500, 0.502,	0.250, 0.250, 0.750,	/* 0.375, 0.250, 0.000,  */
	-0.500, 0.500, 0.502,	0.250, 0.250, 0.750,	/* 0.375, 0.250, 0.000,  */
	                        	                    /*                       */
	-0.501, 0.502, 0.501,	0.250, 0.750, 0.250,	/* 0.000, 0.250, 0.000,  */
	 0.501, 0.502, 0.501,	0.250, 0.750, 0.250,	/* 0.000, 0.250, 0.000,  */
	 0.501, 0.502,-0.501,	0.250, 0.750, 0.250,	/* 0.000, 0.250, 0.000,  */
	-0.501, 0.502,-0.501,	0.250, 0.750, 0.250,	/* 0.000, 0.250, 0.000,  */
	                        	                    /*                       */
	 0.502,-0.500, 0.500,	0.750, 0.250, 0.250,	/* 0.250, 0.125, 0.000,  */
	 0.502,-0.500,-0.500,	0.750, 0.250, 0.250,	/* 0.250, 0.125, 0.000,  */
	 0.502, 0.500,-0.500,	0.750, 0.250, 0.250,	/* 0.250, 0.125, 0.000,  */
	 0.502, 0.500, 0.500,	0.750, 0.250, 0.250,	/* 0.250, 0.125, 0.000,  */
	                        	                    /*                       */
	-0.500,-0.500,-0.502,	0.625, 0.625, 0.000,	/* 0.375, 0.250, 0.000,  */
	-0.500, 0.500,-0.502,	0.625, 0.625, 0.000,	/* 0.375, 0.250, 0.000,  */
	 0.500, 0.500,-0.502,	0.625, 0.625, 0.000,	/* 0.375, 0.250, 0.000,  */
	 0.500,-0.500,-0.502,	0.625, 0.625, 0.000,	/* 0.375, 0.250, 0.000,  */
	                        	                    /*                       */
	-0.501,-0.502, 0.501,	0.625, 0.000, 0.625,	/* 0.000, 0.250, 0.000,  */
	-0.501,-0.502,-0.501,	0.625, 0.000, 0.625,	/* 0.000, 0.250, 0.000,  */
	 0.501,-0.502,-0.501,	0.625, 0.000, 0.625,	/* 0.000, 0.250, 0.000,  */
	 0.501,-0.502, 0.501,	0.625, 0.000, 0.625,	/* 0.000, 0.250, 0.000,  */
	                        	                    /*                       */
	-0.502,-0.500, 0.500,	0.000, 0.625, 0.625,	/* 0.250, 0.125, 0.000,  */
	-0.502, 0.500, 0.500,	0.000, 0.625, 0.625,	/* 0.250, 0.125, 0.000,  */
	-0.502, 0.500,-0.500,	0.000, 0.625, 0.625,	/* 0.250, 0.125, 0.000,  */
	-0.502,-0.500,-0.500,	0.000, 0.625, 0.625,	/* 0.250, 0.125, 0.000,  */
};
static unsigned short elementsVoxel[] = {
	0,1,2,			0,2,3,
	4,5,6,			4,6,7,
	8,9,10,			8,10,11,
	12,13,14,		12,14,15,
	16,17,18,		16,18,19,
	20,21,22,		20,22,23,
};




#define levelsize 32
static unsigned char* level;

static float model[4*4] = {0};
static float view[4*4] = {0};
static float projection[4*4] = {0};




unsigned char integerscaling = 0;
unsigned short cameraframe = 0;
unsigned short cameraframescaled[2] = {0};

float cameradesrot[3] = {0};
static float cameraease = 2./16;
static float camerarot[3] = {0,M_PI/4,0};
int camerapos[3] = {0,0,0};

void cameraSetup(void){

	SDL_SetWindowResizable(isolaWindow,1);
	SDL_SetWindowSize(isolaWindow,
						isolaInfoWindow.desktopDisplayMode.w,
						isolaInfoWindow.desktopDisplayMode.h);
	isolaGetWindow();


	cameraframe = levelsize*4.;

	camerarot[0] = asin(0.5);

	camerapos[0] = levelsize/2. -1 ;
	camerapos[1] = levelsize/2. -1 ;
	camerapos[2] = levelsize/2. -1 ;


	model[0*4+0] = 1.;
	model[1*4+1] = 1.;
	model[2*4+2] = 1.;
	model[3*4+3] = 1.;

	view[0*4+0] = 1.;
	view[1*4+1] = 1.;
	view[2*4+2] = 1.;
	view[3*4+3] = 1.;

	view[3*4+0] = 0.;
	view[3*4+1] = 0.;
	view[3*4+2] = -64.;

}
void cameraUpdate(void){

	float rot[3*3] = {0};
	float brot[3*3] = {0};


	camerarot[0] = asin(0.5);
	if (fabs(cameradesrot[0])<(M_PI*cameraease)/64) {
		camerarot[0] += cameradesrot[0];
		cameradesrot[0] = 0;
	}else{
		camerarot[0] += cameradesrot[0]*cameraease;
		cameradesrot[0] -= cameradesrot[0]*cameraease;
	}
	if (fabs(cameradesrot[1])<(M_PI*cameraease)/64) {
		camerarot[1] += cameradesrot[1];
		cameradesrot[1] = 0;
	}else{
		camerarot[1] += cameradesrot[1]*cameraease;
		cameradesrot[1] -= cameradesrot[1]*cameraease;
	}
	if (fabs(cameradesrot[2])<(M_PI*cameraease)/64) {
		camerarot[2] += cameradesrot[2];
		cameradesrot[2] = 0;
	}else{
		camerarot[2] += cameradesrot[2]*cameraease;
		cameradesrot[2] -= cameradesrot[2]*cameraease;
	}
	if(camerarot[0]>2*M_PI){
		camerarot[0] -= 2*M_PI;
	}else if (camerarot[0]<0) {
		camerarot[0] += 2*M_PI;
	}
	if(camerarot[1]>2*M_PI){
		camerarot[1] -= 2*M_PI;
	}else if (camerarot[1]<0) {
		camerarot[1] += 2*M_PI;
	}
	if(camerarot[2]>2*M_PI){
		camerarot[2] -= 2*M_PI;
	}else if (camerarot[2]<0) {
		camerarot[2] += 2*M_PI;
	}


	rot[0*3+0] = 1;
	rot[1*3+1] = cos(camerarot[0]);
	rot[1*3+2] = sin(camerarot[0]);
	rot[2*3+1] = -sin(camerarot[0]);
	rot[2*3+2] = cos(camerarot[0]);

	brot[1*3+1] = 1;
	brot[0*3+0] = cos(camerarot[1]);
	brot[0*3+2] = -sin(camerarot[1]);
	brot[2*3+0] = sin(camerarot[1]);
	brot[2*3+2] = cos(camerarot[1]);
	mut_m3_mul(rot,brot,rot);
	brot[0*3+2] = 0.;
	brot[2*3+0] = 0.;

	brot[2*3+2] = 1;
	brot[0*3+0] = cos(camerarot[2]);
	brot[0*3+1] = sin(camerarot[2]);
	brot[1*3+0] = -sin(camerarot[2]);
	brot[1*3+1] = cos(camerarot[2]);
	mut_m3_mul(rot,brot,rot);

	mut_m3_cp_m4(rot,view);


	if(!integerscaling){
		cameraframescaled[0] = cameraframe*isolaInfoWindow.xratio-
						(int)(cameraframe*isolaInfoWindow.xratio)%2;
		cameraframescaled[1] = cameraframe*isolaInfoWindow.yratio-
						(int)(cameraframe*isolaInfoWindow.yratio)%2;
	}else{
		cameraframescaled[0] = cameraframe*isolaInfoWindow.xratio-
						(int)(cameraframe*isolaInfoWindow.xratio)%2;
		cameraframescaled[1] = cameraframe*isolaInfoWindow.yratio-
						(int)(cameraframe*isolaInfoWindow.yratio)%2;
	}
	mut_proj_glortho(-cameraframescaled[0]*(sqrt(2)/8),
					cameraframescaled[0]*(sqrt(2)/8),
					-cameraframescaled[1]*(sqrt(2)/8),
					cameraframescaled[1]*(sqrt(2)/8),
					0.250, 128., projection);


	if (camerapos[0] < 0) {
		camerapos[0] = 0;
	}else if (camerapos[0] > levelsize) {
		camerapos[0] = levelsize;
	}
	if (camerapos[1] < 0) {
		camerapos[1] = 0;
	}else if (camerapos[1] > levelsize) {
		camerapos[1] = levelsize;
	}
	if (camerapos[2] < 0) {
		camerapos[2] = 0;
	}else if (camerapos[2] > levelsize) {
		camerapos[2] = levelsize;
	}
	model[3*4+0] = -camerapos[0];
	model[3*4+1] = -camerapos[1]/(sqrt(2)*cos(asin(0.5)));
	model[3*4+2] = -camerapos[2];
}




void recursetree(unsigned char head){

	static unsigned short count = 0;
	static unsigned short x=levelsize/2,y=0,z=levelsize/2;
	int i;


	switch (head) {
		case 0:
			if (y+1 < levelsize) {
				y++;
			}else { return; }
		break;
		case 1:
			if (z+1 < levelsize) {
				z++;
			}else { return; }
		break;
		case 2:
			if (x+1 < levelsize) {
				x++;
			}else { return; }
		break;
		case 3:
			if (z != 0) {
				z--;
			}else { return; }
		break;
		case 4:
			if (x != 0) {
				x--;
			}else { return; }
		break;
		case 5:
			y--;
		break;
		case 6:
			count = 0;
			x = levelsize/2;
			y = 0;
			z = levelsize/2;
			y++;
		break;
	}

	if (	!level[z+y*levelsize+x*levelsize*levelsize]
			&& count<pow(levelsize,2)
			&& rand()%4	){
		level[z+y*levelsize+x*levelsize*levelsize] = 1;
		count++;
	}else {goto back;}

	if (!(rand()%2)) {
		for (i = 0; i<5; i++) {
/* 			if (!(rand()%2)) { */
				recursetree((rand()%5)+1);
/* 			} */
		}
	}else {recursetree(0);}

	back:
	switch (head) {
		case 0:
			y--;
		break;
		case 1:
			z--;
		break;
		case 2:
			x--;
		break;
		case 3:
			z++;
		break;
		case 4:
			x++;
		break;
		case 5:
			y++;
		break;
	}
}
void levelCreate(void){

	unsigned short i,j,k;
	unsigned short u,o,l;


	level = calloc(pow(levelsize,3),sizeof(unsigned char));

	for(i = 0;i<levelsize -2;i+=3){
		for(j = 0;j<levelsize -2;j+=3){
			for(k = 0;k<levelsize -2;k+=3){

/* 				if(rand()%2){ */
				if(1){
					for(u = 0;u<2;u++){
						for(o = 0;o<2;o++){
							for(l = 0;l<2;l++){
								level[k+j*levelsize+i*levelsize*levelsize +
										u+o*levelsize+l*levelsize*levelsize]
/* 									= rand()%3 & rand()%3 & rand()%3; */
									= 1;

							}
						}
					}
				}
/* 				level[k+j*levelsize+i*levelsize*levelsize] = rand()%2; */
			}
		}
	}
	
/* 	levelreset();
 	recursetree(0); */

}
void levelreset(void){

	int i,j,k;


	for(i = 0;i<levelsize;i++){
		for(j = 0;j<levelsize;j++){
			for(k = 0;k<levelsize;k++){
				if (j==0) {
					level[k+j*levelsize+i*levelsize*levelsize] = 1;
				}else{
					level[k+j*levelsize+i*levelsize*levelsize] = 0;
				}
			}
		}
	}

}




static unsigned int drawBuffers[1];
static unsigned int renderBuffer[2];
static unsigned int frameBuffer[1];

static unsigned int elementBuffer[1];
static unsigned int vertexArrayObject[1];
static unsigned int vertexBuffer[1];
static unsigned int shaderProgram[1];
void renderCreate(void){

	int locPos = 0,locCol = 1;
	int id;
	unsigned int vs, fs;
	int locMdl, locViw, locPrj, locDis;


	levelCreate();




	glGenFramebuffers(1,&frameBuffer[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,frameBuffer[0]);
	glGenRenderbuffers(2,&renderBuffer[0]);

	glBindRenderbuffer(GL_RENDERBUFFER,renderBuffer[0]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_RGB,
							isolaInfoWindow.desktopDisplayMode.w,
							isolaInfoWindow.desktopDisplayMode.h);
	glBindRenderbuffer(GL_RENDERBUFFER,renderBuffer[1]);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT24,
							isolaInfoWindow.desktopDisplayMode.w,
							isolaInfoWindow.desktopDisplayMode.h);

	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
							  GL_RENDERBUFFER,renderBuffer[0]);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,
							  GL_RENDERBUFFER,renderBuffer[1]);

	drawBuffers[0] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1,drawBuffers);

	cameraSetup();




	glGenVertexArrays(1,&vertexArrayObject[0]);
	glGenBuffers(1,&vertexBuffer[0]);
	glGenBuffers(1,&elementBuffer[0]);


	id = 0;
	glBindVertexArray(vertexArrayObject[id]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elementBuffer[id]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elementsVoxel),
				 elementsVoxel,GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0,
					sizeof(elementsVoxel),elementsVoxel);

	glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer[id]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexCube),
				 vertexCube,GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,
					sizeof(vertexCube),vertexCube);

	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos,3,GL_FLOAT,GL_FALSE,
						  sizeof(vertexCube[0])*6,(void*)0);
	
	glEnableVertexAttribArray(locCol);
	glVertexAttribPointer(locCol,3,GL_FLOAT,GL_FALSE,
						  sizeof(vertexCube[0])*6,
						  (void*)(sizeof(vertexCube[0])*3));




	id = 0;
	shaderProgram[id] = glCreateProgram();
	vs = isolaShaderCompile("glsl/default.vert",GL_VERTEX_SHADER);
	fs = isolaShaderCompile("glsl/default.frag",GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgram[id],vs);
	glAttachShader(shaderProgram[id],fs);

	glBindAttribLocation(shaderProgram[id],locPos,"vertPosition");
	glBindAttribLocation(shaderProgram[id],locCol,"vertColor");

	glLinkProgram(shaderProgram[id]);
	glDetachShader(shaderProgram[id],vs);
	glDetachShader(shaderProgram[id],fs);
	glDeleteShader(vs);
	glDeleteShader(fs);




	id = 0;
	glUseProgram(shaderProgram[id]);

	locMdl = glGetUniformLocation(shaderProgram[id],"matModel");
	if(locMdl == -1){SDL_Log("matModel not found in shader %d",id);}
	glUniformMatrix4fv(locMdl,1,GL_FALSE,model);

	locViw = glGetUniformLocation(shaderProgram[id],"matView");
	if(locViw == -1){SDL_Log("matView not found in shader %d",id);}
	glUniformMatrix4fv(locViw,1,GL_FALSE,view);

	locPrj = glGetUniformLocation(shaderProgram[id],"matProj");
	if(locPrj == -1){SDL_Log("matProj not found in shader %d",id);}
	glUniformMatrix4fv(locPrj,1,GL_FALSE,projection);

}
void renderDestroy(void){

	free(level);

	glBindRenderbuffer(GL_RENDERBUFFER,0);
	glDeleteRenderbuffers(2,&renderBuffer[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
	glDeleteFramebuffers(1,&frameBuffer[0]);

	glUseProgram(0);
	glBindVertexArray(0);
	glDeleteProgram(shaderProgram[0]);
	glDeleteBuffers(1,vertexBuffer);
	glDeleteBuffers(1,elementBuffer);
	glDeleteVertexArrays(1,vertexArrayObject);
}
void renderDraw(void){

	int id;
	int locMdl, locViw, locPrj, locLevel;
	unsigned int i,j,k;


	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,frameBuffer[0]);
	glViewport(0,0,cameraframescaled[0],cameraframescaled[1]);
	glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

	id = 0;
	glBindVertexArray(vertexArrayObject[id]);
	glUseProgram(shaderProgram[id]);
	locMdl = glGetUniformLocation(shaderProgram[id],"matModel");
	glUniformMatrix4fv(locMdl,1,GL_FALSE,model);
	locViw = glGetUniformLocation(shaderProgram[id],"matView");
	glUniformMatrix4fv(locViw,1,GL_FALSE,view);
	locPrj = glGetUniformLocation(shaderProgram[id],"matProj");
	glUniformMatrix4fv(locPrj,1,GL_FALSE,projection);
	locLevel = glGetUniformLocation(shaderProgram[id],"position");
	glUniform3f(locLevel,0,sqrt(2)/(8.*cos(asin(0.5))),0);

	for(i = 0;i<levelsize;i++){
		for(j = 0;j<levelsize;j++){
			for(k = 0;k<levelsize;k++){
				if (level[k+j*levelsize+i*levelsize*levelsize]) {
					glUniform3f(locLevel,k,j+sqrt(2)/(8.*cos(asin(0.5))),i);
					glDrawRangeElements(GL_TRIANGLES,0,
							0-1+sizeof(elementsVoxel)/sizeof(elementsVoxel[0]),
							sizeof(elementsVoxel)/sizeof(elementsVoxel[0]),
							GL_UNSIGNED_SHORT,(void*)0);
				}
			}
		}
	}

	glBindFramebuffer(GL_READ_FRAMEBUFFER,frameBuffer[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
	glBlitFramebuffer(0,0,cameraframescaled[0],cameraframescaled[1],
						0,0,isolaInfoWindow.width,isolaInfoWindow.height,
						GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT,GL_NEAREST);

	SDL_GL_SwapWindow(isolaWindow);
}




