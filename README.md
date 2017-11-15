# Storage Selector
Storage Selector is used to select from a list of possible Block Device implementations and FileSystem implementations.

## Storage options
The following storage options are supported:

- `SD_CARD` - Uses SPI (defaults to onboard card slot if available).
- `SPI_FLASH` - Must be a standard Serial NOR Flash device (defaults to onboard flash if available).
- `DATA_FLASH` - Supports the SPI interface for the AT45DB device family.
- `INTERNAL_FLASH` - Uses internal flash of device.
- `HEAP` - RAM backed device, most useful for debugging.

Most of these options have additional configuration options. They are designed to have reasonable defaults, but you are encouraged to override these values to suit your needs. See the corresponding driver for more information

## Selecting the storage

In your application's `mbed_app.json`, add the following lines:

```json
{
    "target_overrides": {
        "K64F": {
            "storage-selector.storage": "SPI_FLASH"
        }
    }
}
```

Where `K64F` should be replaced by your target and `SPI_FLASH` should be replaced by the storage option.

## Using the storage

In your application, instantiate the Block Device object like this:

```
#include "storage-selector/storage-selector.h"

BlockDevice* bd = storage_selector();
```

## Adding new storage options
The following must be true for all new storage options:

- The driver must compile **even when not in use**.
    - This means if the driver requires config options, you must provide reasonable defaults.
- The driver must not add to the ROM/RAM usage when not in use.
- The driver must be wrapped in `#ifdef DEVICE_*` guards for the Mbed HAL APIs it uses to ensure it compiles.
    - An example of this can be seen in the [sd-driver](https://github.com/ARMmbed/sd-driver/blob/master/SDBlockDevice.h#L26).

## Filesystem options

The following filesystem options are supported:

- `FAT` - FAT filesystem.
- `LITTLE` - Experimental fail-safe embedded filesystem.

Most filesystems have additional configuration options. They are designed to have reasonable defaults, but you are encouraged to override these values to suit your needs. See the corresponding driver for more information

## Selecting the filesystem

In your application's `mbed_app.json`, add the following lines:

```json
{
    "target_overrides": {
        "NUCLEO_F429ZI": {
            "storage-selector.filesystem": "FAT",
            "storage-selector.mount-point": "\"sd\""
        }
    }
}
```

Where `NUCLEO_F429ZI` should be replaced by your target, `FAT` should be replaced by the filesystem option, and `mount-point` should be replaced with the filesystem mounting point. Note the escaped double quotes around the mounting point. You only need to configure a filesystem if you intend to use one.

## Multiple filesystems/partitions

You need to configure an addition config parameter to use multiple filesystems/partitions:

```
{
    "target_overrides": {
        "NUCLEO_F429ZI": {
            "storage-selector.filesystem-instances": 2
        }
    }
}
```

The following is an example of using the `MBRBlockDevice` to use multiple partitions.

```c++
// Get the block device
BlockDevice *bd = storage_selector();
bd->init();

// Create and initialize partitions
MBRBlockDevice::partition(bd , 1, 0x83, 0, 512*1024);
MBRBlockDevice::partition(bd , 2, 0x83, 512*1024, 1024*1024);
MBRBlockDevice part1(bd, 1);
MBRBlockDevice part2(bd, 2);

// Mount the filesystems
FileSystem *fs1 = filesystem_selector("fs1", &part1, 0);
FileSystem *fs2 = filesystem_selector("fs2", &part2, 1);
```

## Using the filesystem

In your application, you can instantiate the filesystem like this:

```
FileSystem* fs = filesystem_selector();
```

This will automatically instantiate the Block Device selected and pass it to the selected filesystem and mount it at the configured location. Alternatively, a selected filesystem can be instantiated manually:

```
BlockDevice* sd = storage_selector();
FileSystem* fs = filesystem_selector("sd", sd);
```

## Adding new filesystem options
The following must be true for all new filesystem options:

- The filesystem must compile **even when not in use**.
    - This means if the filesystem requires config options, you must provide reasonable defaults.
- The filesystem must not add to the ROM/RAM usage when not in use.
