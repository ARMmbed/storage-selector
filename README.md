# Storage Selector
Library used to select from a list of possible Block Device implementations.

## Storage options
The following storage options are supported:

- `SDCARD`

## Selecting the storage

In the application's `mbed_app.json`, add the following lines:

```json
{
    "target_overrides": {
        "K64F": {
            "storage-selector.storage": "SPIFLASH"
        }
    }
}
```

Where `K64F` would be replaced by your target and `SPIFLASH` would be replaced by the storage option.
