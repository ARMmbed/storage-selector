#include "mbed.h"
#include "storage-selector.h"

#define BLOCK_NUMBER 0

int main() {
    printf("Welcome to the storage selector example.\r\n");
    printf("Initializing...\r\n");
    BlockDevice *bd = storage_selector();
    int error = bd->init();

    if (error) {
        printf("Block device failed to initialize with error %d\r\n", error);
        return -1;
    }

    bd_size_t erase_size = bd->get_erase_size();
    uint8_t *buffer = new uint8_t[erase_size];

    for (unsigned int i = 0; i < erase_size; i++) {
        buffer[i] = i % 256;
    }

    printf("Erasing...\r\n");
    error = bd->erase(BLOCK_NUMBER, erase_size);

    if (error) {
        printf("Block device failed to erase with error %d\r\n", error);
        return -1;
    }

    printf("Programming...\r\n");
    error = bd->program(buffer, BLOCK_NUMBER, erase_size);

    if (error) {
        printf("Block device failed to program with error %d\r\n", error);
        return -1;
    }

    memset(buffer, 0, erase_size);

    printf("Reading...\r\n");
    error = bd->read(buffer, BLOCK_NUMBER, erase_size);

    if (error) {
        printf("Block device failed to read with error %d\r\n", error);
        return -1;
    }

    printf("Confirming values...\r\n");
    uint8_t expected;
    for (unsigned int i = 0; i < erase_size; i++) {
        expected = i % 256;
        if (buffer[i] != expected) {
            printf("[ERR] Expected value %d at byte %d, actual value was %d\r\n", expected, i, buffer[i]);
        }
    }

    printf("Deinitializing...\r\n");
    error = bd->deinit();

    if (error) {
        printf("Block device failed to deinit with error %d\r\n", error);
        return -1;
    }

    printf("Storage selector example complete.\r\n");
    delete[] buffer;
    while (true) {}
}
