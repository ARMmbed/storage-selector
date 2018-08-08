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

#include "mbed.h"
#include "filesystem/FileSystem.h"

BlockDevice* storage_selector();

#ifdef MBED_CONF_STORAGE_SELECTOR_FILESYSTEM

mbed::FileSystem* filesystem_selector(const char* mount, BlockDevice* bd, unsigned int instance_number = 1);

mbed::FileSystem* filesystem_selector(const char* mount = MBED_CONF_STORAGE_SELECTOR_MOUNT_POINT);

#endif //MBED_CONF_STORAGE_SELECTOR_FILESYSTEM

#endif //_STORAGE_SELECTOR_H_
