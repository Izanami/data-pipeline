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

#ifndef DP_JOB_H_
#define DP_JOB_H_

#include "glib.h"

/*! \defgroup job Job
 *  \{
 */

/// \brief Job class.
typedef struct { GList* pipelines; } DpJob;

/// \brief Builder of job.
DpJob* DpJobNew(void) __attribute__((warn_unused_result));

/// \brief Constructor of job.
void DpJobCreate(DpJob**) __attribute__((nonnull));

/// \brief Destructor of job.
void DpJobDestroy(DpJob**) __attribute__((nonnull));

/// \brief Initalize data in job
void DpJobInit(DpJob*) __attribute__((nonnull));

/// \brief Deallocation memory of job.
void DpJobFree(DpJob*) __attribute__((nonnull));

/// \brief Build a pipeline.
gpointer DpJobPipelineNew(DpJob*);

/// \brief Returns all orhpans pipelines.
GList* DpJobOrphan(DpJob*) __attribute__((nonnull));

/// \brief Destroy all orphans pipelines.
void DpJobOrphanDestroy(DpJob*) __attribute__((nonnull));

/*!
 * \}
 */

#endif /* ifndef DP_JOB_H_ */
