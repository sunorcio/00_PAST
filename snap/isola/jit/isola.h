#ifndef ISOLA_H
#define ISOLA_H





/* [1^0]  NOT IMPLEMENTED : runtime parse of parameters */
#define ISOLA_INITPARSE		0
/* [1^0]  alternatively, set -DISOLA_DBG flag */
#define ISOLA_DEBUG			1
/* [1^0]  input stderr to file (./isola.log) */
#define ISOLA_LOG			0

/* Init parameters for SDL context creation ________________________________ */

#define ISOLA_GAMEPAD			0  /* [1^0] */
#define ISOLA_DEPTH				1  /* [1^0] */
#define ISOLA_STENCIL			0  /* [1^0] */
#define ISOLA_ALPHA				0  /* [1^0] */
#define ISOLA_DOUBLEBUFFER		1  /* [1^0] */
#define ISOLA_MSANTIALIASING	0  /* [0^2^4^8^16] (requires doublebuffer) */
#define ISOLA_MAJOR_VERSION		3  /* gl version ( 4.6 == MAJ 4, MIN 6 ) */
#define ISOLA_MINOR_VERSION		0
/* SDL_GL_CONTEXT_PROFILE_[CORE^COMPATIBILITY]	(only since version 3.2) */
#define ISOLA_PROFILE			SDL_GL_CONTEXT_PROFILE_CORE
#define ISOLA_GLSLCHARMAX		10000  /* default glsl buffer size */

/* _________________________________________________________________________ */


#if defined(ISOLA_GAMEPAD) && (ISOLA_GAMEPAD < 0 || ISOLA_GAMEPAD > 1)
 #error ISOLA_GAMEPAD: invalid definition
#endif
#if defined(ISOLA_MSANTIALIASING) && (ISOLA_MSANTIALIASING < 0                \
									|| ISOLA_MSANTIALIASING > 16)
 #error ISOLA_MSANTIALIASING: invalid definition
#endif
#if defined(ISOLA_GLSLCHARMAX) && ISOLA_GLSLCHARMAX <= 0
 #error ISOLA_GLSLCHARMAX: invalid definition
#endif

#if(ISOLA_DEBUG)
 #define ISOLA_DBG 1
#endif





#include <SDL2/SDL.h>
#include <GL/glew.h>





/* extended replacement for SDL_Init() */ 
extern void isolaInit(void);
extern void isolaQuit(void);




#ifdef ISOLA_DBG
 #define isolaDBG_(x) if(isolaErrorGL()){                                     \
						SDL_Log(" UNEXPECTED ERROR, line : %d, file : %s\n",  \
								__LINE__,__FUNCTION__,__FILE__);              \
					  }                                                       \
					  x;                                                      \
					  if(isolaErrorGL()){                                     \
						SDL_Log(" ^- in line : %d, file : %s\n\n",			  \
								__LINE__,__FUNCTION__,__FILE__);              \
					  }
#else
 #define isolaDBG_(x) x;
#endif

/* print & clear sdl errors, returns -1 if error, else 0 */
extern signed char isolaErrorSDL(int SDLfunction);
/* print & clear gl errors, returns -1 if error, else 0 */
extern signed char isolaErrorGL(void);




extern SDL_GLContext* isolaContext;
extern SDL_Window* isolaWindow;

struct ISOLA_Context{
	int maxVertices;
	int maxIndices;
	int maxAttrib;
	int maxVertexUniforms;
	int maxFragmentUniforms;
	int maxSamplers;
	int maxTexUnits;
	int maxTexSize;
	int max3DTexSize;
	int maxCubeTexSize;
	int maxDrawBuffers;
	int maxColorAttachments;
	int maxRenderbufferSize;

	int cpuCount;
	int systemRAM;
	int cacheSize;
}extern isolaInfoContext;

struct ISOLA_Window{
	int xpos;
	int ypos;
	int width;
	int height;
	int flags;
	int displayIndex;
	SDL_DisplayMode displayMode;
}extern isolaInfoWindow;

struct ISOLA_Display{
	int* displayModeCount;
	SDL_DisplayMode* displayModes;
}extern isolaInfoDisplay;

#define isolaStateBLEND				0x0001
#define isolaStateCOLORLOGIC		0x0002
#define isolaStateCULLFACE 			0x0004
#define isolaStateDEPTHTEST			0x0008
#define isolaStateDITHER 			0x0010
#define isolaStateDOUBLEBUFFER		0x0020
#define isolaStateSCISSORTEST 		0x0040
#define isolaStateSTENCILTEST 		0x0080
#define isolaStateSRGBFRAMEBUFFER 	0x0100
#define isolaStatePOINTSMOOTH 		0x0200
#define isolaStateLINESMOOTH 		0x0400
#define isolaStatePOLYGONSMOOTH		0x0800
#define isolaStatePOINTSIZEPROGRAM	0x1000
#define isolaStateMULTISAMPLE 		0x2000
extern unsigned int isolaInfoState;



/* update window information in (isolaWindowInfo) */
extern void isolaGetWindow(void);
/* update window & current display availiable modes in (isolaDisplayInfo) */
extern void isolaGetDisplay(void);
/* retrieve current opengl state */
extern void isolaGetState(void);




/* compile source file into returned gl shader object id */
extern unsigned int isolaShaderCompile(const char* shaderFile,
									   unsigned int shaderType);

/* loads srcfile into heap, returns a pointer that can be issued to
 * isolaShaderSrcCompare(), you must free this pointer yourself */
extern char* isolaShaderSrcLoad(const char* shaderFile);
/* compares srcfile with loaded src, if !=, src is updated and return !0 */
extern unsigned char isolaShaderSrcCompare(char* shaderSrc,
										   const char* shaderFile);





#endif
