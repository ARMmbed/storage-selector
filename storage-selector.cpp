/* mbed Microcontroller Library
 * Copyright (c) 2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "storage-selector.h"
#include "options/sd_card.h"
#include "options/heap.h"
#include "options/spi_flash.h"
#include "options/data_flash.h"
#include "options/internal_flash.h"
#include "options/fat_filesystem.h"
#include "options/little_filesystem.h"

using mbed::BlockDevice;

// These two macros are a bit of magic that concatinate the symbol and
// function prefix to create a valid function name
#define _STORAGE_SELECTOR_concat(dev) _storage_selector_##dev()
#define _STORAGE_SELECTOR(dev) _STORAGE_SELECTOR_concat(dev)

#define _FILESYSTEM_SELECTOR_concat(dev, ...) _filesystem_selector_##dev(__VA_ARGS__)
#define _FILESYSTEM_SELECTOR(dev, ...) _FILESYSTEM_SELECTOR_concat(dev, __VA_ARGS__)

BlockDevice* storage_selector() {
    return _STORAGE_SELECTOR(MBED_CONF_STORAGE_SELECTOR_STORAGE);
}

#ifdef MBED_CONF_STORAGE_SELECTOR_FILESYSTEM
bool _filesystem_initialized[MBED_CONF_STORAGE_SELECTOR_FILESYSTEM_INSTANCES];

FileSystem* filesystem_selector(const char* mount, BlockDevice* bd, unsigned int instance_number) {
    // Filesystem numbering starts at 1, not 0
    // This is meant to mirror the partition numbering present in MBRBlockDevice
    MBED_ASSERT(instance_number != 0);

    // Move to zero index here for internal operations
    instance_number--;
    // Ensure the requested filesystem instance is inside the declared range
    MBED_ASSERT(instance_number < MBED_CONF_STORAGE_SELECTOR_FILESYSTEM_INSTANCES);
    // Ensure the filesystem instance hasn't already been initialized
    MBED_ASSERT(!_filesystem_initialized[instance_number]);
    _filesystem_initialized[instance_number] = true;
    return _FILESYSTEM_SELECTOR(MBED_CONF_STORAGE_SELECTOR_FILESYSTEM, mount, bd, instance_number);
}

FileSystem* filesystem_selector(const char* mount) {
    return filesystem_selector(mount, storage_selector(), 1);
}

#endif //MBED_CONF_STORAGE_SELECTOR_FILESYSTEM
