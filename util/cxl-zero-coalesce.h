#ifndef CXL_ZERO_COALESCE_H
#define CXL_ZERO_COALESCE_H

#include "qemu/osdep.h"

typedef struct CXLZeroRange {
    uint64_t start;
    uint64_t length;
} CXLZeroRange;

/* Add one exact zero-write interval. Returns false when it is not adjacent. */
bool cxl_zero_range_add(CXLZeroRange *range, uint64_t start, uint64_t length);

#endif
