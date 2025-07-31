#ifndef RENDER_H
#define RENDER_H




extern unsigned int resolution[2];
extern unsigned int framesize[2];

extern float view[4*4];
extern float projection[4*4];

extern void renderCreate(void);
extern void renderDestroy(void);
extern void draw(void);




#endif
