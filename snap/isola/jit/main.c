
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#include "isola.h"


#include "matrix.h"
#include "render.h"




float xrot[3*3] = {0};
float yrot[3*3] = {0};
float zrot[3*3] = {0};
float brot[3*3] = {0};
float camerarad[3] = {((M_PI*2)/360)*35,M_PI/4,0};
float cameradesrad[3] = {((M_PI*2)/360)*35,M_PI/4,0};
void mrot(void){
	camerarad[0] = (cameradesrad[0]-camerarad[0])*0.9;
	camerarad[1] = (cameradesrad[1]-camerarad[1])*0.9;
	camerarad[2] = (cameradesrad[2]-camerarad[2])*0.9;

	xrot[0*3+0] = 1;
	xrot[1*3+1] = cos(camerarad[0]);
	xrot[1*3+2] = sin(camerarad[0]);
	xrot[2*3+1] = -sin(camerarad[0]);
	xrot[2*3+2] = cos(camerarad[0]);

	yrot[1*3+1] = 1;
	yrot[0*3+0] = cos(camerarad[1]);
	yrot[0*3+2] = -sin(camerarad[1]);
	yrot[2*3+0] = sin(camerarad[1]);
	yrot[2*3+2] = cos(camerarad[1]);

	zrot[2*3+2] = 1;
	zrot[0*3+0] = cos(camerarad[2]);
	zrot[0*3+1] = sin(camerarad[2]);
	zrot[1*3+0] = -sin(camerarad[2]);
	zrot[1*3+1] = cos(camerarad[2]);

	mat_mul_3(xrot,yrot,brot);
	mat_mul_3(brot,zrot,brot);
	mat_cp_3_4(brot,view);
}


void loop(void){
	#define isolaFPS 60
	#define isolaSPS 60
	const unsigned long clockFreq = SDL_GetPerformanceFrequency();
	unsigned long lastFrame = SDL_GetPerformanceCounter();
	unsigned long lastStep = SDL_GetPerformanceCounter();

	int keyLength;
	const unsigned char* keyState = SDL_GetKeyboardState(&keyLength);

	SDL_Event event = {0};
	unsigned char run = 1;
	unsigned char pause = 0;
	while(run){
		while (SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){run = 0;}
			if(event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){

					case SDLK_ESCAPE:
						run = !run;
					break;
					case SDLK_q:
						run = !run;
					break;
					case SDLK_p:
						pause = !pause;
					break;
					case SDLK_SPACE:
						printm4(view);
						printm4(projection);
					break;
					case SDLK_a:
						cameradesrad[1] += M_PI/4;
						if(cameradesrad[1]>M_PI*2){cameradesrad[1]-=M_PI*2;}
					break;
					case SDLK_d:
						cameradesrad[1] -= M_PI/4;
						if(cameradesrad[1]<0){cameradesrad[1]=(M_PI*2)+cameradesrad[1];}
					break;
				}
			}
		}

		if(!pause){
			if(SDL_GetPerformanceCounter()>=lastStep+clockFreq/isolaSPS){
				lastStep = SDL_GetPerformanceCounter();

/* 				if (keyState[SDL_SCANCODE_A]){
					cameradesrad[1] += M_PI/32;
					if(cameradesrad[1]>M_PI*2){cameradesrad[1]-=M_PI*2;}
				} */
/* 				if (keyState[SDL_SCANCODE_D]){
					cameradesrad[1] -= M_PI/32;
					if(cameradesrad[1]<0){cameradesrad[1]=M_PI*2-cameradesrad[1];}
				} */
				if (keyState[SDL_SCANCODE_S]){
					cameradesrad[0] -= M_PI/32;
					if(cameradesrad[0]<-M_PI/2){cameradesrad[0]=-M_PI/2;}
				}
				if (keyState[SDL_SCANCODE_W]){
					cameradesrad[0] += M_PI/32;
					if(cameradesrad[0]>M_PI/2){cameradesrad[0]=M_PI/2;}
				}

				mrot();
			}
		}

		if(SDL_GetPerformanceCounter()>=lastFrame+clockFreq/isolaFPS){
			lastFrame = SDL_GetPerformanceCounter();

			draw();

		}else{SDL_Delay(1);}

	}
}




int main(void){
	srand(time(0));
	isolaInit();


	renderCreate();
	loop();
	renderDestroy();


	isolaErrorGL();
	isolaErrorSDL(-1);
	isolaQuit();
	return 0;
}




