#ifndef RENDER_H
#define RENDER_H




#include "isola.h"
#include "mutil.h"




extern float cameradesrot[3];
extern float cameradespos[3];
extern unsigned short cameradesframe;
extern void cameraUpdate(void);

extern void renderCreate(void);
extern void renderDestroy(void);
extern void renderDraw(void);




#endif
