


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <math.h>



/*
S16 format
1-6000 safety range
*/
#define DSRATE 48000
#define DSCHAN 1
#define DSTIME 10
#define DSNUMS (DSRATE*DSCHAN*DSTIME)
#define DSMAMP 0x7fff
#define DSDAMP 0x007f
#define DSLWFQ 1
#define DSHGFQ 4000


void spike(int16_t* sdata){
	const float fq = 300;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph <= M_PI_2) {
			sdata[i] = (ph/M_PI_2) * DSDAMP;
		}else if (ph <= M_PI) {
			sdata[i] = DSDAMP - (ph/M_PI_2-1) * DSDAMP;
		}else if (ph < M_PI+M_PI_2) {
			sdata[i] = (ph/M_PI_2-2) * -DSDAMP;
		}else{
			sdata[i] = -DSDAMP + (ph/M_PI_2-3) * DSDAMP;
		}
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
void square(int16_t* sdata){
	const float fq = 300;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph < M_PI) {
			sdata[i] = DSDAMP;
		}else {
			sdata[i] = -DSDAMP;
		}
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
void saw(int16_t* sdata){
	const float fq = 300;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph < M_PI) {
			sdata[i] = (ph/M_PI)*DSDAMP;
		}else {
			sdata[i] = -DSDAMP + (ph/M_PI_2)*DSDAMP;
		}	
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
void sine(int16_t* sdata){
	const float fq = 300;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		sdata[i] = sinf(ph)*DSDAMP;
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}

void sweepspike(int16_t* sdata){
	float fq = DSLWFQ;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph <= M_PI_2) {
			sdata[i] = (ph/M_PI_2) * DSDAMP;
		}else if (ph <= M_PI) {
			sdata[i] = DSDAMP - (ph/M_PI_2-1)*DSDAMP;
		}else if (ph < M_PI+M_PI_2) {
			sdata[i] = (ph/M_PI_2-2) * -DSDAMP;
		}else{
			sdata[i] = -DSDAMP + (ph/M_PI_2-3)*DSDAMP;
		}
		fq = DSLWFQ + (DSHGFQ - DSLWFQ)*((float)i/DSNUMS) ;
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
/* weird two tone in higher square/saw frequencies, check wave alignment (maybe get rid of vertical definition) */
void sweepsquare(int16_t* sdata){
	float fq = DSLWFQ;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph < M_PI) {
			sdata[i] = DSDAMP;
		}else if (ph >= M_PI) {
			sdata[i] = -DSDAMP;
		}
		fq = DSLWFQ + (DSHGFQ - DSLWFQ)*((float)i/DSNUMS) ;
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
void sweepsaw(int16_t* sdata){
	float fq = DSLWFQ;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		if (ph < M_PI) {
			sdata[i] = (ph/M_PI)*DSDAMP;
		}else {
			sdata[i] = -DSDAMP + (ph/M_PI_2)*DSDAMP;
		}	
		fq = DSLWFQ + (DSHGFQ - DSLWFQ)*((float)i/DSNUMS) ;
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}
void sweepsine(int16_t* sdata){
	float fq = DSLWFQ;
	float ph = 0;

	unsigned int i;
	for (i = 0; i<DSNUMS; i++) {
		sdata[i] = sinf(ph)*DSDAMP;
		fq = DSLWFQ + (DSHGFQ - DSLWFQ)*((float)i/DSNUMS) ;
		ph += (M_PI*2)/(DSRATE/fq);
		if (ph >= M_PI*2) {
			ph -= M_PI*2;
		}
	}
}



/*
#include <unistd.h>
*/


void soundgen(int16_t* sdata){
	sweepsaw(sdata);
}

int main(void){
	int16_t* sdata;
	FILE* sound;
	/*
	char* const cmd[] = {"aplay","sound","-f","S16","-r","48000","-c","1","-d","1",(char*)0};
	*/

	sdata = calloc(DSNUMS, sizeof(int16_t));


	soundgen(sdata);


	sound = fopen("sound", "wb");
	fwrite(sdata, sizeof(int16_t), DSNUMS, sound);
	fclose(sound);
	free(sdata);
	
	/*
	execvp("aplay", cmd);
	*/
	}



