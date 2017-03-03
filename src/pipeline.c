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
    DpPipelineFree(*pipeline);
    g_free(*pipeline);
    *pipeline = NULL;
}

void DpPipelineInit(DpPipeline* self) {
    g_datalist_init(&(self->input));
    g_datalist_init(&(self->output));

    self->input_count = 0;
    self->output_count = 0;
}

void DpPipelineFree(DpPipeline* self) {
    g_datalist_clear(&(self->input));
    g_datalist_clear(&(self->output));
    self->input_count = 0;
    self->output_count = 0;
}

gboolean DpPipelinePushInput(DpPipeline* self, const char* key,
                             DpPipeline* pipeline_input) {
    // Ignore push because a circular dependency is forbidden.
    if (self == pipeline_input) return FALSE;

    self->input_count++;

    g_datalist_set_data(&self->input, key, pipeline_input);
    return TRUE;
}

gboolean DpPipelinePushOutput(DpPipeline* self, const char* key,
                              DpPipeline* pipeline_output) {
    // Ignore push because a circular dependency is forbidden.
    if (self == pipeline_output) return FALSE;

    self->output_count++;

    g_datalist_set_data(&self->output, key, pipeline_output);
    return TRUE;
}

gpointer DpPipelineGetInput(DpPipeline* self, const char* key) {
    return g_datalist_get_data(&self->input, key);
}

gpointer DpPipelineGetOutput(DpPipeline* self, const char* key) {
    return g_datalist_get_data(&self->output, key);
}
