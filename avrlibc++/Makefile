NAME = libc++.a

SRCDIR = source
ASMDIR = ${SRCDIR}
OBJDIR = objects


INCDIR += ./headers

WARNINGS += no-pointer-arith
DEFINES += __AVR_ATmega644P__ F_CPU=12000000

COMPILE = avr-gcc
CPP_COMPILE_FLAGS = -std=c++20 -O3 -c ${INCDIR:%=-I%} ${WARNINGS:%=-W%} ${DEFINES:%=-D%}
C_COMPILE_FLAGS = -O3 -c ${INCDIR:%=-I%} ${WARNINGS:%=-W%} ${DEFINES:%=-D%}

ARCHIVE = avr-ar

CPPSRCEXT = cpp
CSRCEXT = c
ASMEXT = S
OBJEXT = o


CPPSRC += ${wildcard ${SRCDIR}/*.${CPPSRCEXT}}
CPPSRC += ${wildcard ${SRCDIR}/**/*.${CPPSRCEXT}}
CPPSRC += ${wildcard ${SRCDIR}/**/**/*.${CPPSRCEXT}}
CPPSRC += ${wildcard ${SRCDIR}/**/**/**/*.${CPPSRCEXT}}
CPPSRC += ${wildcard ${SRCDIR}/**/**/**/**/*.${CPPSRCEXT}}

CSRC += ${wildcard ${SRCDIR}/*.${CSRCEXT}}
CSRC += ${wildcard ${SRCDIR}/**/*.${CSRCEXT}}
CSRC += ${wildcard ${SRCDIR}/**/**/*.${CSRCEXT}}
CSRC += ${wildcard ${SRCDIR}/**/**/**/*.${CSRCEXT}}
CSRC += ${wildcard ${SRCDIR}/**/**/**/**/*.${CSRCEXT}}

ASM += ${wildcard ${ASMDIR}/*.${ASMEXT}}
ASM += ${wildcard ${ASMDIR}/**/*.${ASMEXT}}
ASM += ${wildcard ${ASMDIR}/**/**/*.${ASMEXT}}
ASM += ${wildcard ${ASMDIR}/**/**/**/*.${ASMEXT}}
ASM += ${wildcard ${ASMDIR}/**/**/**/**/*.${ASMEXT}}


OBJ += ${CPPSRC:${SRCDIR}%.${CPPSRCEXT}=${OBJDIR}%.${OBJEXT}}
OBJ += ${CSRC:${SRCDIR}%.${CSRCEXT}=${OBJDIR}%.${OBJEXT}}
OBJ += ${ASM:${ASMDIR}%.${ASMEXT}=${OBJDIR}%.${OBJEXT}}

all: ${NAME}

debug:
	@echo "CPPSRC:"
	@echo ${CPPSRC}
	@echo "CSRC:"
	@echo ${CSRC}
	@echo "ASM:"
	@echo ${ASM}
	@echo "OBJ:"
	@echo ${OBJ}

Cobj: ${PPSRC}

${OBJDIR}/%.${OBJEXT}: ${ASMDIR}/%.${ASMEXT}
	${COMPILE} ${CPP_COMPILE_FLAGS} -o $@ $<
${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${CPPSRCEXT}
	${COMPILE} ${CPP_COMPILE_FLAGS} -o $@ $<
${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${CSRCEXT}
	${COMPILE} ${C_COMPILE_FLAGS} -o $@ $<


${NAME}: ${OBJ}
	@echo "OBJ:"
	@echo ${OBJ}

	${ARCHIVE} rcs -o $@ $^

clean:
	rm -rf ${NAME} ${OBJ} 


