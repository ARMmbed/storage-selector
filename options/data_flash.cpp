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

#include "DataFlashBlockDevice.h"

DataFlashBlockDevice* _storage_selector_DATA_FLASH() {
    static DataFlashBlockDevice bd(MBED_CONF_DATAFLASH_SPI_MOSI,
                                   MBED_CONF_DATAFLASH_SPI_MISO,
                                   MBED_CONF_DATAFLASH_SPI_CLK,
                                   MBED_CONF_DATAFLASH_SPI_CS);
    return &bd;
}
