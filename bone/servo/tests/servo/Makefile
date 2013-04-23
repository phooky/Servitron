-include DIRS

PRU_SW?=/home/root/am335x_pru_package/pru_sw
CROSS_COMPILE?=arm-angstrom-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm.arm7l

CFLAGS+= -Wall -I../.. -I$(INCDIR_APP_LOADER) -D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv -lpthread


TARGETS=servo_test 
BIN=../../quad.bin

all: $(TARGETS) $(BIN)
%.o: %.c $(DEPS)
	$(CROSS_COMPILE)gcc $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.o: %.cc $(DEPS)
	$(CROSS_COMPILE)g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.bin: %.p $(DEPS)
	${PASM} -b $<

servo_test: servo_test.o ../../pwm.o ../../brake.o ../../motor.o  ../../quadrature.o ../../util.o ../../servo.o ../../pid.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *~ *.bin *.o  $(TARGET)


