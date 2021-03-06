
PROGRAM = USBSerial



ASMDIR = asm
OBJDIR = obj
SRCDIR = src

SRCEXT = cpp
ASMEXT = s
OBJEXT = o


SRC += ${wildcard ${SRCDIR}/**/*.${SRCEXT}}\
${wildcard ${SRCDIR}/*.${SRCEXT}}
ASM = ${SRC:${SRCDIR}/%.${SRCEXT}=${ASMDIR}/%.${ASMEXT}}
OBJ = ${ASM:${ASMDIR}/%.${ASMEXT}=${OBJDIR}/%.${OBJEXT}}

OBJ += /usr/lib/avr/lib/avr5/crtatmega644p.o

WARNINGS += all pedantic extra shadow no-overflow #no-volatile
STANDARD = c++17
OPTIMISATION = 2
DEFINES += __AVR_ATmega644P__ F_CPU=12000000 #ENABLE_INTERRUPTS
INCLUDEPATH += /home/ali/Projects/EmbeddedC++_v2/avrlibc++/headers/ /usr/lib/avr/include/ ../../../libusb++/hdr/
INC = ${INCLUDEPATH:%=-I%}
LIBDIR += . /usr/local/avr/lib/avr5/ ../../../avrlibc++/ ../../../libusb++/
LIBRARIES += atmega644p c c++ 
WHOLE_LIBRARIES += usb++
LIB = ${LIBDIR:%=-L%} ${LIBRARIES:%=-l%} -Wl,--whole-archive ${WHOLE_LIBRARIES:%=-l%} -Wl,--no-whole-archive

COMPILE_FLAGS = -c -std=${STANDARD} ${WARNINGS:%=-W%} -O${OPTIMISATION} ${INC} ${DEFINES:%=-D%} -ggdb
ASSEMBLE_FLAGS = -c -mmcu=atmega644p
LINK_FLAGS = ${LIB}

COMPILE = avr-gcc-10.1.0
ASSEMBLE = avr-as
LINK = avr-gcc-5.4.0



all: ${PROGRAM}


debug:
	@echo "SRC:"
	@echo ${SRC}
	@echo "OBJ:"
	@echo ${OBJ}



#make assembly files
obj: ${OBJ}
${OBJDIR}/%.${OBJEXT}: ${SRCDIR}/%.${SRCEXT}
	${COMPILE} ${COMPILE_FLAGS} -o $@ $<

asm: ${ASM}
${ASMDIR}/%.${ASMEXT}: ${SRCDIR}/%.${SRCEXT}
	${COMPILE} -S ${COMPILE_FLAGS} -o $@ $<


#make executeable file
# ${PROGRAM}: ${OBJ}
	# ${LINK}  -o $@ $< /usr/lib/avr/lib/avr5/crtatmega644p.o ${LINK_FLAGS}

${PROGRAM}: ${OBJ}
	${LINK}  -o $@ $< /usr/lib/avr/lib/avr5/crtatmega644p.o ${LINK_FLAGS}

hex: ${PROGRAM}
	avr-objcopy -O ihex ${PROGRAM} ${PROGRAM}.hex

upload: hex
	avrdude -c usbasp -p m644p -U flash:w:${PROGRAM}.hex


clean:
	rm -rf ${ASMDIR}/* ${OBJDIR}/* ${PROGRAM}

size: ${PROGRAM}

nm: ${PROGRAM}
	avr-nm -C -S --size-sort -t d $<