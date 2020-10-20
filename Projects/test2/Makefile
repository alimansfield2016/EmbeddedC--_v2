PRJNAME = IlMattoCpp

MMCU = atmega644p

CC = avr-g++
CXX_FLAGS = -Wall -Wextra -Wshadow -std=c++17 -ggdb -mmcu=${MMCU} -D__AVR_ATmega644P__ -DF_CPU=12000000 -O3 -Wall
LD_FLAGS = -L.
LIBS = 

INCLUDEPATH += /home/ali/Projects/EmbeddedC++_v2/avrlibc++/ /usr/lib/avr/include/

INC = ${INCLUDEPATH:%=-I%}

MINOR_BUILD_FILE=.build_nos/minor
INTER_BUILD_FILE=.build_nos/inter
MAJOR_BUILD_FILE=.build_nos/major

MINOR_BUILD_NO = $(shell cat ${MINOR_BUILD_FILE})
INTER_BUILD_NO = $(shell cat ${INTER_BUILD_FILE})
MAJOR_BUILD_NO = $(shell cat ${MAJOR_BUILD_FILE})


SRCEXT = .cpp
OBJEXT = .o
DEPEXT = .d

SRCDIR = src
OBJDIR = obj
DEPDIR = dep

SRC += ${wildcard ${SRCDIR}/**/*${SRCEXT}}\
${wildcard ${SRCDIR}/*${SRCEXT}}
OBJ = ${SRC:${SRCDIR}/%${SRCEXT}=${OBJDIR}/%${OBJEXT}}
DEP = ${SRC:${SRCDIR}/%${SRCEXT}=${DEPDIR}/%${DEPEXT}}




all: prj ${DEP}
	@echo ${SRC}
	@echo ${OBJ}

dep: ${DEP}

${DEPDIR}/%${DEPEXT}:${SRCDIR}/%${SRCEXT}
	@${CC} ${CXX_FLAGS} $< -MM -MT ${@:${DEPDIR}/%${DEPEXT}=${OBJDIR}/%${OBJEXT}}  >$@

obj: ${OBJ}

${OBJDIR}/%${OBJEXT}:${SRCDIR}/%${SRCEXT}
	${CC} ${CXX_FLAGS} -DBUILD_NO=\"${MAJOR_BUILD_NO}.${INTER_BUILD_NO}.${MINOR_BUILD_NO}\" ${INC} -o $@ -c $<



${PRJNAME}: ${OBJ}
	${CC} -mmcu=${MMCU} ${LD_FLAGS} -o $@ $^ ${LIBS:%=-l%}

prj: ${PRJNAME}

hex: ${PRJNAME}
	avr-objcopy -O ihex ${PRJNAME} ${PRJNAME}.hex

bin: ${PRJNAME}
	avr-objcopy -O bin ${PRJNAME} ${PRJNAME}.bin

upload: hex minor
	avrdude -c usbasp -p m644p -U flash:w:${PRJNAME}.hex


.PHONY: clean
clean:
	rm -f ${OBJ} ${DEP} ${PRJNAME}*


# Build number file.  Increment if any object file changes.
minor:
	@if ! test -f $(MINOR_BUILD_FILE); then echo 0 > $(MINOR_BUILD_FILE); fi
	@echo $$(($$(cat $(MINOR_BUILD_FILE)) + 1)) > $(MINOR_BUILD_FILE)

interm: minor
	@echo 0 > ${MINOR_BUILD_FILE}
	@if ! test -f $(INTER_BUILD_FILE); then echo 0 > $(INTER_BUILD_FILE); fi
	@echo $$(($$(cat $(INTER_BUILD_FILE)) + 1)) > $(INTER_BUILD_FILE)

major: interm
	@echo 0 > ${INTER_BUILD_FILE}
	@if ! test -f $(MAJOR_BUILD_FILE); then echo 0 > $(MAJOR_BUILD_FILE); fi
	@echo $$(($$(cat $(MAJOR_BUILD_FILE)) + 1)) > $(MAJOR_BUILD_FILE)