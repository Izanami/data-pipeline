#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "file.h"

static int setup(void **state) {
    DpFile *file = DpFileNew();
    *state = file;
    return 0;
}

static int teardown(void **state) {
    DpFile *file = *state;
    DpPipelineDestroy(&file);
    return 0;
}

static void null_test(void **state) { (void)state; }

static void input_test(void **state) {
    DpFile *file = *state;
    DpInput *input = DpInputNew();
    DpInputAssign(input, "fum");

    DpPipelinePushInput(file, "path", input);
    assert_string_equal(DpFileGetPath(file)->str, "fum");

    DpPipelineDestroy(&input);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(null_test, setup, teardown),
        cmocka_unit_test_setup_teardown(input_test, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
