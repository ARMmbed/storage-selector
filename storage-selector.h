#ifndef _STORAGE_SELECTOR_H_
#define _STORAGE_SELECTOR_H_

#include "options/sd_card.h"
#include "options/heap.h"
#include "options/spi_flash.h"
#include "options/data_flash.h"
#include "options/internal_flash.h"

// These two macros are a bit of magic that concatinate the symbol and
// function prefix to create a valid function name
#define _STORAGE_SELECTOR_concat(dev) _storage_selector_##dev()
#define _STORAGE_SELECTOR(dev) _STORAGE_SELECTOR_concat(dev)

BlockDevice* storage_selector() {
    return _STORAGE_SELECTOR(MBED_CONF_STORAGE_SELECTOR_STORAGE);
}

#endif //_STORAGE_SELECTOR_H_
