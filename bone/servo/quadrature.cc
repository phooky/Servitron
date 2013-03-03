#include "quadrature.h"
#include "config.h"
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <stdio.h>
#include "util.h"

#define PRU_NUM 0

#include "json/JSONValue.h"

std::string inputPinNames[] = {
  "gpmc_ad6",
  "gpmc_ad7",
  "gpmc_ad2",
  "gpmc_ad3",
  "gpmc_ad13",
  "gpmc_ad12",
  "gpmc_ad15",
  "gpmc_ad14",
  "gpmc_csn2",
  "gpmc_csn1",
  "gpmc_ad5",
  "gpmc_ad4",
  "gpmc_ad1",
  "gpmc_ad0",
  "gpmc_cns0",
  "gpmc_ben1",
  "gpmc_a0",
  "gpmc_a1",
  ""
};

Quadrature::Quadrature() : pru_data_map((uint8_t*)-1) {
}

void Quadrature::initChannel(uint8_t ch, uint8_t a, uint8_t b, uint8_t idx) {
  QuadState* qs = (QuadState*)(pru_data_map + QUAD_STATE_BASE);
  qs += ch;
  qs->position = 0;
  qs->state = 0;
  qs->pinA = a;
  qs->pinB = b;
  qs->pinIdx = idx;
  qs->errors = 0;
}

void Quadrature::init() {
    unsigned int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    // The muxing. Oh, the muxing.
    std::string *namesIter = inputPinNames;
    while (! namesIter->empty()) {
      writePath(std::string("/sys/kernel/debug/omap_mux/")+*namesIter, 0x3f);
      namesIter++;
    }

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

    prussdrv_map_prumem (PRUSS0_PRU0_DATARAM, (void**)&pru_data_map);
    initChannel(0, Q0A, Q0B, Q0I);
    initChannel(1, Q1A, Q1B, Q1I);
    initChannel(2, Q2A, Q2B, Q2I);
    initChannel(3, Q3A, Q3B, Q3I);
    initChannel(4, Q4A, Q4B, Q4I);
    initChannel(5, Q5A, Q5B, Q5I);

    /* Set update period */
    *(uint32_t*)(pru_data_map + CYCLE_COUNT_BASE) = 0x30d40; // 0xbebc200;

    /* Execute quadrature peripheral on PRU */
    prussdrv_exec_program (PRU_NUM, "./quad.bin");
}

Report Quadrature::getNextReport() {

    /* Wait until PRU0 has finished execution */
    prussdrv_pru_wait_event (PRU_EVTOUT_0);
    QuadState* qs = (QuadState*)(pru_data_map + QUAD_STATE_BASE);
    Report r = *((Report*)(pru_data_map + QUAD_STATE_BASE));// REPORT_BASE));
    prussdrv_pru_clear_event (PRU0_ARM_INTERRUPT);

    return r;
}

void Quadrature::shutdown() {
    /* Disable PRU and close memory mapping*/
    prussdrv_pru_disable (PRU_NUM);
    prussdrv_exit ();
}
