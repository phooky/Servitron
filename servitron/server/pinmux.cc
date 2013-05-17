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

    return true;
}

