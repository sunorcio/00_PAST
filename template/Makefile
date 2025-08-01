



default: test


#[linux^windows]
TARGET_OS = linux
#[dynamic^static]
TARGET_LINK = dynamic
#[incremental^unified]
TARGET_BUILD = incremental

#[off^on]
TARGET_RELEASE = off
#[off^on]
TARGET_DEBUG = off
#[off^on]
TARGET_SANITIZE = off

#[string], binary name
TARGET_BIN = ##BINARYNAME


# /\ /\ MAKEFILE CONFIGURATION /\ /\
# || ||                        || ||
# rules are at the bottom of this file




ifeq (${TARGET_OS}, linux)
else ifeq (${TARGET_OS}, windows)
else
 $(error wrong TARGET_OS value)
endif

ifeq (${TARGET_LINK}, dynamic)
else ifeq (${TARGET_LINK}, static)
else
 $(error wrong TARGET_LINK value)
endif

ifeq (${TARGET_BUILD}, incremental)
else ifeq (${TARGET_BUILD}, unified)
else
 $(error wrong TARGET_BUILD value)
endif

ifeq (${TARGET_RELEASE}, on)
else ifeq (${TARGET_RELEASE}, off)
else
 $(error wrong TARGET_RELEASE value)
endif

ifeq (${TARGET_DEBUG}, on)
else ifeq (${TARGET_DEBUG}, off)
else
 $(error wrong TARGET_DEBUG value)
endif

ifeq (${TARGET_SANITIZE}, on)
else ifeq (${TARGET_SANITIZE}, off)
else
 $(error wrong TARGET_SANITIZE value)
endif




#GLOBALDEP = Makefile
GLOBALDEP = ##FILES_THAT_FORCE_RECOMPILATION
#AUTORULE = bin compdb
AUTORULE = ##RULES_THAT_RUN_EVERYTIME


ifeq (${TARGET_BUILD}, incremental)

# #HDR = ${shell find . -type f -name '*.h' ! -path '*/bin/*'}
#HDR =
#SRC = ${shell find . -type f -name '*.c' ! -path '*/bin/*' ! -name 'all.c'}
SRC = ##LOCAL_SOURCES
#DEP = ${shell find . -type f -name '*.d' ! -path '*/bin/*'}
DEP = ##LOCAL_SOURCE_DEPS
OBJ = ${SRC:.c=.o}


else ifeq (${TARGET_BUILD}, unified)

SRC = all.c
OBJ = ${SRC:.c=.o}

all.c:
	find . -type f -name '*.c' ! -path '*/bin/*' > all.c.temp
	sed -e 's/\.\///' all.c.temp > all.c1.temp
	sed -e 's/.*/#include "&"/' all.c1.temp > all.c
	rm *.temp -f


endif




ifeq (${TARGET_OS},linux)

 #CC = clang
 CC = ##COMPILER/LINKER

 #INCS = -I./
 INCS = ##INCLUDEDIRS

 ifeq (${TARGET_BUILD},dynamic)
  #LIBS = -L./ -l##LIBNAME -lm
  LIBS = ##LIBDIRS ##LIBDEPS
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -Wl,-Bstatic ##STATIC_LIBS -Wl,-Bdynamic ##DYNAMIC_LIBS
  LIBS = ##LIBDIRS ##LIBDEPS
 endif
 
 
 #CFLAGS = -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare -Wno-unsafe-buffer-usage -std=c99 -D_REENTRANT
 CFLAGS = ${INCS}
 #LDFLAGS = -v
 LDFLAGS = ${LIBS}


 ifeq (${TARGET_BUILD}, incremental)
  #CFLAGS += -MMD -MF ${@:.o=.d} -MJ $@.json
  CFLAGS +=
  #LDFLAGS +=
  LDFLAGS +=
 endif

 ifeq (${TARGET_RELEASE}, on)
  #CFLAGS += -O3 -ffast-math -pipe -march=native -march=x86-64
  CFLAGS +=
  #LDFLAGS += -flto=full
  LDFLAGS +=
 endif

 ifeq (${TARGET_DEBUG}, on)
  #CFLAGS += -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
  CFLAGS +=
  #LDFLAGS +=
  LDFLAGS +=
 endif

 ifeq (${TARGET_SANITIZE}, on)
  #CFLAGS += -Weverything -Werror -std=c89 -fsanitize=undefined -fsanitize=address
  CFLAGS +=
  #LDFLAGS += -fsanitize=undefined -fsanitize=address
  LDFLAGS +=
 endif


else ifeq (${TARGET_OS},windows)

 #CC = x86_64-w64-mingw32-gcc
 CC = ##COMPILER/LINKER

 #INCS = -I./bin/
 INCS = ##INCLUDEDIRS

 ifeq (${TARGET_BUILD},dynamic)
  #LIBS = -L./bin/ -l##LIBNAME
  LIBS = ##LIBDIRS ##LIBDEPS
  $(error no defined windows dynamic compilation)
 else ifeq (${TARGET_BUILD},static)
  #LIBS = -Wl,-Bstatic ##STATIC_LIBS -static-libgcc -lmingw32 -lm -Wl,-Bdynamic ##DYNAMIC_LIBS
  LIBS = ##LIBDIRS ##LIBDEPS
 endif
 
 
 #CFLAGS = -D_REENTRANT -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wno-sign-compare -Wno-old-style-declaration -std=c99
 CFLAGS = ${INCS} -DWIN32_LEAN_AND_MEAN
 #LDFLAGS = -v -mwindows
 LDFLAGS = ${LIBS}


 ifeq (${TARGET_RELEASE}, on)
  #CFLAGS += -O3 -ffast-math -pipe
  CFLAGS +=
  #LDFLAGS +=
  LDFLAGS +=
 endif

 ifeq (${TARGET_DEBUG}, on)
  #CFLAGS += -g -fno-omit-frame-pointer
  CFLAGS +=
  #LDFLAGS +=
  LDFLAGS +=
 endif

 ifeq (${TARGET_SANITIZE}, on)
  #CFLAGS += -Weverything -Werror -std=c89
  CFLAGS +=
  #LDFLAGS +=
  LDFLAGS +=
 endif


#else ifeq (${TARGET_OS},)
endif




include ${DEP}

${OBJ}: ${GLOBALDEP}

${OBJ}: %.o : %.c
	${CC} -c $< -o $@ ${CFLAGS}




ifeq (${TARGET_OS}, linux)

#bin:
#	mkdir bin


else ifeq (${TARGET_OS}, windows)

#bin:
#	mkdir bin
	##GET_BINARIES
	#wget ##BINARYURL -P bin/
	#unzip bin/##BINARYARCHIVE -d bin/
	#rm bin/*.zip -f


endif




${TARGET_BIN}: ${AUTORULE} ${OBJ}
	${CC} -o $@.out ${OBJ} ${LDFLAGS}


clean:
	rm ${OBJ} -f

deepclean:
	rm ${TARGET_BIN}.out ${TARGET_BIN}.exe a.out -f
	rm ${shell find . -type f -name '*.o' ! -path '*/bin/*'} -f
	#rm ${shell find . -type f -name '*.d' ! -path '*/bin/*'} -f
	#rm ${shell find . -type f -name '*.o.json' ! -path '*/bin/*'} -f
	#rm perf.* -f

#update: deepclean
#	rm bin -rf

#compdb: ${OBJ}
#	sed -e '1s/^/[\n/' -e '$$s/,$$/\n]/' ${shell find . -type f -name "*.o.json" ! -path '*/bin/*'} > compile_commands.json

#flamegraph:
#	su -c "perf record -F 999 -g --call-graph dwarf ./a.out; perf script | /opt/FlameGraph/stackcollapse-perf.pl > perf.fold; /opt/FlameGraph/flamegraph.pl perf.fold > perf.svg"

test: ${TARGET_BIN}
	./${TARGET_BIN}.out

debug: clean
	make a TARGET_BIN=a TARGET_DEBUG=on clean

sanitize: clean
	make a TARGET_BIN=a TARGET_SANITIZE=on clean

release:
	make clean ${TARGET_BIN} TARGET_OS=linux TARGET_LINK=static TARGET_BUILD=unified TARGET_RELEASE=on

#windows:
#	make clean ${TARGET_BIN} TARGET_OS=windows TARGET_LINK=static TARGET_BUILD=unified TARGET_RELEASE=on




.PHONY: default clean deepclean update compdb flamegraph test debug sanitize release windows
