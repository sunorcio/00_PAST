
default_rule: all
	./$(BIN)


BIN = isola_example
CC = clang

#CFLAGS = -Wall -Wextra -pedantic -std=c89 -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
CFLAGS = -Wall -Wextra -pedantic -std=c89 -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -MJ $@.json
OPT = -O3 -pipe -march=native
#

LIBS = -lGLEW -lGL -lGLU -lSDL2 -lm
LDFLAGS = ${LIBS}

SRC = isola.c render.c main.c
OBJ = ${SRC:.c=.o}

DEPS = ${SRC}



.c.o:
#	${CC} -c ${CFLAGS} $<
	${CC} -c ${CFLAGS} ${OPT} $<

${OBJ}: ${DEPS}



all: $(BIN) Compdb clean

$(BIN): ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

Compdb: ${OBJ}
	./Compdb

clean: $(BIN)
	rm *.o*
	


#TODO
# Depends on these sources:
# glew - https://github.com/nigels-com/glew
# SDL - https://github.com/libsdl-org/SDL
# consider using cglm (c) or glm (c++) for vector math and gl matrix setup
#
# ____________________DYNAMIC COMPILE
# 
# Linux
# 
# clang sdlglExample_main.c -lm -lGLEW -lGL -lGLU -lSDL2 /
# -O3 -march=native -pipe
#  
# ____________________STATIC COMPILE 
# 
# 	Linux
# clang sdlglExample_main.c -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -Wl,-Bstatic -lSDL2 -lGLEW -lGLU -Wl,-Bdynamic -lGL -lm -ldl -lpthread -lrt -DGLEW_STATIC
# 
# 	Windows (Crosscompiled)	[GLEW windows binaries] : 
#
# x86_64-w64-mingw32-gcc sdlglExample_main.c -o win64.exe --static -I/usr/local/x86_64-w64-mingw32/include -I/[PATH_TO_GLEW_SOURCE]/include -L/usr/local/x86_64-w64-mingw32/lib -L/[PATH_TO_GLEW_SOURCE]/lib/Release/x64 -Wl,-Bstatic -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -lsetupapi -lcfgmgr32 -luuid -static-libgcc -lglew32s -lopengl32 -lglu32 -DGLEW_STATIC
# 
# i686-w64-mingw32-gcc sdlglExample_main.c -o win32.exe --static -I/usr/local/i686-w64-mingw32/include -I/[PATH_TO_GLEW_SOURCE]/include -L/usr/local/i686-w64-mingw32/lib -L/[PATH_TO_GLEW_SOURCE]/lib/Release/Win32 -Wl,-Bstatic -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -lsetupapi -lcfgmgr32 -luuid -static-libgcc -lglew32s -lopengl32 -lglu32 -DGLEW_STATIC
