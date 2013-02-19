-include DIRS

PRU_SW?=/home/root/am335x_pru_package/pru_sw
CROSS_COMPILE?=arm-angstrom-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm

CFLAGS+= -Wall -I$(INCDIR_APP_LOADER) -D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv -lpthread


ASSEM_FILES=encoder.p
TARGET=encoder
OBJ=encoder.o
BIN=encoder.bin

all: $(TARGET)
%.o: %.c $(DEPS)
	$(CROSS_COMPILE)gcc $(CFLAGS) -c -o $@ $< $(LDFLAGS)

%.bin: %.p $(DEPS)
	${PASM} -b $<


$(TARGET): $(OBJ) $(BIN)
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *~ *.bin *.o  $(TARGET)


