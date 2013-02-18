-include DIRS

PRU_SW?=~/am335x_pru_package/pru_sw
CROSS_COMPILE?=arm-arago-linux-gnueabi-
LIBDIR_APP_LOADER?=$(PRU_SW)/app_loader/lib
INCDIR_APP_LOADER?=$(PRU_SW)/app_loader/include
PASM?=$(PRU_SW)/utils/pasm

ASSEM_FILES=test.p

all:
# Make PRU example applications
	#make CROSS_COMPILE="${CROSS_COMPILE}" LIBDIR_APP_LOADER="${LIBDIR_APP_LOADER}" LIBDIR_EDMA_DRIVER="${LIBDIR_EDMA_DRIVER}" INCDIR_APP_LOADER="${INCDIR_APP_LOADER}" INCDIR_EDMA_DRIVER="${INCDIR_EDMA_DRIVER}" 
	for a_file in ${ASSEM_FILES} ; \
	do \
          ${PASM} -b $$a_file ; \
	done ; \


