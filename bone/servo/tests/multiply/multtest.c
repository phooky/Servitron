#include <stdio.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 1
#define PRU_DATA PRUSS0_PRU1_DATARAM

#define AM33XX

#include <stdint.h>

#include "pru_mem.h"

int main (void)
{
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
    
    printf("\nINFO: Starting %s example.\r\n", "multtest");
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

    void* pru_data_map;
    prussdrv_map_prumem (PRU_DATA, &pru_data_map);

    /* Set update period */
    *(uint32_t*)(pru_data_map + CYCLE_COUNT_BASE) = 0x30d40; // 0xbebc200;

    // load parameters
    int32_t a;
    int32_t b;
    int32_t p32;
    int64_t p64;

    
    *((*int32)(pru_data_map+A)) = a;
    *((*int32)(pru_data_map+B)) = b;

    /* Execute example on PRU */
    printf("\tINFO: Executing example.\r\n");
    prussdrv_exec_program (PRU_NUM, "./multtest.bin");
    
    /* Wait until PRU0 has finished execution */
    printf("\tINFO: Waiting for HALT command.\r\n");
    prussdrv_pru_wait_event (PRU_EVTOUT_0);
    printf("\tINFO: PRU completed transfer.\r\n");
    prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT);

    // check results
    p32 = *((*int32)(pru_data_map+OUT16));
    p64 = *((*int32)(pru_data_map+OUT32HI));
    p64 <<= 32;
    p64 += *((*int32)(pru_data_map+OUT32LO));

    printf("A = %d\nB = %d\n",a,b);
    printf("32 bit result %d (should be %d)\n",p32,a*b);
    printf("64 bit result %lld (should be %lld)\n",p64,(int64)a*b);

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable (PRU_NUM);
    prussdrv_exit ();

    return(0);
}
