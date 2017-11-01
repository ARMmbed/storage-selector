#include "DataFlashBlockDevice.h"

DataFlashBlockDevice* _storage_selector_DATA_FLASH() {
    static DataFlashBlockDevice bd(MBED_CONF_DATAFLASH_SPI_MOSI,
                                   MBED_CONF_DATAFLASH_SPI_MISO,
                                   MBED_CONF_DATAFLASH_SPI_CLK,
                                   MBED_CONF_DATAFLASH_SPI_CS);
    return &bd;
}
