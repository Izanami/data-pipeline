#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "file.h"

static int setup(void **state) {
    DpPipeline *pipeline = DpFileNew();
    *state = pipeline;
    return 0;
}

static int teardown(void **state) {
    DpPipeline *pipeline = *state;
    DpPipelineDestroy(&pipeline);
    return 0;
}

static void null_test(void **state) { (void)state; }

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(null_test, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}