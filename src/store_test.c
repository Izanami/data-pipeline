#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "store.h"

static int setup_int(void **state) {
    int d = 4;
    DpStore *store = DpStoreNew(&d);
    *state = store;
    return 0;
}

static int teardown(void **state) {
    DpStore *store = *state;
    DpStoreDestroy(&store);
    return 0;
}

static void null_test(void **state) { (void)state; }

static void is_test(void **state) {
    DpStore *store = *state;
    assert_true(DpStoreIs(store, kInteger));
    assert_false(DpStoreIs(store, kString));
}

static void same_test(void **state) {
    DpStore *store = *state;
    int bar = 42;
    assert_true(DpStoreSame(store, &bar));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(null_test, setup_int, teardown),
        cmocka_unit_test_setup_teardown(is_test, setup_int, teardown),
        cmocka_unit_test_setup_teardown(same_test, setup_int, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
