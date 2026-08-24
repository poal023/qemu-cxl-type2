#include "qemu/osdep.h"
#include "util/cxl-zero-coalesce.h"

static void test_adjacent_zero_writes_merge(void)
{
    CXLZeroRange range = { 0 };

    g_assert_true(cxl_zero_range_add(&range, 0x1000, 8));
    g_assert_true(cxl_zero_range_add(&range, 0x1008, 16));
    g_assert_cmphex(range.start, ==, 0x1000);
    g_assert_cmphex(range.length, ==, 24);
}

static void test_gap_does_not_merge(void)
{
    CXLZeroRange range = { 0 };

    g_assert_true(cxl_zero_range_add(&range, 0x1000, 8));
    g_assert_false(cxl_zero_range_add(&range, 0x1010, 8));
    g_assert_cmphex(range.start, ==, 0x1000);
    g_assert_cmphex(range.length, ==, 8);
}

static void test_overflow_does_not_merge(void)
{
    CXLZeroRange range = { 0 };

    g_assert_true(cxl_zero_range_add(&range, UINT64_MAX - 8, 8));
    g_assert_false(cxl_zero_range_add(&range, 0, 1));
    g_assert_cmphex(range.start, ==, UINT64_MAX - 8);
    g_assert_cmphex(range.length, ==, 8);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/cxl-zero-coalesce/adjacent", test_adjacent_zero_writes_merge);
    g_test_add_func("/cxl-zero-coalesce/gap", test_gap_does_not_merge);
    g_test_add_func("/cxl-zero-coalesce/overflow", test_overflow_does_not_merge);
    return g_test_run();
}
