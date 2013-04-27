#include <stdio.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 1
#define PRU_DATA PRUSS0_PRU1_DATARAM

#define AM33XX

#include <stdint.h>

#include "multiply_pru_mem.h"

void testMult(int32_t a, int32_t b)
{
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
    
    //printf("\nINFO: Starting %s example.\r\n", "multtest");
    /* Initialize the PRU */
    prussdrv_init ();		
    
    /* Open PRU Interrupt */
    ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret)
    {
        printf("prussdrv_open open failed\n");
        return;
    }
    
    /* Get the interrupt initialized */
    prussdrv_pruintc_init(&pruss_intc_initdata);

    uint8_t* pru_data_map;
    prussdrv_map_prumem (PRU_DATA, (void**)&pru_data_map);

    // load parameters
    int32_t p32,p64lo,p64hi;
    int64_t p64;
    
    *((int32_t*)(pru_data_map+A)) = a;
    *((int32_t*)(pru_data_map+B)) = b;

    /* Execute example on PRU */
    //printf("\tINFO: Executing example.\r\n");
    prussdrv_exec_program (PRU_NUM, "./multtest.bin");
    
    /* Wait until PRU0 has finished execution */
    //printf("\tINFO: Waiting for HALT command.\r\n");
    prussdrv_pru_wait_event (PRU_EVTOUT_0);
    //printf("\tINFO: PRU completed transfer.\r\n");
    prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT);

    // check results
    p32 = *((int32_t*)(pru_data_map+OUT32));
    p64lo = *((int32_t*)(pru_data_map+OUT64LO));
    p64hi = *((int32_t*)(pru_data_map+OUT64HI));
    p64 = ((uint64_t)p64hi << 32) | ((uint32_t)p64lo);

    printf("A = %d\nB = %d\n",a,b);
    printf("32 bit result %d (should be %d)\n",p32,a*b);
    printf("64 bit result %lld (should be %lld)\n",p64,(int64_t)a*b);

    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable (PRU_NUM);
    prussdrv_exit ();
}

int main() {
	testMult(100,523);
	testMult(-123,321);
	testMult(214,-23);
	testMult(-3421,-234);
	return 0;
}

