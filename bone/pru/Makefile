-include DIRS

PRU_SW?=~/am335x_pru_package/pru_sw
CROSS_COMPILE?=arm-arago-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm

CFLAGS+= -Wall -I$(INCDIR_APP_LOADER) -D__DEBUG -O2 -mtune=cortex-a8 -march=armv
7-a
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv -lpthread
OBJDIR=obj

ASSEM_FILES=test.p


$(OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p obj
	$(CROSS_COMPILE)gcc $(CFLAGS) -c -o $@ $< 

$(TARGET): $(OBJ)
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/ *~  $(INCDIR_APP_LOADER)/*~  $(TARGET)

all: test
# Make PRU example applications
	for a_file in ${ASSEM_FILES} ; \
	do \
          ${PASM} -b $$a_file ; \
	done ; \


