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

#include "file.h"

DpPipeline* DpFileNew(void) {
    DpPipeline* pipeline = NULL;
    DpPipelineCreate(&pipeline);
    return pipeline;
}

void __attribute__((overloadable)) DpPipelineCreate(DpFile** file) {
    *file = g_new(DpFile, 1);
    (*file)->pipeline = DpPipelineNew();
    DpPipelineInit(*file);
}

void __attribute__((overloadable)) DpPipelineInit(DpFile* self) {
    DpPipelineInit(self->pipeline);
}

void __attribute__((overloadable)) DpPipelineDestroy(DpFile** file) {
    DpPipeline* pipeline = (*file)->pipeline;
    DpPipelineDestroy(&pipeline);
    g_free(*file);
    *file = NULL;
}
