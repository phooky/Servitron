-include DIRS

PRU_SW?=/home/root/am335x_pru_package/pru_sw
CROSS_COMPILE?=arm-angstrom-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm

CFLAGS+= -Wall -I$(INCDIR_APP_LOADER) -D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv -lpthread


TARGETS=brake_test motor_test pwm_test quad_test servo_test quad.bin
BIN=

all: $(TARGETS) $(BIN)
%.o: %.c $(DEPS)
	$(CROSS_COMPILE)gcc $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.o: %.cc $(DEPS)
	$(CROSS_COMPILE)g++ $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.bin: %.p $(DEPS)
	${PASM} -b $<


pwm_test: pwm_test.o pwm.o util.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

quad_test: quad_test.o quadrature.o util.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

motor_test: motor_test.o motor.o util.o pwm.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS)

servo_test: servo_test.o servo.o pid.o motor.o pwm.o util.o quadrature.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

brake_test: brake_test.o brake.o
	$(CROSS_COMPILE)g++ $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

.PHONY: clean

clean:
	rm -f *~ *.bin *.o  $(TARGET)


