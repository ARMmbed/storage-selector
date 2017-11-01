#include "SPIFBlockDevice.h"

SPIFBlockDevice* _storage_selector_SPIFLASH() {
    static SPIFBlockDevice bd(MBED_CONF_SPIF_DRIVER_SPI_MOSI, MBED_CONF_SPIF_DRIVER_SPI_MISO, MBED_CONF_SPIF_DRIVER_SPI_CLK, MBED_CONF_SPIF_DRIVER_SPI_CS);
    return &bd;
}
