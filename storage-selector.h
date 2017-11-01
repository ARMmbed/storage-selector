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
