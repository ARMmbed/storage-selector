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

#include "mbed.h"
#include "LittleFileSystem.h"

LittleFileSystem* _filesystem_selector_LITTLE(const char* mount, BlockDevice* bd, unsigned int instance_num) {
    MBED_ALIGN(2*sizeof(uintptr_t)) static char fs_instances[MBED_CONF_STORAGE_SELECTOR_FILESYSTEM_INSTANCES * sizeof(LittleFileSystem)];
    return new(&(fs_instances[instance_num * sizeof(LittleFileSystem)])) LittleFileSystem(mount, bd);
}
