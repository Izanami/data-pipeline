#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "pipeline.h"

static int setup(void **state) {
    DpPipeline *pipeline = DpPipelineNew();

    *state = pipeline;
    return 0;
}

static int setup_populated(void **state) {
    setup(state);

    DpPipeline *pipeline = *state;

    DpPipeline *pipeline_input = NULL;
    DpPipelineCreate(&pipeline_input);

    DpPipeline *pipeline_output = NULL;
    DpPipelineCreate(&pipeline_output);

    DpPipelinePushInput(pipeline, "input", pipeline_input);
    DpPipelinePushOutput(pipeline, "output", pipeline_output);
    return 0;
}

static int teardown(void **state) {
    DpPipeline *pipeline = *state;
    DpPipelineDestroy(&pipeline);
    return 0;
}

static int teardown_populated(void **state) {
    DpPipeline *pipeline = *state;

    DpPipeline *pushed_output = DpPipelineGetOutput(pipeline, "output");
    assert_non_null(&pushed_output);
    DpPipelineDestroy(&pushed_output);

    DpPipeline *pushed_input = DpPipelineGetInput(pipeline, "input");
    assert_non_null(&pushed_input);
    DpPipelineDestroy(&pushed_input);

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
}

static void getter_test(void **state) {
    DpPipeline *pipeline = *state;

    assert_non_null(DpPipelineGetInput(pipeline, "input"));
    assert_non_null(DpPipelineGetOutput(pipeline, "output"));

    assert_null(DpPipelineGetOutput(pipeline, "unknown"));
    assert_null(DpPipelineGetInput(pipeline, "unknown"));
}

static void orphan_test(void **state) {
    DpPipeline *pipeline = *state;
    assert_true(DpPipelineIsOrphan(pipeline));
}

static void no_orphan_test(void **state) {
    DpPipeline *pipeline = *state;
    assert_false(DpPipelineIsOrphan(pipeline));
}

static void property_test(void **state) {
    DpPipeline *pipeline = *state;
    GString *value = NULL;

    assert_null(DpPipelineGetProperty(pipeline, "buzz"));
    DpPipelineSetProperty(pipeline, "buzz", "true");

    value = DpPipelineGetProperty(pipeline, "buzz");
    assert_non_null(value);
    assert_string_equal(value->str, "true");

    DpPipelineSetProperty(pipeline, "buzz", "false");

    value = DpPipelineGetProperty(pipeline, "buzz");
    assert_non_null(value);
    assert_string_equal(value->str, "true");
}

static int on_get_call = 0;
static void on_get(DpPipeline *self, const char *getted) {
    (void)self;
    (void)getted;
    on_get_call++;
}

static void on_get_test(void **state) {
    DpPipeline *pipeline = *state;
    DpPipelineOnGetInput(pipeline, on_get);
    DpPipelineOnGetOutput(pipeline, on_get);

    DpPipelineGetInput(pipeline, "bar");
    assert_int_equal(on_get_call, 1);
    DpPipelineGetOutput(pipeline, "bar");
    assert_int_equal(on_get_call, 2);
}

static int on_push_call = 0;
static void on_push(DpPipeline *self, const char *getted) {
    (void)self;
    (void)getted;
    on_push_call++;
}

static void on_push_test(void **state) {
    DpPipeline *pipeline = *state;
    DpPipeline *pipeline_pushed = DpPipelineNew();

    DpPipelinePushInput(pipeline, "buzz", pipeline_pushed);
    DpPipelinePushOutput(pipeline, "buzz", pipeline_pushed);
    assert_int_equal(on_push_call, 0);

    DpPipelineOnPushOutput(pipeline, on_push);
    DpPipelineOnPushInput(pipeline, on_push);
    assert_int_equal(on_push_call, 0);

    DpPipelinePushOutput(pipeline, "buzz", pipeline_pushed);
    assert_int_equal(on_push_call, 1);
    DpPipelinePushInput(pipeline, "buzz", pipeline_pushed);
    assert_int_equal(on_push_call, 2);

    DpPipelineDestroy(&pipeline_pushed);
    (void)pipeline;
}

static void on_remove_test(void **state) {
    DpPipeline *pipeline = *state;
    DpPipeline *pipeline_pushed = DpPipelineNew();

    DpPipelinePushInput(pipeline, "buzz", pipeline_pushed);
    DpPipelinePushOutput(pipeline, "buzz", pipeline_pushed);

    DpPipelineRemoveInput(pipeline, "buzz");
    DpPipelineRemoveOutput(pipeline, "buzz");

    assert_null(DpPipelineGetInput(pipeline, "buzz"));
    assert_null(DpPipelineGetOutput(pipeline, "buzz"));

    DpPipelineDestroy(&pipeline_pushed);
    (void)pipeline;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(push_test, setup, teardown),
        cmocka_unit_test_setup_teardown(getter_test, setup_populated,
                                        teardown_populated),
        cmocka_unit_test_setup_teardown(orphan_test, setup, teardown),
        cmocka_unit_test_setup_teardown(no_orphan_test, setup_populated,
                                        teardown_populated),
        cmocka_unit_test_setup_teardown(property_test, setup, teardown),
        cmocka_unit_test_setup_teardown(on_get_test, setup, teardown),
        cmocka_unit_test_setup_teardown(on_push_test, setup, teardown),
        cmocka_unit_test_setup_teardown(on_remove_test, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
