-include DIRS

MACHINE=$(shell sh -c 'uname -m')

ifeq ($(MACHINE),armv7l)
	PLATFORM=arm
	CFLAGS+=-mtune=cortex-a8 -march=armv7-a
endif
ifeq ($(MACHINE),x86_64)
	PLATFORM=x86
endif

PLATFORM?=$(MACHINE)

PRU_SW?=../am335x_pru_package/pru_sw
#CROSS_COMPILE?=arm-angstrom-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm_2.$(PLATFORM)
GPP=g++
GCC=gcc

CFLAGS+= -Wall -I$(INCDIR_APP_LOADER) -D__DEBUG -O2 
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv -lpthread


TARGETS=quad.bin quad_test brake_test motor_test #pwm_test quad_test servo_test quad.bin
BIN=

all: $(TARGETS) $(BIN)
%.o: %.c $(DEPS)
	$(GPP) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.o: %.cc $(DEPS)
	$(GPP) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.bin: %.p $(DEPS)
	$(PASM) -V2 -b $<


pwm_test: pwm_test.o pwm.o util.o
	$(GPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

quad_test: quad_test.o quadrature.o util.o
	$(GPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

motor_test: motor_test.o motor.o util.o pwm.o
	$(GPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)

servo_test: servo_test.o servo.o pid.o motor.o pwm.o util.o quadrature.o
	$(GPP) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

brake_test: brake_test.o brake.o util.o
	$(GPP) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

.PHONY: clean

clean:
	rm -f *~ *.bin *.o  $(TARGET)


