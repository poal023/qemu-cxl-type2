#include "qemu/osdep.h"
#include "util/cxl-zero-coalesce.h"

bool cxl_zero_range_add(CXLZeroRange *range, uint64_t start, uint64_t length)
{
    uint64_t end;
    uint64_t range_end;

    if (!range || length == 0 || start > UINT64_MAX - length) {
        return false;
    }
    end = start + length;

    if (range->length == 0) {
        range->start = start;
        range->length = length;
        return true;
    }
    if (range->start > UINT64_MAX - range->length) {
        return false;
    }
    range_end = range->start + range->length;
    if (start != range_end) {
        return false;
    }
    range->length = end - range->start;
    return true;
}
