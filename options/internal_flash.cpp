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
#ifdef DEVICE_FLASH

#include "FlashIAPBlockDevice.h"

// Assert that the user has specified a flash region
#define INTERNAL_FLASH true
#if MBED_CONF_STORAGE_SELECTOR_STORAGE
MBED_STATIC_ASSERT(MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE > 0,
    "No flash region specified. Set configuration option "
    "'flashiap-block-device.size' to an integer greater than 0."
#endif
#undef INTERNAL_FLASH

FlashIAPBlockDevice* _storage_selector_INTERNAL_FLASH() {
    static FlashIAPBlockDevice bd(MBED_CONF_FLASHIAP_BLOCK_DEVICE_BASE_ADDRESS,
                                  MBED_CONF_FLASHIAP_BLOCK_DEVICE_SIZE);
    return &bd;
}

#endif //DEVICE_FLASH
