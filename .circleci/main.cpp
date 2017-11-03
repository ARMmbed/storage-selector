#include "mbed.h"
#include "storage-selector.h"

int main() {
    // Create both the filesystem and the block device
    FileSystem *fs = filesystem_selector();

    // Retrieve just the block device and get erase size
    BlockDevice *bd = storage_selector();
    volatile bd_size_t erase_size = bd->get_erase_size();

    // Unmount fs
    fs->unmount();
}
