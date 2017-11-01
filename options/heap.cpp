#include "HeapBlockDevice.h"

HeapBlockDevice* _storage_selector_HEAP() {
    static HeapBlockDevice bd(MBED_CONF_STORAGE_SELECTOR_HEAP_SIZE);
    return &bd;
}
