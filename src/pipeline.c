/*
 *DataPipeline - Pipeline
 *Copyright © 2017 Adrien Jeser <adrien@jeser.me>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pipeline.h"

DpPipeline* DpPipelineNew(void) {
    DpPipeline* pipeline = NULL;
    DpPipelineCreate(&pipeline);
    return pipeline;
}

void DpPipelineCreate(DpPipeline** pipeline) {
    *pipeline = g_new(DpPipeline, 1);
    DpPipelineInit(*pipeline);
}

void DpPipelineDestroy(DpPipeline** pipeline) {
    if ((*pipeline)->OnDestroy != NULL) (*pipeline)->OnDestroy(*pipeline);

    DpPipelineFree(*pipeline);
    g_free(*pipeline);
    *pipeline = NULL;
}

void DpPipelineInit(DpPipeline* self) {
    g_datalist_init(&(self->input));
    g_datalist_init(&(self->output));
    g_datalist_init(&(self->properties));

    self->input_count = 0;
    self->output_count = 0;

    self->OnGetInput = NULL;
    self->OnGetOutput = NULL;
    self->OnPushInput = NULL;
    self->OnPushOutput = NULL;
    self->OnDestroy = NULL;
}

void DpPipelineFree(DpPipeline* self) {
    g_datalist_clear(&(self->input));
    g_datalist_clear(&(self->output));
    g_datalist_clear(&(self->properties));
    self->input_count = 0;
    self->output_count = 0;
}

gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input) {
    // Ignore push because a circular dependency is forbidden.
    if (self == pipeline_input) return FALSE;

    g_datalist_set_data(&self->input, key, pipeline_input);
    self->input_count++;

    if (self->OnPushInput != NULL) self->OnPushInput(self, key);

    return TRUE;
}

gboolean DpPipelinePushOutput(DpPipeline* self, const char* key,
                              DpPipeline* pipeline_output) {
    // Ignore push because a circular dependency is forbidden.
    if (self == pipeline_output) return FALSE;

    g_datalist_set_data(&self->output, key, pipeline_output);
    self->output_count++;

    if (self->OnPushOutput != NULL) self->OnPushOutput(self, key);
    return TRUE;
}

DpPipeline* DpPipelineGetInput(DpPipeline* self, const char* key) {
    DpPipeline* input = g_datalist_get_data(&self->input, key);
    if (self->OnGetInput != NULL) self->OnGetInput(self, key);
    return input;
}

DpPipeline* DpPipelineGetOutput(DpPipeline* self, const char* key) {
    DpPipeline* output = g_datalist_get_data(&self->output, key);
    if (self->OnGetOutput != NULL) self->OnGetOutput(self, key);
    return output;
}

void DpPipelineRemoveInput(DpPipeline* self, const char* key) {
    g_datalist_remove_data(&(self->input), key);
    self->input_count--;
}

void DpPipelineRemoveOutput(DpPipeline* self, const char* key) {
    g_datalist_remove_data(&(self->output), key);
    self->output_count--;
}

gboolean DpPipelineIsOrphan(DpPipeline* self) {
    return (self->output_count == 0 && self->input_count == 0);
}

GString* DpPipelineGetProperty(DpPipeline* self, const char* name_property) {
    return g_datalist_get_data(&self->properties, name_property);
}

void DpPipelineSetProperty(DpPipeline* self, const char* name_property,
                           char* value) {
    GString* value_str = DpPipelineGetProperty(self, name_property);

    // If not exists, when initialize.
    if (value_str == NULL) {
        value_str = g_string_new(value);
    } else {
        g_string_assign(value_str, value);
    }

    g_datalist_set_data(&self->properties, name_property, value_str);
}

void DpPipelineOnGetInput(DpPipeline* self,
                          void observer(DpPipeline*, const char*)) {
    self->OnGetInput = observer;
}

void DpPipelineOnGetOutput(DpPipeline* self,
                           void observer(DpPipeline*, const char*)) {
    self->OnGetOutput = observer;
}

void DpPipelineOnPushOutput(DpPipeline* self,
                            void observer(DpPipeline*, const char*)) {
    self->OnPushOutput = observer;
}

void DpPipelineOnPushInput(DpPipeline* self,
                           void observer(DpPipeline*, const char*)) {
    self->OnPushInput = observer;
}

void DpPipelineOnDestroy(DpPipeline* self, void observer(DpPipeline*)) {
    self->OnDestroy = observer;
}

gboolean DpPipelineIsInputExists(DpPipeline* self, const char* key) {
    return (g_datalist_get_data(&self->input, key) != NULL);
}

gboolean DpPipelineIsOutputExists(DpPipeline* self, const char* key) {
    return (g_datalist_get_data(&self->output, key) != NULL);
}
