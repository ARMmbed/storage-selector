# Storage Selector
Library used to select from a list of possible Block Device implementations.

## Storage options
The following storage options are supported:

- `SD_CARD` - Uses SPI (defaults to onboard card slot if available)
- `SPI_FLASH` - Must be a standard Serial NOR Flash device (defaults to onboard flash if available)
- `DATA_FLASH` - Supports the SPI interface for the AT45DB device family
- `INTERNAL_FLASH` - Uses internal flash of device
- `HEAP` - RAM backed device, most useful for debugging

Most of these options have additional configuration options. They are designed to have reasonable defaults, but you are encouraged to override these values to suit your needs. See the corresponding driver for more information

## Selecting the storage

In you application's `mbed_app.json`, add the following lines:

```json
{
    "target_overrides": {
        "K64F": {
            "storage-selector.storage": "SPI_FLASH"
        }
    }
}
```

Where `K64F` would be replaced by your target and `SPI_FLASH` would be replaced by the storage option.

## Adding new storage options
The following should be true for all new storage options:

- The driver should compile **even when not in use**
    - This means if the driver requires config options, you should provide reasonable defaults
- The driver should not add to the ROM/RAM usage when not in use
- The driver should be wrapped in `#ifdef DEVICE_*` guards for the Mbed HAL APIs it uses to ensure it compiles
    - An example of this can be seen in the [sd-driver](https://github.com/ARMmbed/sd-driver/blob/master/SDBlockDevice.h#L26)
