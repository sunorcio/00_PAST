#ifndef RENDER_H
#define RENDER_H




#include "isola.h"




extern void levelreset(void);
extern void recursetree(unsigned char head);

extern unsigned char integerscaling;
extern unsigned short cameraframe;
extern unsigned short cameraframescaled[2];
extern float cameradesrot[3];
extern int camerapos[3];
extern void cameraUpdate(void);

extern void renderCreate(void);
extern void renderDestroy(void);
extern void renderDraw(void);




#endif
