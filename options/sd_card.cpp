#include "SDBlockDevice.h"

SDBlockDevice* _storage_selector_SDCARD() {
    static SDBlockDevice bd(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK, MBED_CONF_SD_SPI_CS);
    return &bd;
}
