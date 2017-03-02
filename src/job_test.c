#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "job.h"

static int setup(void **state) {
    DpJob *job = DpJobNew();
    *state = job;
    return 0;
}

static int setup_populated(void **state) {
    setup(state);
    DpJobPipelineNew(*state);
    return 0;
}

static int teardown(void **state) {
    DpJob *job = *state;
    DpJobDestroy(&job);
    return 0;
}

static void null_test(void **state) { (void)state; }

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(null_test, setup, teardown),
        cmocka_unit_test_setup_teardown(null_test, setup_populated, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
