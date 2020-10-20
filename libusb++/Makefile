PROGRAM = libusb++


LIBEXT = a
SRCEXT = cpp
CSRCEXT = c
OBJEXT = o

ASMEXT = S
SRCDIR = src
SRC += ${wildcard ${SRCDIR}/*.${SRCEXT}}
SRC += ${wildcard ${SRCDIR}/**/*.${SRCEXT}}
CSRC += ${wildcard ${SRCDIR}/*.${CSRCEXT}}
CSRC += ${wildcard ${SRCDIR}/**/*.${CSRCEXT}}
ASM += ${wildcard ${SRCDIR}/*.${ASMEXT}}
ASM += ${wildcard ${SRCDIR}/**/*.${ASMEXT}}

OBJDIR = obj
OBJ += ${SRC:${SRCDIR}/%.${SRCEXT}=${OBJDIR}/%.${OBJEXT}}
OBJ += ${CSRC:${SRCDIR}/%.${CSRCEXT}=${OBJDIR}/%.${OBJEXT}}
OBJ += ${ASM:${SRCDIR}/%.${ASMEXT}=${OBJDIR}/%.${OBJEXT}}

INCLUDEPATH += ./hdr/ /home/ali/Projects/EmbeddedC++_v2/avrlibc++/headers/

COMPILE = avr-gcc-5.4.0
ARCHIVE = avr-ar

STANDARD = c++17
OPTIMISATION = 3

MMCU = atmega644p
CLOCk_FREQ = 12000000

DEFINES += F_CPU=${CLOCk_FREQ}

COMPILE_FLAGS += -c ${INCLUDEPATH:%=-I%} -O${OPTIMISATION} -mmcu=${MMCU}  -ggdb ${DEFINES:%=-D%}
CPP_COMPILE_FLAGS += -std=${STANDARD}  ${COMPILE_FLAGS}
CPP_COMPILE_FLAGS += ${COMPILE_FLAGS}
ASM_FLAGS += -c ${DEFINES:%=-D%} -mmcu=${MMCU}
ARCHIVE_FLAGS += rcs


debug:
	@echo "SRC:"
	@echo ${SRC}
	@echo "OBJ:"
	@echo ${OBJ}



${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${ASMEXT}
	${COMPILE} ${ASM_FLAGS} -o $@ $<
${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${SRCEXT}
	${COMPILE} ${CPP_COMPILE_FLAGS} -o $@ $<
${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${CSRCEXT}
	${COMPILE} ${C_COMPILE_FLAGS} -o $@ $<




${PROGRAM}.${LIBEXT}: ${OBJ}
	${ARCHIVE} ${ARCHIVE_FLAGS} $@ $^

lib: ${PROGRAM}.${LIBEXT}


clean:
	rm -rf ${PROGRAM}* ${OBJ}