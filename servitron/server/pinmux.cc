#include "pinmux.h"

#include <string>
#include <fstream>

bool writePath(std::string path, int value, bool hex = true) {
    std::ofstream outf;
    outf.open(path.c_str());
    if (hex) { outf << std::hex; }
    outf << value;
    outf.close();
    return true;
}

bool mux::mux_all_pins() {
    // mux all pwm pins
    writePath("/sys/kernel/debug/omap_mux/mcasp0_fsx", 1); // 0:0
    writePath("/sys/kernel/debug/omap_mux/mcasp0_aclkx", 1); // 0:1
    writePath("/sys/kernel/debug/omap_mux/gpmc_a2", 6); // 1:0
    writePath("/sys/kernel/debug/omap_mux/gpmc_a3", 6); // 1:1
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad8", 4); // 2:0
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad9", 4); // 2:1
    // mux brake
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad10", 0x0f);
    // mux quadrature pins
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad6", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad7", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad2", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad3", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad13", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad12", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad15", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad14", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_csn2", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_csn1", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad5", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad4", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad1", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ad0", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_cns0", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_ben1", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_a0", 0x3f);
    writePath("/sys/kernel/debug/omap_mux/gpmc_a1", 0x3f);
    return true;
}

