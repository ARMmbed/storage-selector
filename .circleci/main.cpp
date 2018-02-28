#include "mbed.h"
#include "sstest.h"
#include "storage-selector.h"

int main() {
    printf("Starting...\r\n");
    // Retrieve just the block device and get erase size
    BlockDevice *bd = storage_selector();
    BlockDevice *bd_same = sstest_indirection();

    // Pointers should be the same
    MBED_ASSERT(bd == bd_same);

    bd->init();
    volatile bd_size_t erase_size = bd->get_erase_size();

    SlicingBlockDevice slice1(bd, 0*512, 32*512);
    SlicingBlockDevice slice2(bd, 32*512, 64*512);

    // Multiple filesystem example (partitions)
    printf("Fs warnings may show here...\r\n");
    FileSystem *fs1 = filesystem_selector("s1", &slice1, 1);
    FileSystem *fs2 = filesystem_selector("s2", &slice2, 2);

    printf("\r\nReformatting...\r\n");
    fs1->reformat();
    fs2->reformat();

    // Unmount fs
    fs1->unmount();
    fs2->unmount();

    fs1->mount(&slice1);
    fs2->mount(&slice2);
    printf("Completed!\r\n");
}
