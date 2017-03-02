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

#include "job.h"
#include "pipeline.h"

DpJob* DpJobNew(void) {
    DpJob* job = NULL;
    DpJobCreate(&job);
    return job;
}

void DpJobCreate(DpJob** job) {
    *job = g_new(DpJob, 1);
    DpJobInit(*job);
}

void DpJobDestroy(DpJob** job) {
    DpJobFree(*job);
    g_free(*job);
    *job = NULL;
}

void DpJobInit(DpJob* self) { self->pipelines = NULL; }

static void DpJobFreeEach(gpointer data) {
    DpPipeline* pipeline = data;
    DpPipelineDestroy(&pipeline);
}

void DpJobFree(DpJob* self) {
    g_list_free_full(self->pipelines, &DpJobFreeEach);
}

gpointer DpJobPipelineNew(DpJob* self) {
    DpPipeline* pipeline = DpPipelineNew();

    self->pipelines = g_list_append(self->pipelines, pipeline);
    return NULL;
}

GList* DpJobOrphan(DpJob* self) {
    GList* orphans = NULL;
    GList* pipelines = self->pipelines;

    while (pipelines != NULL) {
        DpPipeline* pipeline = pipelines->data;
        if (pipeline->input_count == 0 && pipeline->output_count == 0) {
            orphans = g_list_append(orphans, pipeline);
        }

        pipelines = g_list_next(pipelines);
    }

    return orphans;
}

void DpJobOrphanDestroy(DpJob* self) {
    GList* cursor = self->pipelines;

    while (cursor != NULL) {
        DpPipeline* pipeline = cursor->data;

        // If has not any link, when destroy it.
        if (pipeline->input_count == 0 && pipeline->output_count == 0) {
            self->pipelines = g_list_delete_link(self->pipelines, cursor);
            g_list_free1(cursor);
            DpPipelineDestroy(&pipeline);
        }
        cursor = g_list_next(cursor);
    }
}
