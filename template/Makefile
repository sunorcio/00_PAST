



#(linux^)
TARGET_OS = linux
#(dynamic^static)
TARGET_BUILD = dynamic
#(on^off)
TARGET_DEBUG = off
#(off^on)
TARGET_SANITIZE = off
#(binary name string)
TARGET_BIN = ##BINARY_NAME




default_rule: test




ifeq (${TARGET_OS},linux)
 #CC = clang
 CC = ##COMPILER/LINKER
#else ifeq (${TARGET_OS},windows)
# CC = x86_64-w64-mingw32-gcc
#else ifeq (${TARGET_OS},)
else
 $(error wrong TARGET_OS value)
endif

ifeq (${TARGET_BUILD},dynamic)
#else ifeq (${TARGET_BUILD},static)
else
 $(error wrong TARGET_BUILD value)
endif

ifeq (${TARGET_DEBUG},on)
else ifeq (${TARGET_DEBUG},off)
else
 $(error wrong TARGET_DEBUG value)
endif

ifeq (${TARGET_SANITIZE},on)
else ifeq (${TARGET_SANITIZE},off)
else
 $(error wrong TARGET_SANITIZE value)
endif




#GLOBALDEP = Makefile
GLOBALDEP = #files that force total recompile
#AUTORULE = bin compdb
AUTORULE = #rules to run each compilation

# #HDR = ${shell find . -type f -name '*.h' ! -path '*/bin/*'}
#HDR =
#SRC = ${shell find . -type f -name '*.c' ! -path '*/bin/*'}
SRC = ##LOCAL_SOURCES
#DEP = ${shell find . -type f -name '*.d' ! -path '*/bin/*'}
DEP = ##LOCAL_SOURCE_DEPS
OBJ = ${SRC:.c=.o}




ifeq (${TARGET_OS},linux)

 #INCS = -I./
 INCS = ##INCLUDEDIRS

 ifeq (${TARGET_BUILD},dynamic)
  #LIBS = -L./ -l##LIBNAME -lm
  LIBS = ##LIBDIRS ##LIBDEPS
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -L./ -l##LIBNAME -Wl,-Bstatic -Wl,-Bdynamic
  LIBS = ##LIBDIRS ##LIBDEPS
  $(error no defined linux static compilation)
 endif
 
 
 #CFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare -Wno-unsafe-buffer-usage -std=c99 -O3 -ffast-math -pipe -march=native -MMD -MF ${@:.o=.d} -MJ $@.json -D_REENTRANT
 CFLAGS = ${INCS}
 #LDFLAGS = -flto=full -v
 LDFLAGS = ${LIBS}

 ifeq (${TARGET_DEBUG},on)
  #CFLAGS += -DISOLA_DBG
  CFLAGS += -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
  #LDFLAGS +=
  LDFLAGS +=
 endif

 ifeq (${TARGET_SANITIZE},on)
  #CFLAGS += -Weverything -Werror -std=c89
  CFLAGS += -fsanitize=undefined -fsanitize=address
  #LDFLAGS +=
  LDFLAGS += -fsanitize=undefined -fsanitize=address
 endif


else ifeq (${TARGET_OS},windows)

 #INCS = -I./bin/
 INCS = ##INCLUDEDIRS

 ifeq (${TARGET_BUILD},dynamic)
  #LIBS = -L./bin/ -l##LIBNAME
  LIBS = ##LIBDIRS ##LIBDEPS
  $(error no defined windows dynamic compilation)
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -L./bin/ -l##LIBNAME -Wl,-Bstatic -static-libgcc -lmingw32 -lm -Wl,-Bdynamic
  LIBS = ##LIBDIRS ##LIBDEPS
 endif
 
 
 #CFLAGS = -Werror -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare -Wno-old-style-declaration -std=c99 -O3 -ffast-math -pipe -D_REENTRANT
 CFLAGS = ${INCS} -DWIN32_LEAN_AND_MEAN
 #LDFLAGS = #-v #-mwindows
 LDFLAGS = ${LIBS}

 ifeq (${TARGET_DEBUG},on)
 endif


#else ifeq (${TARGET_OS},)
endif




include ${DEP}

${OBJ}: ${GLOBALDEP}

${OBJ}: %.o : %.c
	${CC} -c $< -o $@ ${CFLAGS}




ifeq (${TARGET_OS},linux)

test: $(TARGET_BIN)
	./$(TARGET_BIN).out

#bin:
#	mkdir bin


#else ifeq (${TARGET_OS},windows)
#
#test: ${TARGET_BIN}
#
#bin:
#	mkdir bin
#	wget ##BINARYURL -P bin/
#	unzip bin/##BINARYARCHIVE -d bin/
#	rm bin/*.zip -f
 

#else ifeq (${TARGET_OS},)
endif




all: $(TARGET_BIN)

$(TARGET_BIN): ${AUTORULE} ${OBJ}
	${CC} -o $@.out ${OBJ} ${LDFLAGS}

clean:
	rm ${OBJ} -f

deepclean:
	rm perf.data* -f
	rm ${TARGET_BIN}.out ${TARGET_BIN}.exe a.out -f
	rm ${shell find . -type f -name '*.o' ! -path '*/bin/*'} -f
	rm ${shell find . -type f -name '*.d' ! -path '*/bin/*'} -f
	rm ${shell find . -type f -name '*.o.json' ! -path '*/bin/*'} -f

#update: deepclean
#	rm bin -rf

#compdb: ${OBJ}
#	sed -e '1s/^/[\n/' -e '$$s/,$$/\n]/' ${shell find . -type f -name "*.o.json" ! -path '*/bin/*'} > compile_commands.json

#debug: clean
#	make a TARGET_BIN=a TARGET_DEBUG=on clean

#sanitize: clean
#	make ${TARGET_BIN} TARGET_SANITIZE=on clean

#windows:
#	make TARGET_OS=windows TARGET_BUILD=static




.PHONY: default_rule test all clean deepclean update debug sanitize compdb windows
