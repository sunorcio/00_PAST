
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


#include "isola.h"


#include "mutil.h"
#include "render.h"




float cameracurrad[3] = {0,M_PI/4,0};
float cameradesrad[3] = {0};
float cameraease = 2./16;
float xrot[3*3] = {0};
float yrot[3*3] = {0};
float zrot[3*3] = {0};
float brot[3*3] = {0};
void mrot(void){
	cameracurrad[0] = asin(0.5);
	cameracurrad[0] += cameradesrad[0]*cameraease;
	cameradesrad[0] -= cameradesrad[0]*cameraease;
	cameracurrad[1] += cameradesrad[1]*cameraease;
	cameradesrad[1] -= cameradesrad[1]*cameraease;
	cameracurrad[2] += cameradesrad[2]*cameraease;
	cameradesrad[2] -= cameradesrad[2]*cameraease;


	xrot[0*3+0] = 1;
	xrot[1*3+1] = cos(cameracurrad[0]);
	xrot[1*3+2] = sin(cameracurrad[0]);
	xrot[2*3+1] = -sin(cameracurrad[0]);
	xrot[2*3+2] = cos(cameracurrad[0]);

	yrot[1*3+1] = 1;
	yrot[0*3+0] = cos(cameracurrad[1]);
	yrot[0*3+2] = -sin(cameracurrad[1]);
	yrot[2*3+0] = sin(cameracurrad[1]);
	yrot[2*3+2] = cos(cameracurrad[1]);

	zrot[2*3+2] = 1;
	zrot[0*3+0] = cos(cameracurrad[2]);
	zrot[0*3+1] = sin(cameracurrad[2]);
	zrot[1*3+0] = -sin(cameracurrad[2]);
	zrot[1*3+1] = cos(cameracurrad[2]);

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
					case SDLK_q:
						run = !run;
					break;
					break;
					case SDLK_p:
						pause = !pause;
					break;
					case SDLK_a:
						cameradesrad[1] += M_PI/2;
					break;
					case SDLK_d:
						cameradesrad[1] -= M_PI/2;
					break;
					case SDLK_i:
						if (frame[0]+ratio[0]*4 < 
								isolaInfoWindow.width &&
							frame[1]+ratio[1]*4 < 
								isolaInfoWindow.height ) {
						frame[0] += ratio[0]*4;
						frame[1] += ratio[1]*4;
						view[3*4+1] = (sqrt(2)/ (2.*cos(asin(0.5)))) /
										(gcd(frame[0],frame[1])*2);
					}
					break;
					case SDLK_k:
					if (frame[0] > ratio[0]*4) {
						frame[0] -= ratio[0]*4;
						frame[1] -= ratio[1]*4;
						view[3*4+1] = (sqrt(2)/ (2.*cos(asin(0.5)))) /
										(gcd(frame[0],frame[1])*2);
					}
					break;
				}
			}
		}

		if(!pause){
			if(SDL_GetPerformanceCounter()>=lastStep+clockFreq/isolaSPS){
				lastStep = SDL_GetPerformanceCounter();

				if (keyState[SDL_SCANCODE_S]){
					cameradesrad[0] -= asin(0.5);
				}
				if (keyState[SDL_SCANCODE_W]){
					cameradesrad[0] += M_PI/2-asin(0.5);
				}

				mrot();
			}
		}

		if(SDL_GetPerformanceCounter()>=lastFrame+clockFreq/isolaFPS){
			lastFrame = SDL_GetPerformanceCounter();

			renderDraw();

		}else{SDL_Delay(1);}

	}
}




int main(void){

	srand(time(0));
	isolaInit();
	SDL_GL_SetSwapInterval(0);


	renderCreate();
	loop();
	renderDestroy();


	isolaErrorGL();
	isolaErrorSDL(-1);
	isolaQuit();
	return 0;
}




