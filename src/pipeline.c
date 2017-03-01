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
}

void DpPipelineFree(DpPipeline* self) {
    g_datalist_clear(&(self->input));
    g_datalist_clear(&(self->output));
}

gboolean DpPipelinePushInput(DpPipeline* self, const char* name,
                             DpPipeline* pipeline_input) {
    // Ignore push because circular dependency is forbidden.
    if (self == pipeline_input) return FALSE;

    g_datalist_set_data(&self->input, name, pipeline_input);
    return TRUE;
}

gboolean DpPipelinePushOutput(DpPipeline* self, const char* name,
                              DpPipeline* pipeline_output) {
    // Ignore push because circular dependency is forbidden.
    if (self == pipeline_output) return FALSE;

    g_datalist_set_data(&self->output, name, pipeline_output);
    return TRUE;
}
