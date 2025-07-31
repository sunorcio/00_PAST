



#(linux^windows)
TARGET_OS = linux
#(dynamic^)
TARGET_BUILD = dynamic
#(on^off)
TARGET_DEBUG = off
TARGET_BIN = socket_host




default_rule: test




ifeq (${TARGET_OS},linux)
 CC = clang
else ifeq (${TARGET_OS},windows)
 CC = x86_64-w64-mingw32-gcc
else
 $(error wrong TARGET_OS value)
endif

ifeq (${TARGET_BUILD},dynamic)
else ifeq (${TARGET_BUILD},static)
else
 $(error wrong TARGET_BUILD value)
endif

ifeq (${TARGET_DEBUG},on)
else ifeq (${TARGET_DEBUG},off)
else
 $(error wrong TARGET_BUILD value)
endif




#HDR =
HDR = ${shell find . -type f -name '*.h' ! -path '*/bin/*'} 
#SRC =
SRC = ${shell find . -type f -name '*.c' ! -path '*/bin/*'}
OBJ = ${SRC:.c=.o}

GLOBALDEPS = bin Makefile ${HDR} #${SRC}




ifeq (${TARGET_OS},linux)

 #INCS = -I./
 INCS =

 ifeq (${TARGET_BUILD},dynamic)
  #LIBS = -L./bin/ -l##LIBNAME
  LIBS =
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -L./ -l##LIBNAME -Wl,-Bstatic -Wl,-Bdynamic
  LIBS = ##LIBDIRS ##LIBDEPS
  $(error no defined linux static compilation)
 endif
 
 
 #CFLAGS =
 CFLAGS = ${INCS} -Wall -Wextra -pedantic -std=c89 -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare \
 		  -Ofast3 -pipe -march=native -MJ $@.json -D_REENTRANT
 #LDFLAGS = -v
 LDFLAGS = ${LIBS} -flto=full

 ifeq (${TARGET_DEBUG},on)
  #CFLAGS += -Weverything
  CFLAGS += -g
 endif


else ifeq (${TARGET_OS},windows)

 #INCS = -I./bin/
 INCS = ##INCLUDEDIRS

 ifeq (${TARGET_BUILD},dynamic)
  $(error no defined windows dynamic compilation)
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -Wl,-Bstatic -static-libgcc -lmingw32 -lm -Wl,-Bdynamic
  LIBS = -Wl,-Bstatic -lwsock32 -lws2_32
 endif
 
 
 #CFLAGS =
 CFLAGS = ${INCS} -Wall -Wextra -Wpedantic -std=c89 -O3 -pipe -D_REENTRANT -DWIN32_LEAN_AND_MEAN \
		  -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare
 #LDFLAGS = #-v #-mwindows
 LDFLAGS = ${LIBS}

 ifeq (${TARGET_DEBUG},on)
 endif


#else ifeq (${TARGET_OS},)
endif




${OBJ}:%.o : %.c
	${CC} -c $< -o $@ ${CFLAGS}

${OBJ}: ${GLOBALDEPS}




ifeq (${TARGET_OS},linux)

test: $(TARGET_BIN) compdb
	./$(TARGET_BIN)

bin:
	mkdir bin


else ifeq (${TARGET_OS},windows)

test: ${TARGET_BIN}
#	make clean

bin:
	mkdir bin
#	wget ##BINARYURL -P bin/
#	unzip bin/##BINARYARCHIVE -d bin/
#	rm bin/*.zip -f


#else ifeq (${TARGET_OS},)
endif




all: $(TARGET_BIN)

$(TARGET_BIN): ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

compdb: ${OBJ}
	./compdb.sh

clean:
	rm ${OBJ} -f
	rm ${OBJ:.o=.o.json} -f

update: clean
	rm bin -rf


windows:
	make TARGET_OS=windows TARGET_BUILD=static




.PHONY: default_rule test all clean compdb update windows
