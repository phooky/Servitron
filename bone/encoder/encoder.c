#include <stdio.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <stdint.h>

#define PRU_NUM 	0
#define AM33XX

typedef struct {
  uint32_t position;
  uint8_t idxA;
  uint8_t idxB;
  uint8_t idxIdx;
  uint8_t state;
  uint16_t errCount;
} __attribute__((packed)) Channel;

#define CHANNEL_COUNT 6

void init(Channel* ch, uint8_t idxA, uint8_t idxB, uint8_t idxIdx) {
  ch->position = 0;
  ch->idxA = idxA;
  ch->idxB = idxB;
  ch->idxIdx = idxIdx;
  ch->errCount = 0;
}

int main (void)
{
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
    static void *pruDataMem;
    Channel* channels;

    printf("\nINFO: Starting %s example.\r\n", "blink");
    /* Initialize the PRU */
    prussdrv_init ();		
    
    /* Open PRU Interrupt */
    ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return (ret);
    }
    
    /* Get the interrupt initialized */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    prussdrv_map_prumem (PRUSS0_PRU0_DATARAM, &pruDataMem);
    channels = (Channel*)pruDataMem;
    init(channels+0, 16, 17, 16);
    init(channels+1, 16, 17, 16);
    init(channels+2, 16, 17, 16);
    init(channels+3, 16, 17, 16);
    init(channels+4, 16, 17, 16);
    init(channels+5, 16, 17, 16);
    init(channels+6, 16, 17, 16);
    init(channels+7, 16, 17, 16);

    /* Execute example on PRU */
    printf("\tINFO: Executing example.\r\n");
    prussdrv_exec_program (PRU_NUM, "./encoder.bin");
    
    /* Wait until PRU0 has finished execution */
    printf("\tINFO: Waiting for HALT command.\r\n");
    prussdrv_pru_wait_event (PRU_EVTOUT_0);
    printf("\tINFO: PRU completed transfer.\r\n");
    prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT);
int i;
    for (i = 0; i < CHANNEL_COUNT; i++) {
      printf("\tENCODER %d VALUE %d ERRORS %d\r\n",i,channels[i].position,channels[i].errCount);
    }

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable (PRU_NUM);
    prussdrv_exit ();

    return(0);
}

