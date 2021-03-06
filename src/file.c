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

DpFile* DpFileNew(void) {
    DpFile* file = NULL;
    DpPipelineCreate(&file);
    return file;
}

static void DpFileUploadPath(DpPipeline* self) {
    DpPipeline* pipeline = DpPipelineGetInput(self, "path");
    GString* path = pipeline->Get(pipeline);
    DpPipelineSetProperty(self, "path", path->str);
}

static void DpFilePushInput(struct DpPipeline* self, const char* key) {
    if (g_strcmp0("path", key) == 0) {
        DpFileUploadPath(self);
    }
}

void __attribute__((overloadable)) DpPipelineCreate(DpFile** file) {
    *file = g_new(DpFile, 1);
    (*file)->pipeline = DpPipelineNew();
    DpPipelineInit(*file);
}

void __attribute__((overloadable)) DpPipelineInit(DpFile* self) {
    DpPipelineInit(self->pipeline);
    self->pipeline->OnPushInput = DpFilePushInput;
}

void __attribute__((overloadable)) DpPipelineDestroy(DpFile** file) {
    DpPipeline* pipeline = (*file)->pipeline;
    DpPipelineDestroy(&pipeline);
    g_free(*file);
    *file = NULL;
}

GString* DpFileGetPath(DpFile* self) {
    return DpPipelineGetProperty(self->pipeline, "path");
}
