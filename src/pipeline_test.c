#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "pipeline.h"

static int setup(void **state) {
    DpPipeline *pipeline = NULL;
    DpPipelineCreate(&pipeline);

    *state = pipeline;
    return 0;
}
static int teardown(void **state) {
    DpPipeline *pipeline = *state;
    DpPipelineDestroy(&pipeline);
    return 0;
}

static void push_test(void **state) {
    DpPipeline *pipeline = *state;

    DpPipeline *pipeline_pushed = NULL;
    DpPipelineCreate(&pipeline_pushed);

    DpPipelinePushInput(pipeline, "foo", pipeline_pushed);
    DpPipelinePushOutput(pipeline, "foo", pipeline_pushed);

    DpPipelineDestroy(&pipeline_pushed);

    (void)state;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(push_test, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
