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

static void orphans_test(void **state) {
    DpJob *job = *state;
    GList *orphans = DpJobOrphan(job);
    assert_non_null(orphans);
}

static void orphans_destroy_test(void **state) {
    DpJob *job = *state;
    DpJobOrphanDestroy(job);

    GList *orphans = DpJobOrphan(job);
    assert_null(orphans);
    assert_null(job->pipelines);
    *state = job;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(null_test, setup, teardown),
        cmocka_unit_test_setup_teardown(null_test, setup_populated, teardown),
        cmocka_unit_test_setup_teardown(orphans_test, setup_populated,
                                        teardown),
        cmocka_unit_test_setup_teardown(orphans_destroy_test, setup_populated,
                                        teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
