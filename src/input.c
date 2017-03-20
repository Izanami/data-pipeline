/*
 *Data-Pipeline
 *Copyright © 2017 Adrien Jeser <adrien@jeser.me>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU Affero General Public License as
 *published by the Free Software Foundation, either version 3 of the
 *License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU Affero General Public License for more details.
 *
 *You should have received a copy of the GNU Affero General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "input.h"

DpInput* DpInputNew(void) {
    DpInput* input = NULL;
    DpPipelineCreate(&input);
    return input;
}

void __attribute__((overloadable)) DpPipelineCreate(DpInput** input) {
    *input = g_new(DpInput, 1);
    (*input)->pipeline = DpPipelineNew();
    DpPipelineInit(*input);
}

void __attribute__((overloadable)) DpPipelineInit(DpInput* self) {
    DpPipelineInit(self->pipeline);
    DpPipelineSetProperty(self->pipeline, "value", "");
}

void __attribute__((overloadable)) DpPipelineDestroy(DpInput** input) {
    DpPipeline* pipeline = (*input)->pipeline;
    DpPipelineDestroy(&pipeline);
    g_free(*input);
    *input = NULL;
}

DpPipeline* DpInputParent(DpInput* self) { return (self->pipeline); }

void DpInputAssign(DpInput* self, char* value) {
    DpPipelineSetProperty(self->pipeline, "value", value);
}

GString* __attribute__((overloadable)) DpInputGet(DpInput* self) {
    return DpInputGet(self->pipeline);
}

GString* __attribute__((overloadable)) DpInputGet(DpPipeline* self) {
    return DpPipelineGetProperty(self, "value");
}
