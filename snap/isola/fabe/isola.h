#ifndef ISOLA_H
#define ISOLA_H




/* isola configuration _____________________________________________________ */

/* alternatively, set -DISOLA_DBG flag */
#define ISOLA_CONFIG_DEBUG			1  /* [1^0] */
/* input stderr to file (./isola.log) */
#define ISOLA_CONFIG_LOG			0  /* [1^0] */


/* init parameters for SDL context creation ________________________________ */

#define ISOLA_WINDOWTITLE		"isola_example"
#define ISOLA_GAMEPAD			0  /* [1^0] */
#define ISOLA_DEPTH				1  /* [1^0] */
#define ISOLA_STENCIL			0  /* [1^0] */
#define ISOLA_ALPHA				1  /* [1^0] */
#define ISOLA_DOUBLEBUFFER		1  /* [1^0] */
#define ISOLA_MSANTIALIASING	0  /* [0^2^4^8^16] (requires doublebuffer) */
#define ISOLA_VSYNC				0  /* [1^0] */
#define ISOLA_MAJOR_VERSION		3  /* gl version ( 4.6 == MAJ 4, MIN 6 ) */
#define ISOLA_MINOR_VERSION		0
/* SDL_GL_CONTEXT_PROFILE_[CORE^COMPATIBILITY]	(only since version 3.2) */
#define ISOLA_PROFILE			SDL_GL_CONTEXT_PROFILE_CORE
#define ISOLA_GLSLCHARMAX		10000  /* default glsl buffer size */

/* _________________________________________________________________________ */




#if defined(ISOLA_GAMEPAD) && (ISOLA_GAMEPAD != 0 && ISOLA_GAMEPAD != 1)
 #error ISOLA_GAMEPAD: invalid definition
#endif
#if defined(ISOLA_MSANTIALIASING) && (ISOLA_MSANTIALIASING < 0                \
			|| ISOLA_MSANTIALIASING > 16 || ISOLA_MSANTIALIASING%2)
 #error ISOLA_MSANTIALIASING: invalid definition
#endif
#if defined(ISOLA_VSYNC) && (ISOLA_VSYNC != 0 && ISOLA_VSYNC != 1)
 #error ISOLA_VSYNC: invalid definition
#endif
#if defined(ISOLA_GLSLCHARMAX) && ISOLA_GLSLCHARMAX <= 0
 #error ISOLA_GLSLCHARMAX: invalid definition
#endif


#if(ISOLA_CONFIG_DEBUG)
 #define ISOLA_DBG 1
#endif


#define STR_(X) #X
#define STR(X) STR_(X)




#include <SDL2/SDL.h>
#include <GL/glew.h>




/* extended replacement for SDL_Init() */ 
extern void isolaInit(void);
/* extended replacement for SDL_Quit() */ 
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


/* system resources and specification related information */
struct ISOLA_Context{
	int fbdefRedsize;
	int fbdefGreensize;
	int fbdefBluesize;
	int fbdefAlphasize;
	int fbdefDepthsize;
	int fbdefStencilsize;		/* GL_LINEAR or GL_SRGB */
	int fbdefColorencoding;

	int maxVertices;
	int maxIndices;				/* at least 16 */
	int maxAttrib;				/* at least 1024 */
	int maxVertexUniforms;		/* at least 1024 */
	int maxFragmentUniforms;	/* at least 64 */
	int maxTexCombinedUnits;	/* at least 16 */
	int maxTexUnits;			/* at least 1024 */
	int maxTexSize;				/* at least 64 */
	int max3DTexSize;			/* at least 1024 */
	int maxCubeTexSize;			/* at least 8 */
	int maxDrawBuffers;			/* at least 8 */
	int maxColorAttachments;	/* at least 8 */
	int maxRenderbufferSize;

	int cpuCount;
	int systemRAM;
	int cacheSize;
}extern isolaInfoContext;

/* current window state. updated with isolaGetWindow() */
struct ISOLA_Window{
	int xpos;
	int ypos;
	int width;
	int height;
	float xratio;
	float yratio;
	int flags;	/* see SDL_WindowFlags for a list of flags */
	int displayIndex;
	SDL_DisplayMode displayMode;
	SDL_DisplayMode desktopDisplayMode;
}extern isolaInfoWindow;

/* dysplay modes for all availiable devices. retrieved with isolaGetDisplay() */
struct ISOLA_Display{
/* 	number of display modes for the id, access array with desired display id */
	int* displayModeCount;
/*	contains ALL display modes, for specific display id, its modes range from
	(sum of previous counts - 1) to (sum of previous counts + count - 1) */
	SDL_DisplayMode* displayModes;
}extern isolaInfoDisplay;

typedef enum {
	ISOLA_STATE_BLEND				= 0x0001,
	ISOLA_STATE_COLORLOGIC			= 0x0002,
	ISOLA_STATE_CULLFACE 			= 0x0004,
	ISOLA_STATE_DEPTHTEST			= 0x0008,
	ISOLA_STATE_DITHER				= 0x0010,
	ISOLA_STATE_DOUBLEBUFFER		= 0x0020,
	ISOLA_STATE_SCISSORTEST 		= 0x0040,
	ISOLA_STATE_STENCILTEST 		= 0x0080,
	ISOLA_STATE_SRGBFRAMEBUFFER 	= 0x0100,
	ISOLA_STATE_POINTSMOOTH 		= 0x0200,
	ISOLA_STATE_LINESMOOTH			= 0x0400,
	ISOLA_STATE_POLYGONSMOOTH		= 0x0800,
	ISOLA_STATE_POINTSIZEPROGRAM	= 0x1000,
	ISOLA_STATE_MULTISAMPLE 		= 0x2000
}ISOLA_State;
/* glEnable information. meant for quick debugging. see isolaGetState() */
extern ISOLA_State isolaInfoState;


/* update window information (isolaInfoWindow) */
extern void isolaGetWindow(void);
/* retrieve all availiable display information (isolaInfoDisplay) */
extern void isolaGetDisplay(void);
/* update currently enabled opengl state (isolaInfoState) */
extern void isolaGetState(void);




/* compile source file into returned gl shader object id */
extern unsigned int isolaShaderCompile(const char* shaderFile,
									   unsigned int shaderType);

/* loads srcfile into heap, returns a pointer that can be issued to
   isolaShaderSrcCompare(), you must free this pointer yourself */
extern char* isolaShaderSrcLoad(const char* shaderFile);
/* compares srcfile with loaded src, if !=, src is updated and return !0 */
extern unsigned char isolaShaderSrcCompare(char* shaderSrc,
										   const char* shaderFile);





#endif
