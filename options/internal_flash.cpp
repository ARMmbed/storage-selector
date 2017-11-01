#include "FlashIAPBlockDevice.h"

FlashIAPBlockDevice* _storage_selector_INTERNAL_FLASH() {
    static FlashIAPBlockDevice bd(MBED_CONF_FLASHIAP_BLOCK_DEVICE_BASE_ADDRESS,
                                  MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE);
    return &bd;
}
