#include "sstest.h"
#include "storage-selector.h"

BlockDevice* sstest_indirection() {
    return storage_selector();
}
